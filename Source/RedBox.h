//
// Created by hannes on 11/14/25.
//

#pragma once

#include <JuceHeader.h>
//#include <juce_gui_basics/components/juce_Component.h>

class ColouredBox : public Component
{
public:
    // fülle den hintergrund mit colour (member variable)
    void paint (Graphics& g) override;

    // speichere newColour im member colour
    void setBoxColour (Colour newColour);

private:
    Colour colour;
};

class RedBox : public ColouredBox {
public:
    RedBox () { setBoxColour (Colours::red); } // Ist ein Construktor!
};

class BlueBox : public ColouredBox {
public:
    BlueBox () { setBoxColour (Colours::blue); } // Ist ein Construktor!
};

class GreenBox : public ColouredBox {
public:
    GreenBox () { setBoxColour (Colours::green); } // Ist ein Construktor!
};