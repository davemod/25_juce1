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

// Step 3 - Variablen in Form eines Structs zum Speichern der Stände anlegen (Muss kein struct sein, ergibt aber Sinn, wenn man mehrere Variablen speichern möchte und es für mehrere ChannelStrips nutzen möchte)
struct BandState
{
    // std::atomic<float> gain { 1.0f }; // optional, da schon separat implementiert (siehe TODO 4 unten)
    std::atomic<bool> mute { false };
    std::atomic<bool> solo { false };
};

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
    void setLowGain (float g)     { lowGain.store (g); }
    void setLowMidGain (float g)  { lowMidGain.store (g); }
    void setHighMidGain (float g) { highMidGain.store (g); }
    void setHighGain (float g)    { highGain.store (g); }

    //Getter
    float getLowGain() const     { return lowGain.load(); }
    float getLowMidGain() const  { return lowMidGain.load(); }
    float getHighMidGain() const { return highMidGain.load(); }
    float getHighGain() const    { return highGain.load(); }


    // Step 5 - setter Methoden für die States anlegen

    void setLowMute     (bool m) { low.mute.store(m);};
    void setLowMidMute  (bool m) { lowMid.mute.store(m);};
    void setHighMidMute (bool m) { highMid.mute.store(m);};
    void setHighMute    (bool m) { high.mute.store(m);};

    // SOLO SETTER
    void setLowSolo     (bool s) { low.solo.store (s); }
    void setLowMidSolo  (bool s) { lowMid.solo.store (s); }
    void setHighMidSolo (bool s) { highMid.solo.store (s); }
    void setHighSolo    (bool s) { high.solo.store (s); }



private:
    // Deklaration einer Funktion
    // 1. Rückgabetyp (juce::AudioProcessorEditor*)
    // 2. Funktionsname (createCrashingEditor)
    // 3. Innerhalb der Klammern Argumente
    juce::AudioProcessorEditor* createCrashsAndLeaks ();
    // TODO 1
    LinearPhaseFourBandEQ lpfbEQ;
    // TODO 4
    // Step 3.1 change values to atomics because of thread safety
    std::atomic<float> lowGain     = 1.0f;
    std::atomic<float> lowMidGain  = 1.0f;
    std::atomic<float> highMidGain = 1.0f;
    std::atomic<float> highGain    = 1.0f;

    // Step 4 - Bandstates als Membervariable hinzufügen
    BandState low, lowMid, highMid, high;

    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HelloWorldAudioProcessor)
};
