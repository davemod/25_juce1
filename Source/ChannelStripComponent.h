//
// Created by hannes on 11/20/25.
//

#pragma once

#include <JuceHeader.h>

class ChannelStripComponent  : public Component
{
public:
    ChannelStripComponent ();
    ~ChannelStripComponent() = default;
    void resized() override;
    //void openLoadFileChooser();

private:
    Slider mainSlider;
    TextButton muteButton { "M" } ;
    TextButton soloButton { "S" };
    //TextButton loadButton { "load" };
    //std::unique_ptr<juce::FileChooser> fileChooser;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ChannelStripComponent)
};
