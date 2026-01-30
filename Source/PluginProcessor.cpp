/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <algorithm>


//==============================================================================
HelloWorldAudioProcessor::HelloWorldAudioProcessor()
     : AudioProcessor (BusesProperties()
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true))
    , state(*this, nullptr, "STATE", createParameterLayout ())
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

juce::AudioProcessorEditor* HelloWorldAudioProcessor::createEditor() {
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

const EQState& HelloWorldAudioProcessor::getEqState() const noexcept
{
  return eqState;
}


void HelloWorldAudioProcessor::setEqGain(int band, float value)
{
    if ( band < 4 && band >= 0)
    {
        eqState.bandGains[band] = value;
    }
    else
    {
        DBG("tf how'd you find this band!?");
    }
    applyEQState();
}

void HelloWorldAudioProcessor::muteBand(int band, bool isMute) {
    if ( band < 4 && band >= 0)
    {
        eqState.bandMute[band] = isMute;
    }
    else
    {
        DBG("muteBand: No such Eq band: " << band);
    }
    applyEQState();
}

void HelloWorldAudioProcessor::soloBand(int band, bool isSolo)
{
  if ( band < 4 && band >= 0)
  {
    eqState.bandSolo[band] = isSolo;
  }
  else
  {
    DBG("soloBand: No such Eq band: " << band);
  }
   applyEQState();
}


void HelloWorldAudioProcessor::applyEQState()
{
    //Array<float> bandGains = bandGains;
    // TODO: Not sure what should happen if multiple bands are soloed and one of them is also muted...

  const bool anySolo =
    std::any_of(std::begin(eqState.bandSolo),
                std::end(eqState.bandSolo),
                [](bool b) { return b; });



  int eqChannels = sizeof(eqState.bandGains) / sizeof(eqState.bandGains[0]);
  for (int i = 0; i < eqChannels; ++i)
  {
    auto gain = eqState.bandGains[i];
    if (anySolo)
    {
      // Solo mode active
      if (!eqState.bandSolo[i])
        gain = 0.0f;
        DBG("Check how I solo them on band " << i);
    }
    else
    {
      // No solo → mute logic
      if (eqState.bandMute[i])
        gain = 0.0f;
        DBG("We mute now on band " << i);
    }
    eq.setBandGain(i, gain);
  }
}

APVTS::ParameterLayout HelloWorldAudioProcessor::createParameterLayout()
{
    APVTS::ParameterLayout layout;
    
    layout.add (std::make_unique<AudioParameterBool> (ParameterID  ("MuteBand1", 1), "Mute Band 1", false));
    layout.add (std::make_unique<AudioParameterBool> (ParameterID  ("MuteBand2", 1), "Mute Band 2", false));
    layout.add (std::make_unique<AudioParameterBool> (ParameterID  ("MuteBand3", 1), "Mute Band 3", false));
    layout.add (std::make_unique<AudioParameterBool> (ParameterID  ("MuteBand4", 1), "Mute Band 4", false));
    
    layout.add (std::make_unique<AudioParameterBool> (ParameterID  ("SoloBand1", 1), "Solo Band 1", false));
    layout.add (std::make_unique<AudioParameterBool> (ParameterID  ("SoloBand2", 1), "Solo Band 2", false));
    layout.add (std::make_unique<AudioParameterBool> (ParameterID  ("SoloBand3", 1), "Solo Band 3", false));
    layout.add (std::make_unique<AudioParameterBool> (ParameterID  ("SoloBand4", 1), "Solo Band 4", false));
    
    NormalisableRange<float> gainRange{ -64.f, 24.f, 0.01f };
    gainRange.setSkewForCentre(0.f);
    
    layout.add (std::make_unique<AudioParameterFloat> (ParameterID  ("GainBand1", 1), "Gain Band 1", gainRange, 0.f));
    layout.add (std::make_unique<AudioParameterFloat> (ParameterID  ("GainBand2", 1), "Gain Band 2", gainRange, 0.f));
    layout.add (std::make_unique<AudioParameterFloat> (ParameterID  ("GainBand3", 1), "Gain Band 3", gainRange, 0.f));
    layout.add (std::make_unique<AudioParameterFloat> (ParameterID  ("GainBand4", 1), "Gain Band 4", gainRange, 0.f));
    
    return layout;
}
