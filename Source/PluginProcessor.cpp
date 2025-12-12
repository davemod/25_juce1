/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

// TODO 2: prepare linear phase filter
// TODO 3: call processBlock from linear phase filter
// TODO 6: call setBandGains and set the band gains using your getter methods

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
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
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

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);
        // ..do something to the data...
    }
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

// Definition einer Funktion
// 1. Rückgabetype (juce::AudioProcessorEditor*)
// 2. Wo ist die Funktion deklariert? (in der Klasse HelloWorldAudioProcessor)
// 3. Jetzt erst der Funktionsname
juce::AudioProcessorEditor* HelloWorldAudioProcessor::createCrashsAndLeaks()
{
    // Instanz von HelloWorldAudioProcessorEditor auf dem STACK
    HelloWorldAudioProcessorEditor instance1 (*this);

    // Erstellen einer Variable, die ein pointer ist, der pointer könnte auf eine Instanz zeigen
    HelloWorldAudioProcessorEditor * editorPtr = nullptr; // tut er aber noch nicht
    
    // erstellen einer neuen instanz auf dem Heap, editorPtr zeigt jetzt auf diese neue instanz
    editorPtr = new HelloWorldAudioProcessorEditor (*this);

    // erstellen NOCH EINE neue instanz und lassen den selben pointer auf die neue instanz zeigen. ziemlich doof.
    editorPtr = new HelloWorldAudioProcessorEditor (*this);
    
    // nur zugriff auf erste Instanz (instance1 liegt auf dem stack) und dritte Instanz (liegt auf dem heap)
    // die zweite instanz, liegt irgendwo, aber es zeigt nichts mehr drauf
    
    // erstellen eines dritten pointers, der auf instance1 zeit. instance1 ist ein Editor, der auf dem stack instanziiert wurde und nur bis zum ende dieses scopes lebt.
    HelloWorldAudioProcessorEditor * editorPtr3 = &instance1;
    
    // return eines pointers zu einem Objekt DAS GLEICH GELÖSCHT WIRD OJE
    return editorPtr3;
} // SCOPE ENDE



