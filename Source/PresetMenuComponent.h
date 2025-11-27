/*
  ==============================================================================

    PresetMenuComponent.h
    Created: 21 Nov 2025 9:42:48am
    Author:  David Hill

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

// TODO 2
// Stell die PresetMenuComponent fertig, sodass sie alle Buttons und das Label richtig anzeigt und positioniert. Füge sie PluginEditor hinzu und positioniere sie am oberen Rand.

// TODO 3 - advanced
// Beim klicken auf loadButton / saveButton soll sich ein juce::FileChooser öffnen.

// TODO 4 - advanced
// Schreibe und lese tatsächliche Dateien
//hallo 
class PresetMenuComponent : public Component
{
public:
    PresetMenuComponent ();
    ~PresetMenuComponent () override;
    
    // 1 was gibt die funktion zurück? 2 wie heißt die funktion? 3 welche argumente bekommt die funktion übergeben? 4 Überschreibt die Funktion eine Funktion aus Component?
    void resized () override;
    void paint (juce::Graphics&) override;
    
private:
    
    // 1. WAS willst du haben? -> TextButton; 2. was soll der button für einen NAMEN haben? -> bspw. loadButton
    TextButton loadButton;
    TextButton saveButton;
    TextButton nextButton;
    TextButton previousButton;
    
    Label currentPresetLabel;
};
