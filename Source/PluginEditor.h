/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "RedBox.h"

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
    

    // TODO:
    // Erstellt ebenso eine juce::ComboBox, einen juce::TextButton, einen juce::ToggleButton.
    // Fügt sie dem UI hinzu, findet ein halbwegs ansprechendes Layout :)
    // Individualisiere einige Eigentschaften, Farben etc der einzelnen Components (Tutorium, wenn ihr einen Termin findet)
    ComboBox comboBox;
    TextButton textButton { "Start" };
    ToggleButton bypassToggleButton;
    
    RedBox redBox;
    
    // Individualisiere einige Eigenschaften, Farben etc der einzelnen Components (Tutorium, wenn ihr einen Termin findet)

    // Advanced:
    // Erstellen eigener Components, bspw. eine Klasse, die einfach nur den gesamten Bereich rot färbt!


    // Übersicht über mögliche juce Components findet ihr hier:
    // https://docs.juce.com/master/classjuce_1_1Component.html

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HelloWorldAudioProcessorEditor)
};


