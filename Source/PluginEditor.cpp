/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

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
    addAndMakeVisible (redBox);
    
    textButton.setColour (TextButton::buttonColourId, Colours::purple);
    textButton.setColour (TextButton::textColourOffId, Colours::black);
    textButton.setColour (TextButton::textColourOnId, Colours::white);
    textButton.setClickingTogglesState(true);

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
    
    FlexBox fb;
    FlexBox col1;
    FlexBox col2;
    
    col1.justifyContent = FlexBox::JustifyContent::spaceAround;
    col1.alignContent = FlexBox::AlignContent::center;
    col1.flexDirection = FlexBox::Direction::column;
    col1.flexWrap = FlexBox::Wrap::noWrap;
    col1.items.addArray({
        FlexItem(bypassToggleButton).withMinHeight(25),
        FlexItem(redBox).withMinHeight(25).withMinWidth(25),
    });
    
    col2.justifyContent = FlexBox::JustifyContent::spaceBetween;
    col2.alignContent = FlexBox::AlignContent::center;
    col2.flexDirection = FlexBox::Direction::column;
    col2.items.add(FlexItem(comboBox).withFlex(1).withHeight(25).withWidth(200));
    col2.items.add(FlexItem(gainSlider).withFlex(2.5).withMinHeight(200));
    col2.items.add(FlexItem(textButton).withFlex(1).withHeight(50).withWidth(200));
    
    fb.flexDirection = FlexBox::Direction::row;
    fb.flexWrap = FlexBox::Wrap::noWrap;
    fb.justifyContent = FlexBox::JustifyContent::spaceAround;
    fb.items.add(FlexItem(col1).withFlex(1).withMinWidth(50));
    fb.items.add(FlexItem(col2).withFlex(3).withMinWidth(200));
    
    fb.performLayout (getLocalBounds());
}
