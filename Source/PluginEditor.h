/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

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
    Slider gainSlider;
    ComboBox selectComboBox;
    TextButton clickTextButton { "Start" } ;
    ToggleButton bypassToggleButton;

    // TODO:
    // Erstellt ebenso eine juce::ComboBox, einen juce::TextButton, einen juce::ToggleButton.
    // Fügt sie dem UI hinzu, findet ein halbwegs ansprechendes Layout :)
    // Individualisiere einige Eigenschaften, Farben etc der einzelnen Components (Tutorium, wenn ihr einen Termin findet)

    // Advanced:
    // Erstellen eigener Components, bspw. eine Klasse, die einfach nur den gesamten Bereich rot färbt!


    // Übersicht über mögliche juce Components findet ihr hier:
    // https://docs.juce.com/master/classjuce_1_1Component.html

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HelloWorldAudioProcessorEditor)
};


