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
audioProcessor (p)
{    
    setResizable(true, true);
    setSize (500, 400);
    
    addAndMakeVisible(channelStrip1);
    
    DBG ("PluginEditor ()");
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
    // g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void HelloWorldAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

    auto bounds = getLocalBounds ();
    auto channelStripWidth = bounds.getWidth()/4;
    
    channelStrip1.setBounds(bounds.removeFromLeft(channelStripWidth));
    
    
}
