

#include "PluginEditor.h"
#include "PluginProcessor.h"

#define MYMACRO DBG("My Macro Print")

HelloWorldAudioProcessorEditor::HelloWorldAudioProcessorEditor(
    HelloWorldAudioProcessor &p)
    : AudioProcessorEditor(&p), audioProcessor(p)
{
  setResizable(true, true);

  APVTS &apvts = audioProcessor.getApvts();

  for (int i = 0; i < numBands; i++)
  {
    auto channelStrip = channelStrips.add(new ChannelStripComponent(apvts, i));
    addAndMakeVisible(channelStrip);

    /*
    soloButtonAttachments.add(std::make_unique<APVTS::ButtonAttachment>(
        apvts, ID::bandSolo(i), channelStrips[i]->getSoloButton()));
    muteButtonAttachments.add(std::make_unique<APVTS::ButtonAttachment>(
        apvts, ID::bandMute(i), channelStrips[i]->getMuteButton()));
    levelFaderAttachments.add(std::make_unique<APVTS::SliderAttachment>(
        apvts, ID::bandGain(i), channelStrips[i]->getLevelFader()));
  */
  }

  addAndMakeVisible(bypassToggleButton);
  addAndMakeVisible(presetMenu);

  bypassToggleButton.setTitle("Bypass");
  bypassToggleButton.setButtonText("Bypass");

  setSize(500, 400);
  setResizeLimits(300, 200, 900, 600);
}

HelloWorldAudioProcessorEditor::~HelloWorldAudioProcessorEditor()
{
  DBG("~PluginEditor ()");
}

//==============================================================================
void HelloWorldAudioProcessorEditor::paint(juce::Graphics &g)
{
  // (Our component is opaque, so we must completely fill the background with a
  // solid color)
  g.fillAll(
      getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
}

void HelloWorldAudioProcessorEditor::resized()
{
  // This is generally where you'll want to lay out the positions of any
  // subcomponents in your editor.
  auto area = getLocalBounds();
  auto channelStripWidth = area.getWidth() / 4;

  presetMenu.setBounds(area.removeFromTop(30));

  // Trying something
  // will this cause issues with apvts?
  for (int i = 0; i < numBands; i++)
  {
    channelStrips[i]->setBounds(area.removeFromLeft(channelStripWidth));
  }
}
