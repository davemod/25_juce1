/*
  ==============================================================================

    RedBox.cpp
    Created: 14 Nov 2025 9:49:46am
    Author:  eddoard

  ==============================================================================
*/

#include <JuceHeader.h>
#include "RedBox.h"

//==============================================================================
RedBox::RedBox()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

RedBox::~RedBox()
{
}

void RedBox::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (Colours::red);   // clear the background
}

void RedBox::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
