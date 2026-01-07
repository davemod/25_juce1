#include <JuceHeader.h>
#include "ChannelStripComponent.h"
ChannelStripComponent::ChannelStripComponent()
{
    // Configure solo button
    soloButton.setButtonText("s");
    soloButton.setClickingTogglesState(true);
    soloButton.setColour(TextButton::buttonOnColourId, Colours::blue);
    // Step 2 -> Callback definieren
    soloButton.onClick = [this] { 
        if (onSoloChanged)
        {
            onSoloChanged(soloButton.getToggleState());
        }
    };
    addAndMakeVisible(soloButton);
    
    // Configure mute button
    muteButton.setButtonText("m");
    muteButton.setClickingTogglesState(true);
    muteButton.setColour(TextButton::buttonOnColourId, Colours::darkorange);
    muteButton.onClick = [this] { 
        if (onMuteChanged)
        {
            onMuteChanged(muteButton.getToggleState());
        }
    };
    addAndMakeVisible(muteButton);
    // Configure level fader
    levelFader.setRange(-69.0, 6);
    levelFader.setTextValueSuffix(" dB");
    levelFader.setValue(0.0);
    levelFader.setSliderStyle(Slider::SliderStyle::LinearVertical);
    levelFader.setColour(Slider::textBoxTextColourId, Colours::black);
    levelFader.setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxBelow, false, 50, 20);
    levelFader.onValueChange = [this]() 
    {
        if (onLevelChanged)
            onLevelChanged((float) levelFader.getValue());
    };
    addAndMakeVisible(levelFader);
    setSize(50, 500);
}
ChannelStripComponent::~ChannelStripComponent()
{
}
void ChannelStripComponent::paint(juce::Graphics& g)
{
    g.fillAll(Colours::darkgrey);
    g.setColour(juce::Colours::beige);
    g.drawRect(getLocalBounds(), 1);
    g.setColour(juce::Colours::black);
    g.setFont(juce::FontOptions(14.0f));
}
void ChannelStripComponent::resized()
{
    auto area = getLocalBounds();
    auto buttonSize = 40;
    // Set bounds for the buttons
    auto margin = 5.0;
    area.removeFromTop(margin);
    area.removeFromBottom(margin);
    
    auto buttonWidth = (area.getWidth() - (margin * 2)) / 2;
    soloButton.setBounds(area.removeFromTop(buttonSize).removeFromLeft(buttonWidth));
    muteButton.setBounds(area.removeFromTop(buttonSize).removeFromRight(buttonWidth));
    
    // Set bounds for the level fader
    levelFader.setBounds(area.removeFromBottom(area.getHeight()));
}