//
// Created by hannes on 11/20/25.
//

#include "ChannelStripComponent.h"

ChannelStripComponent::ChannelStripComponent()
{
    //mainSlider.setSliderStyle(Slider::LinearVertical);
    mainSlider.setSliderStyle(Slider::SliderStyle::LinearBarVertical);
    mainSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 50, 20);
    addAndMakeVisible(mainSlider);

    muteButton.setButtonText("M");
    soloButton.setButtonText("S");

    muteButton.setClickingTogglesState(true);
    soloButton.setClickingTogglesState(true);

    muteButton.setColour (TextButton::buttonColourId, Colours::grey);
    muteButton.setColour (TextButton::buttonOnColourId, Colours::red);
    muteButton.setColour (TextButton::textColourOffId, Colours::black);
    muteButton.setColour (TextButton::textColourOnId, Colours::white);
    soloButton.setColour (TextButton::buttonColourId, Colours::grey);
    soloButton.setColour (TextButton::buttonOnColourId, Colours::yellow);
    soloButton.setColour (TextButton::textColourOffId, Colours::black);
    soloButton.setColour (TextButton::textColourOnId, Colours::black);

    addAndMakeVisible (muteButton);
    addAndMakeVisible (soloButton);
}

void ChannelStripComponent::resized()
{
    auto area = getLocalBounds().reduced(5); // pad away 5 at the borders

    //int buttonWidth = area.getWidth() / 4;
    // reserve space at the bottom for the buttons
    auto buttonsArea = area.removeFromRight(area.getWidth() / 4);

    // split the buttons area in two for mute and solo
    auto buttonWidth = buttonsArea.getWidth() / 2;
    //muteButton.setBounds(buttonsArea.removeFromLeft(buttonWidth).reduced(2));  // small margin
    //soloButton.setBounds(buttonsArea.reduced(2));
    muteButton.setBounds(buttonsArea.getX() + (buttonsArea.getWidth() / 2) - (buttonWidth / 2), buttonsArea.getY(), buttonWidth, buttonWidth);
    soloButton.setBounds(buttonsArea.getX() + (buttonsArea.getWidth() / 2) - (buttonWidth / 2), buttonsArea.getY()+ buttonWidth + (buttonsArea.getHeight() / 9), buttonWidth, buttonWidth);

    int sliderWidth = area.getWidth() / 2;
    // rest is slider
    mainSlider.setBounds(area.getWidth() / 2 - sliderWidth / 2, area.getY(), sliderWidth, area.getHeight());
    //loadButton.setBounds(area.removeFromLeft(buttonWidth * 2));

}