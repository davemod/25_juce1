//
// Created by hannes on 11/21/25.
//


#pragma once

#include <JuceHeader.h>

class PresetMenuComponent : public Component
{
public:
    PresetMenuComponent ();
    ~PresetMenuComponent () override;

    void paint (juce::Graphics&) override;
    void resized () override; // This is important!
private:

    TextButton loadButton { "Load" };
    TextButton saveButton { "Save" };
    //TextButton nextButton { "➡️" };
    //TextButton previousButton { "⬅️" };
    TextButton nextButton { ">" };
    TextButton previousButton { "<" };
    ComboBox presetDropdown;


    Label currentPresetLabel{ "PresetLabel", "PRESET" };

    std::unique_ptr<FileChooser> presetFileChooser;
    void openLoadFileChooser ();
    void openSaveFileChooser ();

    void previousPreset();
    void nextPreset();

    //void uniquePtrExample ();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PresetMenuComponent)
};

