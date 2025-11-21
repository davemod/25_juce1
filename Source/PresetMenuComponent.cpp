/*
  ==============================================================================

    PresetMenuComponent.cpp
    Created: 21 Nov 2025 10:00:36am
    Author:  Niklas Achauer

  ==============================================================================
*/

#include "PresetMenuComponent.h"


PresetMenuComponent::PresetMenuComponent(){
    loadButton.setButtonText("Load");
    saveButton.setButtonText("Save");
    nextButton.setButtonText(">");
    previousButton.setButtonText("<");
    
    currentPresetLabel.setText ("Prest #1", juce::dontSendNotification);
    currentPresetLabel.setColour (juce::Label::outlineColourId, juce::Colours::lightblue);
    
    addAndMakeVisible(loadButton);
    addAndMakeVisible(saveButton);
    addAndMakeVisible(nextButton);
    addAndMakeVisible(previousButton);
    addAndMakeVisible(currentPresetLabel);
}

PresetMenuComponent::~PresetMenuComponent()
{
}

void PresetMenuComponent::paint(Graphics& g){
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::cyan);
    g.drawRect (getLocalBounds(), 1);

    g.setColour (juce::Colours::white);
    g.setFont (juce::FontOptions (14.0f));
};

void PresetMenuComponent::resized(){
    
    
    auto bounds = getLocalBounds();
    int textButtonWidth = 100;
    int arrowButtonWidth = 32;
    
    loadButton.setBounds(bounds.removeFromLeft(textButtonWidth));
    saveButton.setBounds(bounds.removeFromRight(textButtonWidth));
    
    previousButton.setBounds(bounds.removeFromLeft(arrowButtonWidth));
    nextButton.setBounds(bounds.removeFromRight(arrowButtonWidth));
    
    currentPresetLabel.setBounds(bounds);
};
