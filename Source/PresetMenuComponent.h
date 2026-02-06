
#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
 */
class PresetMenuComponent : public juce::Component
{
public:
  PresetMenuComponent(AudioProcessorValueTreeState &state);
  ~PresetMenuComponent() override;

  void paint(juce::Graphics &) override;
  void resized() override;

private:
  AudioProcessorValueTreeState& state;
  String currentPreset;

  ComboBox presetChooser;
  Label currentPresetLabel;
  TextButton loadButton;
  TextButton saveButton;
  TextButton nextButton;
  TextButton previousButton;

  std::unique_ptr<FileChooser> presetFileChooser;

  void openLoadFileChooser();
  void loadPresetFile(File &);
  void openSaveFileChooser();
  void savePresetFile(File &);

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PresetMenuComponent)
};
