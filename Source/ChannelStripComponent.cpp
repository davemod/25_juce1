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

    g.fillAll (Colours::sienna);

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
    soloButton.setButtonText("s");
    soloButton.setClickingTogglesState(true);
    soloButton.setColour(TextButton::buttonOnColourId, Colours::blue);
    addAndMakeVisible(soloButton);

    muteButton.setButtonText("m");
    muteButton.setClickingTogglesState(true);
    muteButton.setColour(TextButton::buttonOnColourId, Colours::darkorange);
    addAndMakeVisible(muteButton);
    //addAndMakeVisible(buttons);
    
    levelFader.setRange(-69.0, 6);
    levelFader.setTextValueSuffix(" dB");
    levelFader.setValue(0.0); // sollte er dann nicht setValue auf den letzten Value haben?
    levelFader.setSliderStyle(Slider::SliderStyle::LinearVertical);
    levelFader.setColour(Slider::textBoxTextColourId, Colours::black);
    levelFader.setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxBelow, false, 50, 20);
    addAndMakeVisible(levelFader);
    
//  DONE 9
    levelFader.onValueChange = [this]()
    {
        if (onLevelChanged) // Wenn wir onLevelChanged nicht nutzen, dann würde ein Crash passieren beim Nutzen!
            onLevelChanged (levelFader.getValue ());
    };

    muteButton.onClick = [this](){
        if (onMuteChanged) {
            onMuteChanged(muteButton.getToggleState());
        }
    };

    soloButton.onClick = [this](){
        if (onSoloChanged) {
            onSoloChanged(soloButton.getToggleState());
        }
    };

    
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