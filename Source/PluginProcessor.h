/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "LinearPhaseFourBandEQ.h"

// TODO 1: include LinearPhaseFourBandEQ.h and create instance
// TODO 4: create four variables to store the gain of each band
// TODO 5: create a setter and getter method, to set each of these values
//
//==============================================================================
/**
*/
class HelloWorldAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    HelloWorldAudioProcessor();
    ~HelloWorldAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    void setLowGain (float gain) { lowGain = gain; }
    float getLowGain () { return lowGain; }
    
    void setLowMidGain (float gain) { lowMidGain = gain; }
    float getLowMidGain () { return lowMidGain; }
    
    void setHighMidGain (float gain) { highMidGain = gain; }
    float getHighMidGain () { return highMidGain; }
    
    void setHighGain (float gain) { highGain = gain; }
    float getHighGain () { return highGain; }
    
private:
    // Deklaration einer Funktion
    // 1. Rückgabetyp (juce::AudioProcessorEditor*)
    // 2. Funktionsname (createCrashingEditor)
    // 3. Innerhalb der Klammern Argumente
    juce::AudioProcessorEditor* createCrashsAndLeaks ();
    LinearPhaseFourBandEQ eq;
    
    float lowGain{ 1.f };
    float lowMidGain{ 1.f };
    float highMidGain{ 1.f };
    float highGain{ 1.f };
    
    bool muteLowGain{ false };
    bool muteLowMidGain{ false };
    bool muteHighMidGain{ false };
    bool muteHighGain{ false };
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HelloWorldAudioProcessor)
};
