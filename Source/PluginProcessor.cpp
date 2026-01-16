/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
HelloWorldAudioProcessor::HelloWorldAudioProcessor()
     : AudioProcessor (BusesProperties()
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true))
, state(*this, nullptr, "HelloWorldState", createParameterLayout())
{
    DBG ("PluginProcessor ()");
    eqState = EQState();
}

HelloWorldAudioProcessor::~HelloWorldAudioProcessor()
{
    DBG ("~PluginProcessor ()"); // will be called when an instance of HelloWorlAudioProcessor is destroyed
}

//==============================================================================
const juce::String HelloWorldAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool HelloWorldAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool HelloWorldAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool HelloWorldAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double HelloWorldAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int HelloWorldAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int HelloWorldAudioProcessor::getCurrentProgram()
{
    return 0;
}

void HelloWorldAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String HelloWorldAudioProcessor::getProgramName (int index)
{
    return {};
}

void HelloWorldAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void HelloWorldAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    eq.prepare(sampleRate, samplesPerBlock, 2);
}

void HelloWorldAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool HelloWorldAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void HelloWorldAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    
    // DBG ("Buffer Size: " << buffer.getNumSamples ());
    
    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
        
    eq.processBlock(buffer);
}

//==============================================================================
bool HelloWorldAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* HelloWorldAudioProcessor::createEditor()
{
    return new HelloWorldAudioProcessorEditor (*this);
}

//==============================================================================
void HelloWorldAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void HelloWorldAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new HelloWorldAudioProcessor();
}

void HelloWorldAudioProcessor::setEqGain(int band, float gain)
{
    eqState.bandGains[band] = gain;
    applyEQState();
}

void HelloWorldAudioProcessor::setMuteBand(int band, bool isMuted)
{
    eqState.bandMutes[band] = isMuted;
    applyEQState();
}

void HelloWorldAudioProcessor::setSoloBand(int band, bool isSolo)
{
    eqState.bandSolos[band] = isSolo;
    applyEQState();
}

void HelloWorldAudioProcessor::applyEQState()
{
    Array<float> bandGains = {0.0f, 0.0f, 0.0f, 0.0f};
    // TODO: Not sure what should happen if multiple bands are soloed and one of them is also muted...
    
    // BAND 1
    if ((eqState.bandMutes[0] || eqState.bandSolos[1] || eqState.bandSolos[2] || eqState.bandSolos[3]) && !eqState.bandSolos[0])
        bandGains.set(0, 0.0f);
    else
        bandGains.set(0, eqState.bandGains[0]);
    
    // BAND 2
    if ((eqState.bandMutes[1] || eqState.bandSolos[0] || eqState.bandSolos[2] || eqState.bandSolos[3]) && !eqState.bandSolos[1])
        bandGains.set(1, 0.0f);
    else
        bandGains.set(1, eqState.bandGains[1]);
    
    // BAND 3
    if ((eqState.bandMutes[2] || eqState.bandSolos[0] || eqState.bandSolos[1] || eqState.bandSolos[3]) && !eqState.bandSolos[2])
        bandGains.set(2, 0.0f);
    else
        bandGains.set(2, eqState.bandGains[2]);
    
    // BAND 4
    if ((eqState.bandMutes[3] || eqState.bandSolos[0] || eqState.bandSolos[1] || eqState.bandSolos[2]) && !eqState.bandSolos[3])
        bandGains.set(3, 0.0f);
    else
        bandGains.set(3, eqState.bandGains[3]);
    
    DBG("Applied eq gains: | 1: " << bandGains[0] << " | 2: " << bandGains[1] << " | 3: " << bandGains[2] << " | 4: " << bandGains[3]);
    
    eq.setBandGains(bandGains);
}

juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout() {
    auto layout = juce::AudioProcessorValueTreeState::ParameterLayout();
    
    // TODO: Add all parameters
    layout.add (std::make_unique<AudioParameterBool> (ParameterID("MuteBand1", 1), "Mute Band 1", false));
    
    return layout;
}
