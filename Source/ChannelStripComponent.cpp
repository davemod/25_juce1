
#include "ChannelStripComponent.h"
#include <JuceHeader.h>
#include "HelloWorldParameterIDs.h"

//==============================================================================
ChannelStripComponent::ChannelStripComponent(AudioProcessorValueTreeState& state, int band)
  :
levelAttachment(state, HelloWorldParameterID::bandGain (band), levelFader),
muteAttachment(state, HelloWorldParameterID::bandMute (band), muteButton),
soloAttachment(state, HelloWorldParameterID::bandSolo (band), soloButton)
{
  soloButton.setButtonText("s");
  soloButton.setClickingTogglesState(true);
  soloButton.setColour(TextButton::buttonOnColourId, Colours::blue);
  addAndMakeVisible(soloButton);

  muteButton.setButtonText("m");
  muteButton.setClickingTogglesState(true);
  muteButton.setColour(TextButton::buttonOnColourId, Colours::darkorange);
  addAndMakeVisible(muteButton);

  levelFader.setRange(-69.0, 6);
  levelFader.setTextValueSuffix(" dB");
  levelFader.setValue(0.0);
  levelFader.setDoubleClickReturnValue(true, 0.0);
  levelFader.setSliderStyle(Slider::SliderStyle::LinearVertical);
  levelFader.setColour(Slider::textBoxTextColourId, Colours::black);
  levelFader.setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxBelow, false,
                             70, 20);
  addAndMakeVisible(levelFader);

  setSize(50, 500);
}

ChannelStripComponent::~ChannelStripComponent() {}

void ChannelStripComponent::setFaderValue(float value)
{
  levelFader.setValue(value);
}

void ChannelStripComponent::setMuteButtonState(bool isOn)
{
  muteButton.setToggleState(isOn, NotificationType::dontSendNotification);
}

void ChannelStripComponent::setSoloButtonState(bool isOn)
{
  soloButton.setToggleState(isOn, NotificationType::dontSendNotification);
}

void ChannelStripComponent::paint(juce::Graphics &g)
{
  g.fillAll(Colours::beige); // clear the background

  g.setColour(juce::Colours::grey);
  g.drawRect(getLocalBounds(), 1); // draw an outline around the component

  g.setColour(juce::Colours::black);
  g.setFont(juce::FontOptions(14.0f));
}

void ChannelStripComponent::resized()
{
  auto area = getLocalBounds();
  auto buttonHeight = 40;
  auto buttonsArea = area.removeFromTop(buttonHeight);
  auto buttonsWidth = buttonsArea.getWidth() / 2;

  soloButton.setBounds(buttonsArea.removeFromLeft(buttonsWidth));
  muteButton.setBounds(buttonsArea.removeFromRight(buttonsWidth));
  area.removeFromBottom(10);
  levelFader.setBounds(area.removeFromBottom(area.getHeight() - buttonHeight));
}
