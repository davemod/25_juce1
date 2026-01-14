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
    
    addAndMakeVisible (bypassToggleButton);
    addAndMakeVisible (channelStrips[0]);
    addAndMakeVisible (channelStrips[1]);
    addAndMakeVisible (channelStrips[2]);
    addAndMakeVisible (channelStrips[3]);
    addAndMakeVisible (presetMenu);
    
    // APPLY STATE TO UI
    EQState state = audioProcessor.getEqState();
    
    for (int i = 0; i < sizeof(channelStrips); i++)
    {
        // Initialize UI state
        channelStrips[i].setFaderValue(state.bandGains[i]);
        channelStrips[i].setMuteButtonState(state.bandMutes[i]);
        channelStrips[i].setSoloButtonState(state.bandSolos[i]);
        
        // UI Callbacks
        channelStrips[i].onFaderValueChange = [=](float value)
        {
            auto gain = juce::Decibels::decibelsToGain(value);
            audioProcessor.setEqGain(i, gain);
        };
        
        channelStrips[i].onMuteChanged = [=](bool isOn)
        {
            if (isOn == audioProcessor.getEqState().bandMutes[i]) { return; }
            audioProcessor.setMuteBand(i, isOn);
        };
        
        channelStrips[i].onSoloChanged = [=](bool isOn)
        {
            if (isOn == audioProcessor.getEqState().bandSolos[i]) { return; }
            audioProcessor.setSoloBand(i, isOn);
        };
    }
    
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
    
    channelStrips[0].setBounds (area.removeFromLeft (channelStripWidth));
    channelStrips[1].setBounds (area.removeFromLeft (channelStripWidth));
    channelStrips[2].setBounds (area.removeFromLeft (channelStripWidth));
    channelStrips[3].setBounds (area.removeFromLeft (channelStripWidth));
}
