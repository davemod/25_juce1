/*
  ==============================================================================

    ChannelStrip.h
    Created: 19 Nov 2025 9:38:05am
    Author:  eddoard

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

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
    
    void setFaderValue(float value);
    void setMuteButtonState(bool isOn);
    void setSoloButtonState(bool isOn);
    
    Button& getMuteButton() { return muteButton; }
    Button& getSoloButton() { return soloButton; }
    Slider& getLevelFader() { return levelFader; }
    
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ChannelStripComponent)
    
    Slider levelFader;
    TextButton soloButton;
    TextButton muteButton;
};
