#pragma once

#include <JuceHeader.h>

class LinearPhaseFourBandEQ
{
public:
    LinearPhaseFourBandEQ() = default;

    // Call this from prepareToPlay
    void prepare (double sampleRate, int samplesPerBlock, int numChannels)
    {
        fs           = sampleRate;
        maxBlockSize = samplesPerBlock;
        numCh        = numChannels;

        juce::dsp::ProcessSpec spec;
        spec.sampleRate       = fs;
        spec.maximumBlockSize = static_cast<juce::uint32> (maxBlockSize);
        spec.numChannels      = static_cast<juce::uint32> (numCh);

        updateFilters();              // creates coefficients, sets lp1/lp2/lp3.state

        lp1.prepare (spec);
        lp2.prepare (spec);
        lp3.prepare (spec);

        lp1.reset();
        lp2.reset();
        lp3.reset();

        // allocate temp buffers
        originalBuffer.setSize (numCh, maxBlockSize);
        lp1Buffer      .setSize (numCh, maxBlockSize);
        lp2Buffer      .setSize (numCh, maxBlockSize);
        lp3Buffer      .setSize (numCh, maxBlockSize);
    }

    void reset()
    {
        lp1.reset();
        lp2.reset();
        lp3.reset();
    }

    // crossover frequencies in Hz (must be ascending and < Nyquist)
    void setCrossoverFrequencies (float f1, float f2, float f3)
    {
        crossovers[0] = f1;
        crossovers[1] = f2;
        crossovers[2] = f3;
        filtersNeedUpdate = true;
    }

    // per-band linear gains (not dB)
    void setBandGain (int band, float gain)
    {
        if (band >= 0 && band <= sizeof(bandGains)) {
            bandGains[band] = gain;
        } else {
            DBG("Band number outside of bounds");
        }
    }
    
    void setBandGains (Array<float> gains)
    {
        for (int i = 0; i < gains.size(); i++) {
            setBandGain(i, gains[i]);
        }
    }
    
    juce::Array<float> getBandGains() {
        Array<float> gains;
        gains.resize(4);
        gains.set(0, bandGains[0]);
        gains.set(1, bandGains[1]);
        gains.set(2, bandGains[2]);
        gains.set(3, bandGains[3]);
        return gains;
    }

    void setFirOrder (size_t newOrder)
    {
        firOrder = newOrder | 1u; // force odd order => nice symmetric center tap
        filtersNeedUpdate = true;
    }

    // === your AudioProcessor::processBlock calls this ===
    void processBlock (juce::AudioBuffer<float>& buffer)
    {
        auto numSamples = buffer.getNumSamples();
        jassert (numSamples <= maxBlockSize);

        if (filtersNeedUpdate)
            updateFilters();

        // Ensure temp buffers match current block size
        originalBuffer.setSize (numCh, numSamples, false, false, true);
        lp1Buffer      .setSize (numCh, numSamples, false, false, true);
        lp2Buffer      .setSize (numCh, numSamples, false, false, true);
        lp3Buffer      .setSize (numCh, numSamples, false, false, true);

        // store original
        originalBuffer.makeCopyOf (buffer);

        // copy original into LP buffers
        lp1Buffer.makeCopyOf (originalBuffer);
        lp2Buffer.makeCopyOf (originalBuffer);
        lp3Buffer.makeCopyOf (originalBuffer);

        // process LP filters (linear-phase FIRs)
        {
            juce::dsp::AudioBlock<float> block1 (lp1Buffer);
            juce::dsp::AudioBlock<float> block2 (lp2Buffer);
            juce::dsp::AudioBlock<float> block3 (lp3Buffer);

            juce::dsp::ProcessContextReplacing<float> ctx1 (block1);
            juce::dsp::ProcessContextReplacing<float> ctx2 (block2);
            juce::dsp::ProcessContextReplacing<float> ctx3 (block3);

            lp1.process (ctx1);
            lp2.process (ctx2);
            lp3.process (ctx3);
        }

        // Recombine into 4 bands:
        //
        // B1: LP(f1)
        // B2: LP(f2) - LP(f1)
        // B3: LP(f3) - LP(f2)
        // B4: x - LP(f3)
        //
        // Then apply per-band gain and sum into output buffer
        buffer.clear();

        for (int ch = 0; ch < numCh; ++ch)
        {
            const float* x  = originalBuffer.getReadPointer (ch);
            const float* l1 = lp1Buffer     .getReadPointer (ch);
            const float* l2 = lp2Buffer     .getReadPointer (ch);
            const float* l3 = lp3Buffer     .getReadPointer (ch);
            float*       y  = buffer        .getWritePointer (ch);

            for (int n = 0; n < numSamples; ++n)
            {
                const float in  = x[n];

                const float b1  = l1[n];
                const float b2  = l2[n] - l1[n];
                const float b3  = l3[n] - l2[n];
                const float b4  = in    - l3[n];

                const float out =
                    bandGains[0] * b1 +
                    bandGains[1] * b2 +
                    bandGains[2] * b3 +
                    bandGains[3] * b4;

                y[n] = out;
            }
        }
    }

private:
    using FIRFilter = juce::dsp::FIR::Filter<float>;
    using FIRCoeffs = juce::dsp::FIR::Coefficients<float>;
    using FIR       = juce::dsp::ProcessorDuplicator<FIRFilter, FIRCoeffs>;

    void updateFilters()
    {
        // Design 3 linear-phase FIR low-passes using window method.
        // docs: designFIRLowpassWindowMethod creates linear-phase FIR coeffs  [oai_citation:0‡JUCE Docs](https://docs.juce.com/master/structjuce_1_1dsp_1_1FilterDesign.html?utm_source=chatgpt.com)
        auto mkLP = [this] (float cutoffHz)
        {
            constexpr auto window = juce::dsp::WindowingFunction<float>::blackman;
            auto coeffPtr = juce::dsp::FilterDesign<float>::designFIRLowpassWindowMethod(
                                cutoffHz,
                                fs,
                                firOrder,
                                window);

            return coeffPtr;
        };

        auto lp1Coeffs = mkLP (crossovers[0]);
        auto lp2Coeffs = mkLP (crossovers[1]);
        auto lp3Coeffs = mkLP (crossovers[2]);

        jassert (lp1Coeffs != nullptr && lp2Coeffs != nullptr && lp3Coeffs != nullptr);

        *lp1.state = *lp1Coeffs;
        *lp2.state = *lp2Coeffs;
        *lp3.state = *lp3Coeffs;

        filtersNeedUpdate = false;
    }

    double fs           = 44100.0;
    int    maxBlockSize = 512;
    int    numCh        = 2;

    // default crossovers
    float crossovers[3] { 200.0f, 2000.0f, 8000.0f };
    float bandGains[4]  { 1.0f, 1.0f, 1.0f, 1.0f };  // linear

    size_t firOrder        = 127;   // FIR order (=> 128 taps); bigger = steeper, more latency
    bool   filtersNeedUpdate = true;

    FIR lp1, lp2, lp3;

    juce::AudioBuffer<float> originalBuffer;
    juce::AudioBuffer<float> lp1Buffer, lp2Buffer, lp3Buffer;
};

// TODO: Use this inside Processor
struct EQState {
    EQState() = default;
    
    static constexpr int numBands = 4;
    
    float bandGains[numBands] = { 1.0f };
    float bandMutes[numBands] = { false };
    float bandSolos[numBands] = { false };
};
