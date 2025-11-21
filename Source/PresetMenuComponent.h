/*
  ==============================================================================

    PresetMenuComponent.h
    Created: 21 Nov 2025 10:00:36am
    Author:  Niklas Achauer

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class PresetMenuComponent : public Component
{
public:
    PresetMenuComponent();
    ~PresetMenuComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;
private:
   
    TextButton loadButton;
    TextButton saveButton;
    TextButton nextButton;
    TextButton previousButton;
    
    Label currentPresetLabel;
    
    String currentPresetPath;
    std::unique_ptr<juce::FileChooser> fileChooser;
    
    void loadPreset();
    void loadPresetFromFile(const juce::File& file);
    
    void savePreset();
    void writePresetToFile(const juce::File& file);
    
};
