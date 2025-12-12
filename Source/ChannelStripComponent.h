/*
  ==============================================================================

    ChannelStrip.h
    Created: 19 Nov 2025 9:38:05am
    Author:  eddoard

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class ChannelStripButtonsComponent  : public juce::Component
{
public:
    ChannelStripButtonsComponent();
    ~ChannelStripButtonsComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ChannelStripButtonsComponent)
    
    TextButton soloButton;
    TextButton muteButton;
};

//==============================================================================
/*
*/
class ChannelStripComponent  : public juce::Component
{
public:
    ChannelStripComponent();
    ~ChannelStripComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    // TODO 7, create an std::function<void(float level)> onLevelChanged;
    // TODO 8, set onValueChanged from your PluginEditor constructor
    // Bsp: channeStrip1.onValueChanged = [&] (float sliderValue) { /* set the corresponding band gain on audio processor */ }
    
    
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ChannelStripComponent)
    
    ChannelStripButtonsComponent buttons;
    Slider levelFader;
};
