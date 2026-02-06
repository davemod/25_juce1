

#include "PluginEditor.h"
#include "PluginProcessor.h"
#include "Identifiers.h"

#define MYMACRO DBG("My Macro Print")

HelloWorldAudioProcessorEditor::HelloWorldAudioProcessorEditor(
    HelloWorldAudioProcessor &p)
    : AudioProcessorEditor(&p), audioProcessor(p), presetMenu(p.getApvts())
{
  setResizable(true, true);

  APVTS &apvts = audioProcessor.getApvts();

  for (int i = 0; i < ProjectConstants::numBands; i++)
  {
    auto channelStrip = channelStrips.add(new ChannelStripComponent(apvts, i));
    addAndMakeVisible(channelStrip);

  }

  addAndMakeVisible(bypassToggleButton);
  addAndMakeVisible(presetMenu);

  bypassToggleButton.setTitle("Bypass");
  bypassToggleButton.setButtonText("Bypass");

  //setWantsKeyboardFocus(true);

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
  for (int i = 0; i < ProjectConstants::numBands; i++)
  {
    channelStrips[i]->setBounds(area.removeFromLeft(channelStripWidth));
  }
}

/*
bool HelloWorldAudioProcessorEditor::keyPressed (const juce::KeyPress& key)
{
  // Check if the key pressed is the Spacebar
  if (key.getKeyCode() == juce::KeyPress::spaceKey)
  {
    DBG("A space bar has been presserino");
    return false;
  }
  return true;
}
*/