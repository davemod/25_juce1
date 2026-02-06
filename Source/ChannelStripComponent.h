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
    ChannelStripComponent(AudioProcessorValueTreeState& state, int band);
    ~ChannelStripComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    
    Button& getMuteButton() { return muteButton; }
    Button& getSoloButton() { return soloButton; }
    Slider& getLevelFader() { return levelFader; }
    
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ChannelStripComponent)
    
    Slider levelFader;
    TextButton soloButton;
    TextButton muteButton;
    
    AudioProcessorValueTreeState::SliderAttachment levelAttachment;
    AudioProcessorValueTreeState::ButtonAttachment soloAttachment;
    AudioProcessorValueTreeState::ButtonAttachment muteAttachment;
};
