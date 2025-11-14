/*
  ==============================================================================

    RedBox.h
    Created: 14 Nov 2025 9:49:46am
    Author:  eddoard

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class RedBox  : public juce::Component
{
public:
    RedBox();
    ~RedBox() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (RedBox)
};
