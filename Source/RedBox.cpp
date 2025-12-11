/*
  ==============================================================================

    RedBox.cpp
    Created: 14 Nov 2025 10:00:37am
    Author:  David Hill

  ==============================================================================
*/

#include "RedBox.h"

void ColouredBox::paint (Graphics& g)
{
    g.fillAll(colour);
}

void ColouredBox::setBoxColour(Colour newColour)
{
    this->colour = newColour;
    repaint();
}

// Definition der Funktion RedBox::paint. Deklariert wird sie in der RedBox.h. Wichtig: hier wird kein override benötigt.
RedBox::RedBox ()
{
    setBoxColour(juce::Colours::red);
}

RedBox::~RedBox() {}

GreenBox::GreenBox ()
{
    setBoxColour(juce::Colours::green);
}

GreenBox::~GreenBox() {}

BlueBox::BlueBox ()
{
    setBoxColour(juce::Colours::blue);
}

BlueBox::~BlueBox() {}
