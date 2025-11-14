//
//  ColourButton.h
//  Hello World
//
//  Created by eddoard on 06.11.25.
//

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class ColourButton  : public juce::Component
{
public:
    ColourButton (); // CTOR / Constructor
    ~ColourButton() override; // Destructor

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
};



