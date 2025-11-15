/*
  ==============================================================================

    ColouredBox.cpp
    Created: 14 Nov 2025 9:49:46am
    Author:  eddoard

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ColouredBox.h"

//==============================================================================
ColouredBox::ColouredBox()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

ColouredBox::~ColouredBox()
{
}

void ColouredBox::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (Colours::red);   // clear the background
}

void ColouredBox::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
