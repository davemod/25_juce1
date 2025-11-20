//
// Created by hannes on 11/20/25.
//

#pragma once

#include <JuceHeader.h>

class ChannelStripComponent  : public juce::Component {
public:
    //ChannelStripComponent (HelloWorldAudioProcessor&); // CTOR / Constructor
    //~ChannelStripComponent() override;

    // Little testfunction
    //void paint (Graphics& g) override;
    void paint (juce::Graphics&) override;
private:
    Slider mainSlider;
    TextButton muteButton { "M" } ;
    TextButton soloButton { "S" };
    //ToggleButton bypassToggleButton;
};
