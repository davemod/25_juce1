
#include "PresetMenuComponent.h"
#include <JuceHeader.h>

//==============================================================================
PresetMenuComponent::PresetMenuComponent(AudioProcessorValueTreeState &state)
    : state(state)
{
  addAndMakeVisible(presetChooser);
  presetChooser.addItem("Awesome Anton", 1);
  presetChooser.addItem("Edgy Energy", 2);
  presetChooser.addItem("Jolly Jasper", 3);
  presetChooser.addItem("Narcotic Niko", 4);
  presetChooser.setSelectedId(4);

  addAndMakeVisible(loadButton);
  loadButton.setButtonText("Load");
  loadButton.onClick = [this] { openLoadFileChooser(); };

  addAndMakeVisible(saveButton);
  saveButton.setButtonText("Save");

  addAndMakeVisible(nextButton);
  nextButton.setButtonText(">");
  nextButton.onClick = [this] { nextPreset(); };

  addAndMakeVisible(previousButton);
  previousButton.setButtonText("<");
  previousButton.onClick = [this] { previousPreset(); };
}

PresetMenuComponent::~PresetMenuComponent() {}

void PresetMenuComponent::openLoadFileChooser()
{
  auto initialDir = File::getSpecialLocation(File::userDocumentsDirectory)
                        .getChildFile(ProjectInfo::companyName)
                        .getChildFile(ProjectInfo::projectName)
                        .getChildFile("Presets");

  DBG("initialDir: " + initialDir.getFullPathName());

  presetFileChooser =
      std::make_unique<FileChooser>("Load Preset...", initialDir, "*.json");

  auto folderChooserFlags = FileBrowserComponent::openMode;

  presetFileChooser->launchAsync(folderChooserFlags,
                                 [this](const FileChooser &chooser)
                                 {
                                   File presetFile(chooser.getResult());

                                   // loadPresetFile (presetFile);
                                   // Something with APVTS, probably
                                   // TODO: load preset file
                                 });
}

void PresetMenuComponent::openSaveFileChooser()
{
  auto dir = File::getSpecialLocation(File::userDocumentsDirectory);
  presetFileChooser =
      std::make_unique<FileChooser>("Load Preset...", File(), "*.json");

  auto folderChooserFlags = FileBrowserComponent::saveMode;

  presetFileChooser->launchAsync(folderChooserFlags,
                                 [this](const FileChooser &chooser)
                                 {
                                   File presetFile(chooser.getResult());
                                   // Save the current apvts state, probably
                                   // into a .json
                                   // TODO: save preset file
                                 });
}

void PresetMenuComponent::paint(juce::Graphics &g)
{

  g.fillAll(getLookAndFeel().findColour(
      juce::ResizableWindow::backgroundColourId)); // clear the background

  g.setColour(juce::Colours::grey);
  g.drawRect(getLocalBounds(), 1); // draw an outline around the component

  g.setColour(juce::Colours::white);
  g.setFont(juce::FontOptions(14.0f));
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

void PresetMenuComponent::nextPreset()
{
  int amnt = presetChooser.getNumItems();
  int id = presetChooser.getSelectedId();

  id = (id % amnt) + 1; // This logic is super janky but it works

  presetChooser.setSelectedId(id);
  DBG("amnt: " << amnt << "\nid: " << id);
}

void PresetMenuComponent::previousPreset()
{
  int amnt = presetChooser.getNumItems();
  int id = presetChooser.getSelectedId();

  id--;
  if (id == 0)
  {
    id = amnt;
  }

  presetChooser.setSelectedId(id);
  DBG("amnt: " << amnt << "\nid: " << id);
}