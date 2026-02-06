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
presetMenu (p.getApvts())
{
    setResizable(true, true);

    APVTS& apvts = audioProcessor.getApvts();
    
    for (int i = 0; i < audioProcessor.getNumEqBands(); i++)
    {
        auto channelStrip = channelStrips.add(new ChannelStripComponent(apvts, i));
        addAndMakeVisible (channelStrip);
    }
    
    addAndMakeVisible (bypassToggleButton);
    addAndMakeVisible (presetMenu);
    
    bypassToggleButton.setTitle("Bypass");
    bypassToggleButton.setButtonText("Bypass");
    
    setSize (500, 400);
    setResizeLimits(300, 200, 900, 600);
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
    auto channelStripWidth = area.getWidth()/4;
    
    presetMenu.setBounds(area.removeFromTop(30));
    
    channelStrips[0] -> setBounds (area.removeFromLeft (channelStripWidth));
    channelStrips[1] -> setBounds (area.removeFromLeft (channelStripWidth));
    channelStrips[2] -> setBounds (area.removeFromLeft (channelStripWidth));
    channelStrips[3] -> setBounds (area.removeFromLeft (channelStripWidth));
}
