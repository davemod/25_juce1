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
    auto area = getLocalBounds();
    //area.removeFromLeft = area.getHeight();
    loadButton.setBounds(area.removeFromLeft(area.getHeight()).reduced(1));
    previousButton.setBounds(area.removeFromLeft(area.getHeight()).reduced(1));
    saveButton.setBounds(area.removeFromRight(area.getHeight()).reduced(1));
    nextButton.setBounds(area.removeFromRight(area.getHeight()).reduced(1));
    
    
    
}

void PresetMenuComponent::paint (Graphics& g)
{
    g.fillAll(Colours::blue);
    g.setColour(Colours::darkred);

}
