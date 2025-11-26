/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


#define MYMACRO DBG("My Macro Print")

//==============================================================================
HelloWorldAudioProcessorEditor::HelloWorldAudioProcessorEditor (HelloWorldAudioProcessor& p)
:
AudioProcessorEditor (&p),
audioProcessor (p),
gainSlider()
{
    setResizable(true, true);
    
    addAndMakeVisible (gainSlider);
    addAndMakeVisible (textButton);
    addAndMakeVisible (comboBox);
    addAndMakeVisible (bypassToggleButton);
    addAndMakeVisible (channelStrip1);
    addAndMakeVisible (channelStrip2);
    addAndMakeVisible (presetMenu);
    
    addAndMakeVisible(redBox);
    addAndMakeVisible(greenBox);
    
    textButton.setColour (TextButton::buttonColourId, Colours::purple);
    textButton.setColour (TextButton::textColourOffId, Colours::black);
    textButton.setColour (TextButton::textColourOnId, Colours::white);
    textButton.setClickingTogglesState(true);
    
    bypassToggleButton.setTitle("Bypass");
    bypassToggleButton.setButtonText("Bypass");

    // Nothing selected - Text
    comboBox.setTextWhenNothingSelected("Select Preset");

    // Add items
    comboBox.addItem ("Cool Gain Slider", 1);
    comboBox.addItem ("Groovy Bypass Toggle", 2);
    comboBox.addItem ("Funky Clicky Textbutton", 3);
    comboBox.addItem ("Awesome ComboBox", 4);

    // Optionally set a default selection:
    comboBox.setSelectedId (0);

    gainSlider.setSliderStyle (Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    gainSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, false, 100, 10);
    
    setSize (500, 400);
    setResizeLimits(300, 200, INT_MAX, INT_MAX);
}

HelloWorldAudioProcessorEditor::~HelloWorldAudioProcessorEditor()
{
    DBG ("~PluginEditor ()");
}

//==============================================================================
void HelloWorldAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
}

void HelloWorldAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    auto area = getLocalBounds();
    auto channelStripWidth = area.getWidth()/5;
    
    presetMenu.setBounds(area.removeFromTop(30));
    
    channelStrip1.setBounds (area.removeFromLeft (channelStripWidth));
    channelStrip2.setBounds (area.removeFromLeft (channelStripWidth));
    
    redBox.setBounds(area.removeFromLeft (channelStripWidth));
    greenBox.setBounds(area.removeFromLeft (channelStripWidth));
}
