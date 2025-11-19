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
    addAndMakeVisible (redBox);
    
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
    
    FlexBox fb;
    
    FlexBox header;
    FlexBox centerContent;
    FlexBox footer;

    header.justifyContent = FlexBox::JustifyContent::center;
    header.alignContent = FlexBox::AlignContent::flexStart;
    header.alignItems = FlexBox::AlignItems::stretch;
    header.flexDirection = FlexBox::Direction::row;
    header.items.addArray({
        FlexItem(comboBox)
            .withFlex(2)
            .withHeight(25.0f)
            .withWidth(200.0f)
            .withMargin(10.0f),
        
        FlexItem(bypassToggleButton)
            .withFlex(1)
            .withMinHeight(25.0f)
            .withMargin(10.0f),
    });
    
    centerContent.justifyContent = FlexBox::JustifyContent::spaceAround;
    centerContent.alignContent = FlexBox::AlignContent::center;
    centerContent.flexDirection = FlexBox::Direction::row;
    centerContent.flexWrap = FlexBox::Wrap::noWrap;
    centerContent.items.addArray({
        FlexItem(gainSlider).withMinHeight(100.0f).withFlex(2),
    });
    
    footer.justifyContent = FlexBox::JustifyContent::center;
    footer.alignContent = FlexBox::AlignContent::center;
    footer.flexDirection = FlexBox::Direction::row;
    footer.alignItems = FlexBox::AlignItems::stretch;
    footer.items.addArray({
        FlexItem(textButton).withFlex(1).withHeight(50.0f).withWidth(200.0f)
    });
    
    fb.flexDirection = FlexBox::Direction::column;
    fb.flexWrap = FlexBox::Wrap::noWrap;
    fb.justifyContent = FlexBox::JustifyContent::spaceBetween;
    fb.alignContent = FlexBox::AlignContent::spaceBetween;
    fb.alignItems = FlexBox::AlignItems::stretch;
    fb.items.addArray({
        FlexItem(header).withFlex(1).withMinWidth(50),
        FlexItem(centerContent).withFlex(3).withMinWidth(200),
        FlexItem(footer).withFlex(2).withMinWidth(200)
    });
    
    fb.performLayout (getLocalBounds());
}
