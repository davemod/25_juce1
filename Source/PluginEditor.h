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

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    HelloWorldAudioProcessor& audioProcessor;

    Slider gainSlider;
    ComboBox comboBox;
    TextButton textButton { "Start" };
    ToggleButton bypassToggleButton;
    
    juce::OwnedArray<ChannelStripComponent> channelStrips;
    
    juce::OwnedArray<AudioProcessorValueTreeState::ButtonAttachment> soloButtonAttachments;
    juce::OwnedArray<AudioProcessorValueTreeState::ButtonAttachment> muteButtonAttachments;
    juce::OwnedArray<AudioProcessorValueTreeState::SliderAttachment> levelFaderAttachments;
    
    PresetMenuComponent presetMenu;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HelloWorldAudioProcessorEditor)
};


