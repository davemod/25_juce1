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

    // RedBox redBox;
    // BlueBox blueBox;
    // GreenBox greenBox;
    
    ChannelStripComponent channelStrip1;
    ChannelStripComponent channelStrip2;
    ChannelStripComponent channelStrip3;
    ChannelStripComponent channelStrip4;
    
    PresetMenuComponent presetMenu;
    
    // Individualisiere einige Eigenschaften, Farben etc der einzelnen Components (Tutorium, wenn ihr einen Termin findet)

    // Advanced:
    // Erstellen eigener Components, bspw. eine Klasse, die einfach nur den gesamten Bereich rot färbt!

    // class ChannelStripComponent, eine Klasse, die einen Slider, einen Solo und einen Mute Button darstellt.
    // Anzeigen von mindestens zwei ChannelStripComponents im PluginEditor
    
    // Übersicht über mögliche juce Components findet ihr hier:
    // https://docs.juce.com/master/classjuce_1_1Component.html

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HelloWorldAudioProcessorEditor)
};


