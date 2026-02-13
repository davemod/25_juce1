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
PresetMenuComponent::PresetMenuComponent(AudioProcessorValueTreeState& state)
:
state (state)
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
    saveButton.onClick = [this] { openSaveFileChooser(); };
    
    addAndMakeVisible(nextButton);
    nextButton.setButtonText(">");
    
    addAndMakeVisible(previousButton);
    previousButton.setButtonText("<");
}

PresetMenuComponent::~PresetMenuComponent()
{}

void PresetMenuComponent::openLoadFileChooser()
{
    auto initialDir = getInitialDirectory();
    
    presetFileChooser = std::make_unique<FileChooser> ("Load Preset...", initialDir, "*." + getFileExtension());
    
    auto folderChooserFlags = FileBrowserComponent::openMode | FileBrowserComponent::canSelectFiles;
     
    presetFileChooser->launchAsync (folderChooserFlags, [this] (const FileChooser& chooser)
    {
        File presetFile (chooser.getResult());
        loadPresetFile (presetFile);
    });
}

void PresetMenuComponent::openSaveFileChooser()
{
    auto initialDir = getInitialDirectory();
    
    presetFileChooser = std::make_unique<FileChooser> ("Save Preset As...", initialDir, "*." + getFileExtension());
    
    auto folderChooserFlags = FileBrowserComponent::saveMode;
     
    presetFileChooser->launchAsync (folderChooserFlags, [this] (const FileChooser& chooser)
    {
        File presetFile (chooser.getResult());
        DBG (presetFile.getFullPathName());
        
        savePresetFile(presetFile);
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

File PresetMenuComponent::getInitialDirectory()
{
    auto initialDir = File::getSpecialLocation(File::userDocumentsDirectory)
        .getChildFile (ProjectInfo::companyName)
        .getChildFile (ProjectInfo::projectName)
        .getChildFile ("Presets");
    
    if (! initialDir.isDirectory ())
        initialDir.deleteFile();
    
    if (! initialDir.exists ())
        initialDir.createDirectory ();
    
    DBG ("Presets initial directory: " << initialDir.getFullPathName());
    
    return initialDir;
}

String PresetMenuComponent::getFileExtension()
{
    return "helloworld";
}

void PresetMenuComponent::loadPresetFile(File& file)
{
    // please pass a valid file
    jassert (file.getFullPathName().isNotEmpty());
    if (file.getFullPathName().isEmpty ())
        return;
    
    // create a stream from our file
    FileInputStream fis{ file };
    
    // parse the value treem using the input stream
    auto newState = ValueTree::readFromStream(fis);
    
    // replace state in our AudioProcessorValueTreeState
    state.replaceState(newState);
}

void PresetMenuComponent::savePresetFile(File& file)
{
    // please pass a valid file
    jassert (file.getFullPathName().isNotEmpty());
    if (file.getFullPathName().isEmpty ())
        return;
    
    // copy the state from our AudioProcessorValueTreeState
    ValueTree lState = state.copyState ();
    
    // create an instance of a FileOutputStream that references the incoming file
    FileOutputStream fos{ file };
    
    // write lState to the file using the FileOutputStream fos
    lState.writeToStream(fos);
}
