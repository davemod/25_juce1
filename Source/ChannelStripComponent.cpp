/*
  ==============================================================================

    ChannelStrip.cpp
    Created: 19 Nov 2025 9:38:05am
    Author:  eddoard

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ChannelStripComponent.h"

ChannelStripButtonsComponent::ChannelStripButtonsComponent()
{
    soloButton.setButtonText("s");
    soloButton.setClickingTogglesState(true);
    soloButton.setColour(TextButton::buttonOnColourId, Colours::blue);
    addAndMakeVisible(soloButton);
    
    muteButton.setButtonText("m");
    muteButton.setClickingTogglesState(true);
    muteButton.setColour(TextButton::buttonOnColourId, Colours::darkorange);
    addAndMakeVisible(muteButton);
}

ChannelStripButtonsComponent::~ChannelStripButtonsComponent()
{}

void ChannelStripButtonsComponent::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (Colours::beige);

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::black);
    g.setFont (juce::FontOptions (14.0f));
}

void ChannelStripButtonsComponent::resized()
{
    auto area = getLocalBounds();
    auto margin = 5.0;
    area.removeFromTop(margin);
    area.removeFromLeft(margin);
    area.removeFromRight(margin);
    area.removeFromBottom(margin);

    auto buttonWidth = (area.getWidth() - margin) / 2;
    muteButton.setBounds(area.removeFromLeft(buttonWidth));
    soloButton.setBounds(area.removeFromRight(buttonWidth));
}

//==============================================================================
ChannelStripComponent::ChannelStripComponent()
{
    addAndMakeVisible(buttons);
    
    levelFader.setRange(-69.0, 6);
    levelFader.setTextValueSuffix(" dB");
    levelFader.setValue(0.0);
    levelFader.setSliderStyle(Slider::SliderStyle::LinearVertical);
    levelFader.setColour(Slider::textBoxTextColourId, Colours::black);
    levelFader.setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxBelow, false, 50, 20);
    addAndMakeVisible(levelFader);
    
//  TODO 9
//    levelFader.onValueChange = [this]() {
//        if (onLevelChanged)
//            onLevelChanged (levelFader.getValue ());
//    };
    
    
    setSize(50, 500);
}

ChannelStripComponent::~ChannelStripComponent()
{
}

void ChannelStripComponent::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (Colours::beige);   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::black);
    g.setFont (juce::FontOptions (14.0f));
}

void ChannelStripComponent::resized()
{
    auto area = getLocalBounds();
    auto buttonSize = 40;
    
    buttons.setBounds(area.removeFromTop(buttonSize));
    area.removeFromBottom(10);
    levelFader.setBounds(area.removeFromBottom(area.getHeight() - buttonSize));
}
