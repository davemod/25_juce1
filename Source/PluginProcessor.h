/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
//TODO 1
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


    // TODO 5
    //Setter
    void setLowGain (float g);
    void setLowMidGain (float g);
    void setHighMidGain (float g);
    void setHighGain (float g);
    //Getter
    float getLowGain() const;
    float getLowMidGain() const;
    float getHighMidGain() const;
    float getHighGain() const;

private:
    // Deklaration einer Funktion
    // 1. Rückgabetyp (juce::AudioProcessorEditor*)
    // 2. Funktionsname (createCrashingEditor)
    // 3. Innerhalb der Klammern Argumente
    juce::AudioProcessorEditor* createCrashsAndLeaks ();
    // TODO 1
    LinearPhaseFourBandEQ lpfbEQ;
    // TODO 4
    float lowGain     = 1.0f;
    float lowMidGain  = 1.0f;
    float highMidGain = 1.0f;
    float highGain    = 1.0f;
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HelloWorldAudioProcessor)
};
