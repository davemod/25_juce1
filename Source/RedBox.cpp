/*
  ==============================================================================

    RedBox.cpp
    Created: 14 Nov 2025 10:00:37am
    Author:  David Hill

  ==============================================================================
*/

#include "RedBox.h"

RedBox::RedBox () { setBoxColour (Colours::red); }
GreenBox::GreenBox () { setBoxColour (Colours::green); }
BlueBox::BlueBox () { setBoxColour (Colours::blue); }
PinkBox::PinkBox () { setBoxColour (Colours::pink); }
WhiteBox::WhiteBox () { setBoxColour (Colours::whitesmoke); }
BlackBox::BlackBox () { setBoxColour (Colours::black); }
PurpleBox::PurpleBox () { setBoxColour (Colours::purple); }
OrangeBox::OrangeBox () { setBoxColour (Colours::orangered); }

void ColouredBox::paint (Graphics& g)
{
    g.fillAll (colour);
}

void ColouredBox::setBoxColour (Colour newColour)
{
    colour = newColour;
    repaint ();
}
