/*
  ==============================================================================

    ChannelStrip.cpp
    Created: 19 Nov 2025 9:38:05am
    Author:  eddoard

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ChannelStripComponent.h"

//==============================================================================
ChannelStripComponent::ChannelStripComponent(APVTS& state, int band)
:
state(state),
levelAttachment(state, "GainBand" + (String)band, levelFader),
soloAttachment(state, "SoloBand" + (String)band, soloButton),
muteAttachment(state, "MuteBand" + (String)band, muteButton)
{
    soloButton.setButtonText("s");
    soloButton.setClickingTogglesState(true);
    soloButton.setColour(TextButton::buttonOnColourId, Colours::blue);
//    soloButton.onClick = [this] ()
//    {
//        if (onSoloChanged) {
//            onSoloChanged(soloButton.getToggleState());
//        }
//    };
    addAndMakeVisible(soloButton);
    
    muteButton.setButtonText("m");
    muteButton.setClickingTogglesState(true);
    muteButton.setColour(TextButton::buttonOnColourId, Colours::darkorange);
//    muteButton.onClick = [this] ()
//    {
//        if (onMuteChanged) {
//            onMuteChanged(muteButton.getToggleState());
//        }
//    };
    addAndMakeVisible(muteButton);
    
//    levelFader.setRange(-69.0, 6);
//    levelFader.setTextValueSuffix(" dB");
//    levelFader.setValue(0.0);
//    levelFader.setDoubleClickReturnValue(true, 0.0);
    levelFader.setSliderStyle(Slider::SliderStyle::LinearVertical);
    levelFader.setColour(Slider::textBoxTextColourId, Colours::black);
    levelFader.setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxBelow, false, 70, 20);
//  levelFader.setNumDecimalPlacesToDisplay(2);
//    levelFader.onValueChange = [this] {
//        if(onFaderValueChange) {
//            onFaderValueChange(levelFader.getValue());
//        }
//    };
    addAndMakeVisible(levelFader);
    
    setSize(50, 500);
}

ChannelStripComponent::~ChannelStripComponent()
{
}

void ChannelStripComponent::setFaderValue(float value) {
//    levelFader.setValue(value);
}

void ChannelStripComponent::setMuteButtonState(bool isOn) {
//    muteButton.setToggleState(isOn, NotificationType::dontSendNotification);
}

void ChannelStripComponent::setSoloButtonState(bool isOn) {
//    soloButton.setToggleState(isOn, NotificationType::dontSendNotification);
}

void ChannelStripComponent::paint (juce::Graphics& g)
{
    g.fillAll (Colours::beige);   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::black);
    g.setFont (juce::FontOptions (14.0f));
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
