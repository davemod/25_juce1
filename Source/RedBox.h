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


// TODO 1 : Erstellen der Definitionen von paint und setBoxColour.
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

// TODO 2 : Ändere die Klasse RedBox so, dass sie von ColouredBox ableitet.
// TODO 3 : Erstelle eine Klasse GreenBox und BlueBox die wiederum von ColouredBox ableiten und die entsprechende Farbe zeichnen.

// Deklaration einer eigenen Klasse, die von juce::Component ableitet.
class RedBox : public ColouredBox
{
public:
    // Überschreiben der Funktion paint. Sie bekommt eine Referenz zu einem Objekt der Klasse Graphics. In der RedBox.h deklarieren wir lediglich die Funktion. Für die Definition, s. RedBox.cpp
    RedBox();
};

class GreenBox : public ColouredBox
{
public:
    // Überschreiben der Funktion paint. Sie bekommt eine Referenz zu einem Objekt der Klasse Graphics. In der RedBox.h deklarieren wir lediglich die Funktion. Für die Definition, s. RedBox.cpp
    GreenBox();
};


class BlueBox : public ColouredBox
{
public:
    // Überschreiben der Funktion paint. Sie bekommt eine Referenz zu einem Objekt der Klasse Graphics. In der RedBox.h deklarieren wir lediglich die Funktion. Für die Definition, s. RedBox.cpp
    BlueBox();
};


