/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "RedBox.h"
#include "ChannelStripComponent.h"
#include "PresetMenuComponent.h"

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

  void bindChannelStrip (ChannelStripComponent& strip, int band);

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    HelloWorldAudioProcessor& audioProcessor;

    Slider gainSlider;
    ComboBox comboBox;
    TextButton textButton { "Start" };
    ToggleButton bypassToggleButton;
    
    ChannelStripComponent channelStrip1;
    ChannelStripComponent channelStrip2;
    ChannelStripComponent channelStrip3;
    ChannelStripComponent channelStrip4;
    
    PresetMenuComponent presetMenu;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HelloWorldAudioProcessorEditor)
};


