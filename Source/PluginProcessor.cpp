/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
HelloWorldAudioProcessor::HelloWorldAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
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

EQState HelloWorldAudioProcessor::getEqState() {
    return eqState;
}

void HelloWorldAudioProcessor::setEqGain(int band, float value) {
    switch (band) {
        case 0:
            eqState.band1Gain = value;
            break;
        case 1:
            eqState.band2Gain = value;
            break;
        case 2:
            eqState.band3Gain = value;
            break;
        case 3:
            eqState.band4Gain = value;
            break;
        default:
            DBG("setEqGain: No such Eq band: " << band);
            break;
    }
    
    applyEQState();
}

void HelloWorldAudioProcessor::muteBand(int band) {
    switch (band) {
        case 0:
            eqState.band1Mute = true;
            break;
        case 1:
            eqState.band2Mute = true;
            break;
        case 2:
            eqState.band3Mute = true;
            break;
        case 3:
            eqState.band4Mute = true;
            break;
        default:
            DBG("muteBand: No such Eq band: " << band);
            break;
    }
    
    applyEQState();
}

void HelloWorldAudioProcessor::unmuteBand(int band) {
    switch (band) {
        case 0:
            eqState.band1Mute = false;
            break;
        case 1:
            eqState.band2Mute = false;
            break;
        case 2:
            eqState.band3Mute = false;
            break;
        case 3:
            eqState.band4Mute = false;
            break;
        default:
            DBG("unmuteBand: No such Eq band: " << band);
            break;
    }
    
    applyEQState();
}

void HelloWorldAudioProcessor::soloBand(int band) {
    switch (band) {
        case 0:
            eqState.band1Solo = true;
            break;
        case 1:
            eqState.band2Solo = true;
            break;
        case 2:
            eqState.band3Solo = true;
            break;
        case 3:
            eqState.band4Solo = true;
            break;
        default:
            DBG("soloBand: No such Eq band: " << band);
            break;
    }
    
    applyEQState();
}

void HelloWorldAudioProcessor::unsoloBand(int band) {
    switch (band) {
        case 0:
            eqState.band1Solo = false;
            break;
        case 1:
            eqState.band2Solo = false;
            break;
        case 2:
            eqState.band3Solo = false;
            break;
        case 3:
            eqState.band4Solo = false;
            break;
        default:
            DBG("unsoloBand: No such Eq band: " << band);
            break;
    }
    
    applyEQState();
}

void HelloWorldAudioProcessor::applyEQState() {
    Array<float> bandGains = {0.0f, 0.0f, 0.0f, 0.0f};
    // TODO: Not sure what should happen if multiple bands are soloed and one of them is also muted...
    
    // BAND 1
    if ((eqState.band1Mute || eqState.band2Solo || eqState.band3Solo || eqState.band4Solo) && !eqState.band1Solo)
        bandGains.set(0, 0.0f);
    else
        bandGains.set(0, eqState.band1Gain);
    
    // BAND 2
    if ((eqState.band2Mute || eqState.band1Solo || eqState.band3Solo || eqState.band4Solo) && !eqState.band2Solo)
        bandGains.set(1, 0.0f);
    else
        bandGains.set(1, eqState.band2Gain);
    
    // BAND 3
    if ((eqState.band3Mute || eqState.band1Solo || eqState.band2Solo || eqState.band4Solo) && !eqState.band3Solo)
        bandGains.set(2, 0.0f);
    else
        bandGains.set(2, eqState.band3Gain);
    
    // BAND 4
    if ((eqState.band4Mute || eqState.band1Solo || eqState.band2Solo || eqState.band3Solo) && !eqState.band4Solo)
        bandGains.set(3, 0.0f);
    else
        bandGains.set(3, eqState.band4Gain);
    
    DBG("Applied eq gains: 1: " << bandGains[0] << " 2: " << bandGains[1] << " 3: " << bandGains[2] << " 4: " << bandGains[3]);
    
    eq.setBandGains(bandGains);
}
