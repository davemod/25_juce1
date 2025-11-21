/*
  ==============================================================================

    ChannelStripComponent.cpp
    Created: 21 Nov 2025 9:43:09am
    Author:  Niklas Achauer

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ChannelStripComponent.h"

//==============================================================================
ChannelStripComponent::ChannelStripComponent()
{
    muteButton.setButtonText("M");
    soloButton.setButtonText("S");
    
    gainSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBarVertical);
    
    addAndMakeVisible(muteButton);
    addAndMakeVisible(soloButton);
    addAndMakeVisible(gainSlider);
}

ChannelStripComponent::~ChannelStripComponent()
{
}

void ChannelStripComponent::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::white);
    g.setFont (juce::FontOptions (14.0f));
}

void ChannelStripComponent::resized()
{
    
    auto bounds = getLocalBounds();
    auto buttonBounds = bounds.removeFromTop(30);
    
    muteButton.setBounds(buttonBounds.removeFromLeft(buttonBounds.getWidth()/2));
    soloButton.setBounds(buttonBounds);
    
    gainSlider.setBounds(bounds);
}
