#pragma once
#include <JuceHeader.h>
class ChannelStripComponent : public juce::Component
{
public:
    ChannelStripComponent();
    ~ChannelStripComponent() override;
    void paint(juce::Graphics&) override;
    void resized() override;
    std::function<void(float level)> onLevelChanged;
    // Step 1 -> callback Funktionen für mute und solo anlegen
    std::function<void (bool)> onMuteChanged;
    std::function<void (bool)> onSoloChanged;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ChannelStripComponent)
    Slider levelFader;
    ToggleButton soloButton;
    ToggleButton muteButton;
};