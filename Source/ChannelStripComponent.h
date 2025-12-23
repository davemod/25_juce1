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

    std::function<void(bool isOn)> onMuteChanged;
    
    bool getIsMuteActive();
    
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
    
    std::function<void(float value)> onFaderValueChange;
    std::function<void(bool isOn)> onMuteChanged;
    
    void setFaderValue(float value);
    
    bool isSoloActive();
    bool isMuteActive();
    
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ChannelStripComponent)
    
    ChannelStripButtonsComponent buttons;
    Slider levelFader;
};
