
#include "PresetMenuComponent.h"
#include <JuceHeader.h>

//==============================================================================
PresetMenuComponent::PresetMenuComponent(AudioProcessorValueTreeState &state)
    : state(state)
{
  addAndMakeVisible(presetChooser);
  presetChooser.addItem("Awesome Anton", 1);
  presetChooser.addItem("Edgy Eddy", 2);
  presetChooser.addItem("Jolly Jasper", 3);
  presetChooser.addItem("Neato Niko", 4);
  presetChooser.setSelectedId(4);
  // Can we find all the files in the preset folder and append them to the
  // presetChooser?

  addAndMakeVisible(loadButton);
  loadButton.setButtonText("Load");
  loadButton.onClick = [this] { openLoadFileChooser(); };

  addAndMakeVisible(saveButton);
  saveButton.setButtonText("Save");
  saveButton.onClick = [this] { openSaveFileChooser(); };

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
  auto initialDir = getInitialDirectory();

  presetFileChooser =
      std::make_unique<FileChooser>("Load Preset...", initialDir, "*." + getFileExtension());

  auto folderChooserFlags = FileBrowserComponent::openMode |
    FileBrowserComponent::canSelectFiles;


  presetFileChooser->launchAsync(folderChooserFlags, [this](const FileChooser &chooser)
{
    File presetFile = chooser.getResult();

    // 1. Verify the file is valid (handles the user hitting 'Cancel')
    if (presetFile.existsAsFile())
    {
        // 2. Read the file and parse it as XML
        // XmlDocument::parse handles the heavy lifting of reading the text
        auto xmlElement = juce::XmlDocument::parse(presetFile);

        if (xmlElement != nullptr)
        {
            // 3. Convert the XML back into a ValueTree
            auto loadedTree = juce::ValueTree::fromXml(*xmlElement);

            // 4. Update the APVTS. This instantly updates your UI sliders too!
            state.replaceState(loadedTree);
        }
    }
});
}

void PresetMenuComponent::openSaveFileChooser()
{
  auto initialDir = getInitialDirectory();

  presetFileChooser = std::make_unique<juce::FileChooser>("Save Preset As...",initialDir,
                                                          "*." + getFileExtension()); // Using .xml for easier loading later

  auto folderChooserFlags = juce::FileBrowserComponent::saveMode | juce::FileBrowserComponent::canSelectFiles;

  presetFileChooser->launchAsync(folderChooserFlags, [this](const juce::FileChooser& chooser)
  {
      juce::File resultFile = chooser.getResult();
/*
      // Check if the user actually picked a file (didn't hit cancel)
      if (resultFile != juce::File{})


        {
          // 2. Get the ValueTree from the APVTS
          // 'state' is your AudioProcessorValueTreeState
          juce::ValueTree myTree = state.copyState();

          // 3. Convert that Tree into an XML element, easier than JSON
          std::unique_ptr<juce::XmlElement> xml = myTree.createXml();

          if (xml != nullptr)
          {
              // 4. Write that XML to the file as a string
              resultFile.replaceWithText(xml->toString());
          }*/
      }
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
  int id = presetChooser.getSelectedId() - 1; // to zero base

  id = (id + 1) % amnt;

  presetChooser.setSelectedId(id + 1); // and back
  DBG("amnt: " << amnt << "\nid: " << id);
}

void PresetMenuComponent::previousPreset()
{
  int amnt = presetChooser.getNumItems();
  int id = presetChooser.getSelectedId() - 1; // to zero base

  id = (id - 1 + amnt) % amnt;

  presetChooser.setSelectedId(id + 1); // and back
  DBG("amnt: " << amnt << "\nid: " << id);
}


File PresetMenuComponent::getInitialDirectory()
{
  auto initialDir = File::getSpecialLocation(File::userDocumentsDirectory)
  .getChildFile(ProjectInfo::companyName)
                        .getChildFile(ProjectInfo::projectName)
                        .getChildFile("Presets");

  if (!initialDir.isDirectory() )
      initialDir.deleteFile();

  if (!initialDir.exists())
    initialDir.createDirectory();

  DBG ("Presets initial directory: " <<
    initialDir.getFullPathName());

  return initialDir;
}

String PresetMenuComponent::getFileExtension()
{
  return "hfm";
}

void PresetMenuComponent::loadPresetFile(File & file)
{
  // please pass a valid file
  jassert (file.getFullPathName().isNotEmpty());
  if (file.getFullPathName().isEmpty ())
    return;

  //create stream from our file
  FileInputStream fis { file };
  auto newState = ValueTree::readFromStream(fis);

  // replace state in our AudioProcessorValutTreeState
  state.replaceState(newState);

}

void PresetMenuComponent::savePresetFile(File & file)
{
  // please pass a valid file
  jassert (file.getFullPathName().isNotEmpty());
  if (file.getFullPathName().isEmpty ())
    return;

  auto lState = state.copyState();

  juce::FileOutputStream fos{ file };
  lState.writeToStream(fos);

}

