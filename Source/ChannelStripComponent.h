/*
  ==============================================================================

    ChannelStrip.h
    Created: 19 Nov 2025 9:38:05am
    Author:  eddoard

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class ChannelStripComponent  : public juce::Component
{
public:
    ChannelStripComponent();
    ~ChannelStripComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    // DONE 7, create an std::function<void(float level)> onLevelChanged;
    // DONE 8, set onLevelChanged from your PluginEditor constructor

    std::function<void(float level)> onLevelChanged; // Hier die Function
    void init (float level) {levelFader.setValue (level, dontSendNotification);}

    std::function<void (bool)> onMuteChanged;
    std::function<void (bool)> onSoloChanged;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ChannelStripComponent)

    Slider levelFader;
    TextButton muteButton;
    TextButton soloButton;
};
