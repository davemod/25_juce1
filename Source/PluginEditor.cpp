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
    
    channelStrip1.setFaderValue(state.band1Gain);
    channelStrip2.setFaderValue(state.band2Gain);
    channelStrip3.setFaderValue(state.band3Gain);
    channelStrip4.setFaderValue(state.band4Gain);
    
    channelStrip1.setMuteButtonState(state.band1Mute);
    channelStrip1.setSoloButtonState(state.band1Solo);
    
    channelStrip2.setMuteButtonState(state.band2Mute);
    channelStrip2.setSoloButtonState(state.band2Solo);
    
    channelStrip3.setMuteButtonState(state.band3Mute);
    channelStrip3.setSoloButtonState(state.band3Solo);
    
    channelStrip4.setMuteButtonState(state.band4Mute);
    channelStrip4.setSoloButtonState(state.band4Solo);
    
    // UI CALLBACKS
    channelStrip1.onFaderValueChange = [this](float value) {
        auto gain = juce::Decibels::decibelsToGain(value);
        audioProcessor.setEqGain(0, gain);
    };
    
    channelStrip1.onMuteChanged = [this](bool isOn) {
        if (isOn) { audioProcessor.muteBand(0); }
        else { audioProcessor.unmuteBand(0); }
    };
    
    channelStrip1.onSoloChanged = [this](bool isOn) {
        if (isOn) { audioProcessor.soloBand(0); }
        else { audioProcessor.unsoloBand(0); }
    };
    
    channelStrip2.onFaderValueChange = [this](float value) {
        auto gain = juce::Decibels::decibelsToGain(value);
        audioProcessor.setEqGain(1, gain);
    };
    
    channelStrip2.onMuteChanged = [this](bool isOn) {
        if (isOn) { audioProcessor.muteBand(1); }
        else { audioProcessor.unmuteBand(1); }
    };
    
    channelStrip2.onSoloChanged = [this](bool isOn) {
        if (isOn) { audioProcessor.soloBand(1); }
        else { audioProcessor.unsoloBand(1); }
    };
    
    channelStrip3.onFaderValueChange = [this](float value) {
        auto gain = juce::Decibels::decibelsToGain(value);
        audioProcessor.setEqGain(2, gain);
    };
    
    channelStrip3.onMuteChanged = [this](bool isOn) {
        if (isOn) { audioProcessor.muteBand(2); }
        else { audioProcessor.unmuteBand(2); }
    };
    
    channelStrip3.onSoloChanged = [this](bool isOn) {
        if (isOn) { audioProcessor.soloBand(2); }
        else { audioProcessor.unsoloBand(2); }
    };
    
    channelStrip4.onFaderValueChange = [this](float value) {
        auto gain = juce::Decibels::decibelsToGain(value);
        audioProcessor.setEqGain(3, gain);
    };
    
    channelStrip4.onMuteChanged = [this](bool isOn) {
        if (isOn) { audioProcessor.muteBand(3); }
        else { audioProcessor.unmuteBand(3); }
    };
    
    channelStrip4.onSoloChanged = [this](bool isOn) {
        if (isOn) { audioProcessor.soloBand(3); }
        else { audioProcessor.unsoloBand(3); }
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
