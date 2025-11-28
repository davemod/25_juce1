/*
  ==============================================================================

    PresetMenuComponent.cpp
    Created: 21 Nov 2025 9:42:48am
    Author:  David Hill

  ==============================================================================
*/

#include "PresetMenuComponent.h"

PresetMenuComponent::PresetMenuComponent ()
{
    // addAndMakeVisible der ganze Buttons
    DBG ("Preset Menu Component Created");
    
    // erstellen einer buttonClicked Methode
    auto loadButtonClicked = [this](){
        DBG ("LOAD CLICKED");
        openLoadFileChooser();
    };

    // speichern der buttonClickFunktion in der onClick Methode eines buttons
    loadButton.onClick = loadButtonClicked;
    saveButton.onClick = [this]()
    {
        DBG ("SAVE CLICKED");
        openSaveFileChooser();
    };
    
    addAndMakeVisible(loadButton);
    addAndMakeVisible(saveButton);
    addAndMakeVisible(nextButton);
    addAndMakeVisible(previousButton);
    addAndMakeVisible(currentPresetLabel);
}

PresetMenuComponent::~PresetMenuComponent ()
{
    DBG ("Preset Menu Component Destroyed");
}

// 1. was gibt die funktion zurück? 2. zu welcher klasse gehört die funktion? 3. wie heißt die funktion? 4. was für argumente hat die funktion?
void PresetMenuComponent::resized ()
{
    auto area = getLocalBounds ();
    DBG ("Width 1: " << area.getWidth());

//  Rectangle::removeFromLeft macht sozusagen das hier:
//    auto amountToRemove = area.getHeight ();
//    const Rectangle r (area.getX () /*x*/, area.getY () /*x*/, jmin (amountToRemove, area.getWidth ()) /*width*/, area.getHeight () /*height*/);
//    area.setX (area.getX () + r.getWidth ());
//    area.setWidth (area.getWidth() - r.getWidth());
    
    auto reduceFactor{ (10) };
    
    loadButton.setBounds (area.removeFromLeft (area.getHeight()).reduced (reduceFactor));
    DBG ("Width 2: " << area.getWidth());
    
    previousButton.setBounds (area.removeFromLeft (area.getHeight()).reduced (reduceFactor));
    DBG ("Width 3: " << area.getWidth());
    
    saveButton.setBounds(area.removeFromRight(area.getHeight ()).reduced (reduceFactor));
    DBG ("Width 4: " << area.getWidth());
    
    nextButton.setBounds (area.removeFromRight(area.getHeight ()).reduced (reduceFactor));
    DBG ("Width 5: " << area.getWidth());
    
    currentPresetLabel.setBounds (area.reduced (reduceFactor));
}

void PresetMenuComponent::paint (Graphics& g)
{
    g.fillAll (juce::Colours::red);
}

void PresetMenuComponent::openLoadFileChooser()
{
    // TODO
}

void PresetMenuComponent::openSaveFileChooser()
{
    // TODO
}


