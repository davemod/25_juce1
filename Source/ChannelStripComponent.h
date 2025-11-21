/*
  ==============================================================================

    ChannelStripComponent.h
    Created: 21 Nov 2025 9:43:09am
    Author:  Niklas Achauer

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

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ChannelStripComponent)
    
    TextButton soloButton;
    TextButton muteButton;
    Slider gainSlider;
};
