//
// Created by hannes on 11/21/25.
//

#include "PresetMenuComponent.h"

PresetMenuComponent::PresetMenuComponent ()
{
    addAndMakeVisible(loadButton);
    addAndMakeVisible(saveButton);
    addAndMakeVisible(nextButton);
    addAndMakeVisible(previousButton);

    DBG ("Preset Menu Component Created");
}

PresetMenuComponent::~PresetMenuComponent ()
{
    DBG ("Preset Menu Component Destroyed");
}

void PresetMenuComponent::resized() {

    auto bounds = getLocalBounds();
    int height = bounds.getY ();
    int width = bounds.getX ();

    loadButton.setBounds(0, 0, width / 8, height);
    previousButton.setBounds((width / 8) + 1, 0, width / 8, height);
    nextButton.setBounds((width / 4) * 3 + 1, 0, width / 8, height);
    saveButton.setBounds((width / 8 ) * 7 +1, 0, width / 8, height);

    //coole Dropdown Box machen für Presets! :)

}