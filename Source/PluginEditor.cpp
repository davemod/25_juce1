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
    
    // APPLY STATE TO UI
    EQState state = audioProcessor.getEqState();
    
    channelStrip1.setFaderValue(state.bandGains[0]);
    channelStrip2.setFaderValue(state.bandGains[1]);
    channelStrip3.setFaderValue(state.bandGains[2]);
    channelStrip4.setFaderValue(state.bandGains[3]);
    
    channelStrip1.setMuteButtonState(state.bandMutes[0]);
    channelStrip1.setSoloButtonState(state.bandSolos[0]);
    
    channelStrip2.setMuteButtonState(state.bandMutes[1]);
    channelStrip2.setSoloButtonState(state.bandSolos[1]);
    
    channelStrip3.setMuteButtonState(state.bandMutes[2]);
    channelStrip3.setSoloButtonState(state.bandSolos[2]);
    
    channelStrip4.setMuteButtonState(state.bandMutes[3]);
    channelStrip4.setSoloButtonState(state.bandSolos[3]);
    
    // UI CALLBACKS
    // TODO: Find a way to define these functions only once (one for onFaderValueChange, one for onMuteChanged, onSoloChanged)
    channelStrip1.onFaderValueChange = [this](float value)
    {
        auto gain = juce::Decibels::decibelsToGain(value);
        audioProcessor.setEqGain(0, gain);
    };
    
    channelStrip1.onMuteChanged = [this](bool isOn)
    {
        if (isOn == audioProcessor.getEqState().bandMutes[0]) { return; }
        audioProcessor.setMuteBand(0, isOn);
    };
    
    channelStrip1.onSoloChanged = [this](bool isOn)
    {
        if (isOn == audioProcessor.getEqState().bandSolos[0]) { return; }
        audioProcessor.setSoloBand(0, isOn);
    };
    
    channelStrip2.onFaderValueChange = [this](float value)
    {
        auto gain = juce::Decibels::decibelsToGain(value);
        audioProcessor.setEqGain(1, gain);
    };
    
    channelStrip2.onMuteChanged = [this](bool isOn)
    {
        if (isOn == audioProcessor.getEqState().bandMutes[1]) { return; }
        audioProcessor.setMuteBand(1, isOn);
    };
    
    channelStrip2.onSoloChanged = [this](bool isOn)
    {
        if (isOn == audioProcessor.getEqState().bandSolos[1]) { return; }
        audioProcessor.setSoloBand(1, isOn);
    };
    
    channelStrip3.onFaderValueChange = [this](float value)
    {
        auto gain = juce::Decibels::decibelsToGain(value);
        audioProcessor.setEqGain(2, gain);
    };
    
    channelStrip3.onMuteChanged = [this](bool isOn)
    {
        if (isOn == audioProcessor.getEqState().bandMutes[2]) { return; }
        audioProcessor.setMuteBand(2, isOn);
    };
    
    channelStrip3.onSoloChanged = [this](bool isOn)
    {
        if (isOn == audioProcessor.getEqState().bandSolos[2]) { return; }
        audioProcessor.setSoloBand(2, isOn);
    };
    
    channelStrip4.onFaderValueChange = [this](float value)
    {
        auto gain = juce::Decibels::decibelsToGain(value);
        audioProcessor.setEqGain(3, gain);
    };
    
    channelStrip4.onMuteChanged = [this](bool isOn)
    {
        if (isOn == audioProcessor.getEqState().bandMutes[3]) { return; }
        audioProcessor.setMuteBand(3, isOn);
    };
    
    channelStrip4.onSoloChanged = [this](bool isOn)
    {
        if (isOn == audioProcessor.getEqState().bandSolos[3]) { return; }
        audioProcessor.setSoloBand(3, isOn);
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
