#pragma once

#include <JuceHeader.h>


/*
Vererbung in C++ bedeutet, dass eine Klasse (die sogenannte abgeleitete Klasse) Eigenschaften 
und Methoden einer anderen Klasse (der Basisklasse) übernimmt. Dadurch kann man gemeinsame 
Funktionalitäten in der Basisklasse definieren und in den abgeleiteten Klassen wiederverwenden 
oder anpassen. 

Polymorphismus ermöglicht es, dass man mit einem Zeiger oder einer Referenz auf 
die Basisklasse verschiedene abgeleitete Klassen ansprechen kann. So kann man z.B. eine Liste 
von Instrumenten verwalten und trotzdem für jedes Instrument die passende play()-Methode 
aufrufen, auch wenn sie unterschiedlich implementiert ist.
*/


// Basisklasse Instrument
class Instrument
{
public:
    virtual ~Instrument() = default;
    virtual void play() const = 0; // rein virtuelle Methode
    virtual juce::String getName() const = 0;
};

// Abstrakte Klasse für Blechblasinstrumente
class BrassInstrument : public Instrument
{
public:
    void cleanMouthpiece() const
    {
        DBG("Mundstück gereinigt.");
    }
};

// Abstrakte Klasse für Streichinstrumente
class StringInstrument : public Instrument
{
public:
    void changeString(int stringNumber)
    {
        DBG("Saite " << stringNumber << " gewechselt.");
    }
};

// Konkrete Klasse für Posaune
class Trombone : public BrassInstrument
{
public:
    void play() const override
    {
        DBG("Die Posaune spielt einen tiefen Ton.");
    }
    juce::String getName() const override
    {
        return "Trombone";
    }
};

// Konkrete Klasse für Cello
class Cello : public StringInstrument
{
public:
    void play() const override
    {
        DBG("Das Cello spielt eine warme Melodie.");
    }
    juce::String getName() const override
    {
        return "Cello";
    }
};


// Beispielklasse, die ein OwnedArray<Instrument> verwendet
class Orchestra
{
public:
    Orchestra()
    {
        // Fügt ein Cello und eine Posaune hinzu
        instruments.add(new Cello());
        instruments.add(new Trombone());
    }

    void perform() const
    {
        for (auto* instrument : instruments)
        {
            juce::String name = instrument->getName();
            DBG(name);
            // Erwartete Ausgabe:
            // 1. "Cello"
            // 2. "Trombone"

            instrument->play();
            // Erwartete Ausgabe:
            // 1. "Das Cello spielt eine warme Melodie."
            // 2. "Die Posaune spielt einen tiefen Ton."
        }
    }

private:
    juce::OwnedArray<Instrument> instruments;
};