/*
  ==============================================================================

    ColouredBox.h
    Created: 14 Nov 2025 9:49:46am
    Author:  eddoard

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class ColouredBox : public juce::Component
{
public:
    ColouredBox();
    ~ColouredBox() override;
    
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ColouredBox)
};
