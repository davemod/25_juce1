/*
  ==============================================================================

    PresetMenuComponent.h
    Created: 21 Nov 2025 9:42:48am
    Author:  David Hill

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

// TODO 1
// Implementiere openLoadFileChooser und openSaveFileChooser

// TODO 2 (advanced)
// Schreibe und lese tatsächliche Dateien

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
    TextButton loadButton{ "L" };
    TextButton saveButton{ "S" };
    TextButton nextButton{ ">" };
    TextButton previousButton{ "<" };
    
    Label currentPresetLabel{ "PresetLabel", "PRESET" };
    
    std::unique_ptr<FileChooser> fileChooser;
    void openLoadFileChooser ();
    void openSaveFileChooser ();
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PresetMenuComponent)
};



/** LAMBDA FUNKTION
 1. capture list, 2. parameters, 3. function body
 [this] (int x, int y) { }
 
 // lambda example
 auto func = []() {
     DBG ("LAMBDA CALLED");
 };
 
 // lambda ausführen
 func ();

 */
