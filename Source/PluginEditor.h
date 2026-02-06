
#pragma once

#include "ChannelStripComponent.h"
#include "PluginProcessor.h"
#include "PresetMenuComponent.h"
#include <JuceHeader.h>

//==============================================================================
/**
 */
class HelloWorldAudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
  HelloWorldAudioProcessorEditor(
      HelloWorldAudioProcessor &);            // CTOR / Constructor
  ~HelloWorldAudioProcessorEditor() override; // Destructor

  //==============================================================================
  void paint(juce::Graphics &) override;
  void resized() override;

private:
  // This reference is provided as a quick way for your editor to
  // access the processor object that created it.
  HelloWorldAudioProcessor &audioProcessor;

  Slider gainSlider;
  ComboBox comboBox;
  TextButton textButton{"Start"};
  ToggleButton bypassToggleButton;

  juce::OwnedArray<ChannelStripComponent> channelStrips;

  /*
  juce::OwnedArray<APVTS::ButtonAttachment> soloButtonAttachments;
  juce::OwnedArray<APVTS::ButtonAttachment> muteButtonAttachments;
  juce::OwnedArray<APVTS::SliderAttachment> levelFaderAttachments;
*/

  PresetMenuComponent presetMenu;

  int numBands = audioProcessor.getNumEqBands();

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(HelloWorldAudioProcessorEditor)
};
