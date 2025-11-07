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

    
    // gainSlider.setVisible (true);
    // addChildComponent (gainSlider);
    addAndMakeVisible (gainSlider);
    addAndMakeVisible (textButton);
    addAndMakeVisible (comboBox);
    addAndMakeVisible (toggleButton);
    
    gainSlider.setSliderStyle (Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    gainSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, false, 100, 20);

    textButton.setButtonText("TextButton");
    
    DBG ("PluginEditor ()");
    
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    
    // Make also sure to call this after you've added all your components using addAndMakeVisible.
    setSize (400, 300);
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
    
//    Rectangle<int> bounds = getLocalBounds ();
//    auto bounds = getLocalBounds ();
//    auto centre = bounds.getCentre();
//    DBG ("Centre: " << centre.getX () << ", " << centre.getY ());
    
    FlexBox fb;
    FlexBox col1;
    FlexBox col2;
    
    col1.justifyContent = FlexBox::JustifyContent::spaceAround;
    col1.alignContent = FlexBox::AlignContent::center;
    col1.flexDirection = FlexBox::Direction::column;
    col1.flexWrap = FlexBox::Wrap::noWrap;
    col1.items.addArray({
        FlexItem(toggleButton).withMinHeight(25),
        FlexItem(textButton).withMinHeight(50),
        FlexItem(comboBox).withMinHeight(25)
    });
    
    col2.justifyContent = FlexBox::JustifyContent::center;
    col2.alignContent = FlexBox::AlignContent::center;
    col2.flexDirection = FlexBox::Direction::column;
    col2.items.add(FlexItem(gainSlider).withFlex(2.5));
    
    fb.flexDirection = FlexBox::Direction::row;
    fb.flexWrap = FlexBox::Wrap::noWrap;
    fb.justifyContent = FlexBox::JustifyContent::spaceAround;
    fb.items.add(FlexItem(col1).withFlex(1).withMinWidth(50));
    fb.items.add(FlexItem(col2).withFlex(3).withMinWidth(200));
    
    fb.performLayout (getLocalBounds());
}
