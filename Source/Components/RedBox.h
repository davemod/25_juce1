/*
  ==============================================================================

    RedBox.h
    Created: 14 Nov 2025 12:28:12pm
    Author:  eddoard

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "ColouredBox.h"

//==============================================================================
/*
*/
class RedBox : public ColouredBox
{
public:
    RedBox();
    ~RedBox() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (RedBox)
};
