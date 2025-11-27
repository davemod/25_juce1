//
// Created by hannes on 11/20/25.
//

#pragma once

#include <JuceHeader.h>

class ChannelStripComponent  : public juce::Component {
public:
    ChannelStripComponent (); // CTOR / Constructor
    ~ChannelStripComponent() = default;

    void resized() = default;

private:
    juce::Slider mainSlider;
    TextButton muteButton { "M" } ;
    TextButton soloButton { "S" };
    //ToggleButton bypassToggleButton;
};
