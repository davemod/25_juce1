/*
  ==============================================================================

    PresetMenuComponent.cpp
    Created: 21 Nov 2025 9:41:00am
    Author:  eddoard

  ==============================================================================
*/

#include <JuceHeader.h>
#include "PresetMenuComponent.h"

//==============================================================================
PresetMenuComponent::PresetMenuComponent()
{
    addAndMakeVisible(presetChooser);
    presetChooser.addItem("Supa Scoopa", 1);
    presetChooser.addItem("Flat", 2);
    presetChooser.addItem("Bob Marley's Bathroom", 3);
    presetChooser.addItem("Default", 4);
    presetChooser.setSelectedId(4);
    
    addAndMakeVisible(loadButton);
    loadButton.setButtonText("Load");
    loadButton.onClick = [this] { openLoadFileChooser(); };
    
    addAndMakeVisible(saveButton);
    saveButton.setButtonText("Save");
    
    addAndMakeVisible(nextButton);
    nextButton.setButtonText(">");
    
    addAndMakeVisible(previousButton);
    previousButton.setButtonText("<");
}

PresetMenuComponent::~PresetMenuComponent()
{
}

void PresetMenuComponent::openLoadFileChooser()
{
    auto presetFileChooser = std::make_unique<FileChooser> ("Load Preset...",
                                                   File::getCurrentWorkingDirectory(),
                                                   "*.json");
    
    auto folderChooserFlags = FileBrowserComponent::openMode;
     
    presetFileChooser->launchAsync (folderChooserFlags, [this] (const FileChooser& chooser)
    {
        File presetFile (chooser.getResult());
 
//        loadPresetFile (presetFile);
    });
}

void PresetMenuComponent::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::white);
    g.setFont (juce::FontOptions (14.0f));
}

void PresetMenuComponent::resized()
{
    auto area = getLocalBounds();
    auto buttonWidth = 30;
    auto chooserWidth = area.getWidth() - (buttonWidth * 6);
    
    loadButton.setBounds(area.removeFromLeft(buttonWidth * 2));
    saveButton.setBounds(area.removeFromLeft(buttonWidth * 2));
    presetChooser.setBounds(area.removeFromLeft(chooserWidth));
    previousButton.setBounds(area.removeFromLeft(buttonWidth));
    nextButton.setBounds(area.removeFromLeft(buttonWidth));
}
