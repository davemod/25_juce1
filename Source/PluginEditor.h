/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

#include "ChannelStripComponent.h"

//==============================================================================
/**
*/
class HelloWorldAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    HelloWorldAudioProcessorEditor (HelloWorldAudioProcessor&); // CTOR / Constructor
    ~HelloWorldAudioProcessorEditor() override; // Destructor

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    HelloWorldAudioProcessor& audioProcessor;

    //juce::Slider gainSlider;
    ChannelStripComponent channelStrip1;
    
    // TODO 4:
    // class ChannelStripComponent, eine Klasse, die einen Slider, einen Solo und einen Mute Button darstellt.
    // Anzeigen von mindestens zwei ChannelStripComponents im PluginEditor
    
    
    // Übersicht über mögliche juce Components findet ihr hier:
    // https://docs.juce.com/master/classjuce_1_1Component.html

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HelloWorldAudioProcessorEditor)
};


