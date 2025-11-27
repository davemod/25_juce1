/*
  ==============================================================================

    RedBox.h
    Created: 14 Nov 2025 10:00:37am
    Author:  David Hill

  ==============================================================================
*/

#pragma once


// Der JuceHeader selbst includes wiederum sämtliche Module, die wir in unserem Projucer Projekt verwenden. So haben wir auch Zugriff auf die Klasse juce::Component
#include <JuceHeader.h>


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

// Deklaration einer eigenen Klasse, die von juce::Component ableitet.
class RedBox : public ColouredBox
{
public:
    RedBox ();
};

// Deklaration einer eigenen Klasse, die von juce::Component ableitet.
class GreenBox : public ColouredBox
{
public:
    GreenBox ();
};

// Deklaration einer eigenen Klasse, die von juce::Component ableitet.
class BlueBox : public ColouredBox
{
public:
    BlueBox ();
};

// TODO 1 Fünf weitere boxen mit verschiedene Farben die von ColouredBox ableiten

class OrangeBox : public ColouredBox
{
public:
    OrangeBox ();
    
};

class PurpleBox : public ColouredBox
{
public:
    PurpleBox ();
    
};

class BlackBox : public ColouredBox
{
public:
    BlackBox ();
    
};
class WhiteBox : public ColouredBox
{
public:
    WhiteBox ();
    
};
class PinkBox : public ColouredBox
{
public:
    PinkBox ();
    
};

