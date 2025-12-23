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
    addAndMakeVisible (channelStrip1);
    addAndMakeVisible (channelStrip2);
    addAndMakeVisible (channelStrip3);
    addAndMakeVisible (channelStrip4);
    addAndMakeVisible (presetMenu);
    
    Array<float> eqGains = audioProcessor.getEqGains();
    int arraySize = eqGains.size();
    
    if (arraySize > 0) {
        DBG("Setting fader 1 to " << eqGains[0]);
        channelStrip1.setFaderValue(eqGains[0]);
    }
    
    if (arraySize > 1) {
        DBG("Setting fader 2 to " << eqGains[1]);
        channelStrip2.setFaderValue(eqGains[1]);
    }
    
    if (arraySize > 2) {
        DBG("Setting fader 3 to " << eqGains[2]);
        channelStrip3.setFaderValue(eqGains[2]);
    }
    
    if (arraySize > 3) {
        DBG("Setting fader 4 to " << eqGains[3]);
        channelStrip4.setFaderValue(eqGains[3]);
    }
    
    channelStrip1.onFaderValueChange = [this](float value) {
        auto gain = juce::Decibels::decibelsToGain(value);
        audioProcessor.setEqGain(0, gain);
    };
    
    channelStrip2.onFaderValueChange = [this](float value) {
        auto gain = juce::Decibels::decibelsToGain(value);
        audioProcessor.setEqGain(1, gain);
    };
    
    channelStrip3.onFaderValueChange = [this](float value) {
        auto gain = juce::Decibels::decibelsToGain(value);
        audioProcessor.setEqGain(2, gain);
    };
    
    channelStrip4.onFaderValueChange = [this](float value) {
        auto gain = juce::Decibels::decibelsToGain(value);
        audioProcessor.setEqGain(3, gain);
    };
    
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
    
    channelStrip1.setBounds (area.removeFromLeft (channelStripWidth));
    channelStrip2.setBounds (area.removeFromLeft (channelStripWidth));
    channelStrip3.setBounds (area.removeFromLeft (channelStripWidth));
    channelStrip4.setBounds (area.removeFromLeft (channelStripWidth));
}
