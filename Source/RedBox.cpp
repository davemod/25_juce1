/*
  ==============================================================================

    RedBox.cpp
    Created: 14 Nov 2025 10:00:37am
    Author:  David Hill

  ==============================================================================
*/

#include "RedBox.h"

void ColouredBox::paint(Graphics& g)
{
    g.fillAll(colour);
}

void ColouredBox::setBoxColour(Colour newColour)
{
    colour = newColour;
}

RedBox::RedBox()
{
    setBoxColour(Colours::red);
}

GreenBox::GreenBox()
{
    setBoxColour(Colours::green);
}


BlueBox::BlueBox()
{
    setBoxColour(Colours::blue);
}



