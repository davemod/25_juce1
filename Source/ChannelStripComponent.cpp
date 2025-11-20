//
// Created by hannes on 11/20/25.
//

#include "ChannelStripComponent.h"

void ChannelStripComponent::paint(Graphics& g) {

    setSize(250,400);

    //g.fillAll(Colours::yellow);

    addAndMakeVisible (muteButton);
    muteButton.setColour (TextButton::buttonColourId, Colours::red);
    muteButton.setColour (TextButton::textColourOffId, Colours::black);
    muteButton.setColour (TextButton::textColourOnId, Colours::white);
    muteButton.setClickingTogglesState(true);
    muteButton.setBounds(200, 10, 25, 25);


    addAndMakeVisible (soloButton);
    soloButton.setColour (TextButton::buttonColourId, Colours::yellow);
    soloButton.setColour (TextButton::textColourOffId, Colours::black);
    soloButton.setColour (TextButton::textColourOnId, Colours::white);
    soloButton.setClickingTogglesState(true);
    soloButton.setBounds(200, 45, 25, 25);

    addAndMakeVisible (mainSlider);
    mainSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, false, 100, 10);
    mainSlider.setSliderStyle(Slider::SliderStyle::LinearBarVertical);
    mainSlider.setBounds(100, 10, 50, 380);



}