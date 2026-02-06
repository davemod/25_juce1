/*
  ==============================================================================

    ChannelStrip.h
    Created: 19 Nov 2025 9:38:05am
    Author:  eddoard

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

using APVTS = AudioProcessorValueTreeState;

//==============================================================================
/*
*/
class ChannelStripComponent  : public juce::Component
{
public:
    ChannelStripComponent(APVTS& state, int band);
    ~ChannelStripComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    
    std::function<void(float value)> onFaderValueChange;
    std::function<void(bool isOn)> onMuteChanged;
    std::function<void(bool isOn)> onSoloChanged;
    
    void setFaderValue(float value);
    void setMuteButtonState(bool isOn);
    void setSoloButtonState(bool isOn);
    
    bool isSoloActive();
    bool isMuteActive();
    
private:
    APVTS& state;
    
    Slider levelFader;
    TextButton soloButton;
    TextButton muteButton;
    
    APVTS::SliderAttachment levelAttachment;
    APVTS::ButtonAttachment soloAttachment;
    APVTS::ButtonAttachment muteAttachment;
    
    
    
    // 1. attachments reinbringen für levelFader, soloButton, muteButton
    // 2. übergebe im ctor das band und erstelle daraus die jeweiligen parameterids für die attachments
    // 3. cleanup, wir brauchen kein onSoloChanged, onFaderValueChange etc mehr.
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ChannelStripComponent)
};
