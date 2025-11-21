//
// Created by hannes on 11/14/25.
//

#include "RedBox.h"

void ColouredBox::paint(Graphics& g)
{
    //g.fillAll(Colours::); ///Was muss hier rein???
    Colour colour;
}

void ColouredBox::setBoxColour (Colour newColour)
{
    colour = newColour;
    repaint (); //muss bei Veränderung neu gezeichnet werden!
}



