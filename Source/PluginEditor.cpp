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
    
    gainSlider.setSliderStyle (Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    gainSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, false, 100, 20);

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

    g.setColour (juce::Colours::white);
    g.setFont (juce::FontOptions (15.0f));
    g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void HelloWorldAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    
//    Rectangle<int> bounds = getLocalBounds ();
//    auto bounds = getLocalBounds ();
//    auto centre = bounds.getCentre();
//    DBG ("Centre: " << centre.getX () << ", " << centre.getY ());
    
    gainSlider.centreWithSize (200, 200);
}
