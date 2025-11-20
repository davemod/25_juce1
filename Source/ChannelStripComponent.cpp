//
// Created by hannes on 11/20/25.
//

#include "ChannelStripComponent.h"

void ChannelStripComponent::paint(Graphics& g) {
    g.fillAll(Colours::yellow);

    addAndMakeVisible (muteButton);
    muteButton.setColour (TextButton::buttonColourId, Colours::red);
    muteButton.setColour (TextButton::textColourOffId, Colours::black);
    muteButton.setColour (TextButton::textColourOnId, Colours::white);
    muteButton.setClickingTogglesState(true);

    addAndMakeVisible (soloButton);
    soloButton.setColour (TextButton::buttonColourId, Colours::yellow);
    soloButton.setColour (TextButton::textColourOffId, Colours::black);
    soloButton.setColour (TextButton::textColourOnId, Colours::white);
    soloButton.setClickingTogglesState(true);

    addAndMakeVisible (mainSlider);

}