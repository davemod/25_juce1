/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "LinearPhaseFourBandEQ.h"

// DONE 1: include LinearPhaseFourBandEQ.h and create instance
// DONE 4: create four variables to store the gain of each band
// DONE 5: create a setter and getter method, to set each of these values
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

    //Setter
    void setLowGain (float g);
    void setLowMidGain (float g);
    void setHighMidGain (float g);
    void setHighGain (float g);

    void setLowMute (bool m);
    void setLowMidMute (bool m);
    void setHighMidMute (bool m);
    void setHighMute (bool m);

    //Getter
    float getLowGain() const; // Die Variable vom letzten get kann nicht verändert werden. RETURN VALUE ist const, NICHT der Low Gain an sich.
    float getLowMidGain() const;
    float getHighMidGain() const;
    float getHighGain() const;

    bool getLowMute() const;
    bool getLowMidMute() const;
    bool getHighMidMute() const;
    bool getHighMute() const;

private:
    // Deklaration einer Funktion
    // 1. Rückgabetyp (juce::AudioProcessorEditor*)
    // 2. Funktionsname (createCrashingEditor)
    // 3. Innerhalb der Klammern Argumente
    juce::AudioProcessorEditor* createCrashsAndLeaks ();

    LinearPhaseFourBandEQ linearPhaseFourBandEQ; // Das ist eine Member-Variable!

    float lowGain = 1.0f;
    float lowMidGain = 1.0f;
    float highMidGain = 1.0f;
    float highGain = 1.0f;

    bool muteLowGain = false ;
    bool muteLowMidGain = false ;
    bool muteHighMidGain = false ;
    bool muteHighGain = false ;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HelloWorldAudioProcessor)
};
