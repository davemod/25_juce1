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
  bindChannelStrip (channelStrip1, 0);
  bindChannelStrip (channelStrip2, 1);
  bindChannelStrip (channelStrip3, 2);
  bindChannelStrip (channelStrip4, 3);
    addAndMakeVisible (presetMenu);
    
    // APPLY STATE TO UI
    EQState state = audioProcessor.getEqState();

  channelStrip1.setFaderValue (juce::Decibels::gainToDecibels(state.bandGains[0]));
  channelStrip1.setMuteButtonState(state.bandMute[0]);
  channelStrip1.setSoloButtonState(state.bandSolo[0]);

  channelStrip2.setFaderValue (juce::Decibels::gainToDecibels(state.bandGains[1]));
  channelStrip2.setMuteButtonState(state.bandMute[1]);
  channelStrip2.setSoloButtonState(state.bandSolo[1]);

  channelStrip3.setFaderValue (juce::Decibels::gainToDecibels(state.bandGains[2]));
  channelStrip3.setMuteButtonState(state.bandMute[2]);
  channelStrip3.setSoloButtonState(state.bandSolo[2]);

  channelStrip4.setFaderValue (juce::Decibels::gainToDecibels(state.bandGains[3]));
  channelStrip4.setMuteButtonState(state.bandMute[3]);
  channelStrip4.setSoloButtonState(state.bandSolo[3]);

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

void HelloWorldAudioProcessorEditor::bindChannelStrip (ChannelStripComponent& strip, int channel)
{
  strip.onFaderValueChange = [this, channel](float dB)
  {
    audioProcessor.setEqGain(
      channel,
      juce::Decibels::decibelsToGain(dB)
      );
  };

  strip.onMuteChanged = [this, channel](bool isOn)
  {
    audioProcessor.muteBand(channel, isOn);
  };
  strip.onSoloChanged = [this, channel](bool isOn)
  {
    audioProcessor.soloBand(channel, isOn);
  };
}

