//
// Created by hannes on 11/21/25.
//

#include "PresetMenuComponent.h"

PresetMenuComponent::PresetMenuComponent()
{

    /*
    auto func = []() {
        DBG ("LAMBDA CALLED");
    };

    func ();

    std::function<void ()> copy = func;

    copy ();
    */

    auto loadButtonClicked = []() {
        DBG ("You have successfully clicked the load button. I am proud of you!");
    };
    auto saveButtonClicked = []() {
        DBG ("You have successfully clicked the save button. You are a lovely person!");
    };
    auto nextButtonClicked = []() {
        DBG ("You have successfully clicked the next button. You are doing your best!");
    };
    auto previousButtonClicked = []() {
        DBG ("You have successfully clicked the previous button. I am happy that you are here!");
    };

    /*
    loadButton.onClick = loadButtonClicked;
    saveButton.onClick = saveButtonClicked;
    nextButton.onClick = nextButtonClicked;
    previousButton.onClick = previousButtonClicked;
    */

    loadButton.onClick = [this]() {
        openLoadFileChooser();
    };

    saveButton.onClick = [this]() {
        openSaveFileChooser();
    };

    nextButton.onClick = [this]() {
        nextPreset();
    };

    previousButton.onClick = [this]() {
        previousPreset();
    };

    addAndMakeVisible(loadButton);
    addAndMakeVisible(saveButton);
    addAndMakeVisible(nextButton);
    addAndMakeVisible(previousButton);
    addAndMakeVisible(presetDropdown);
    presetDropdown.addItem("Awesome Anton", 1);
    presetDropdown.addItem("Edgy Eddy", 2);
    presetDropdown.addItem("Jolly Jasper", 3);
    presetDropdown.addItem("Default", 4);
    presetDropdown.setSelectedId(4);

    //DBG ("Preset Menu Component Created");
}

PresetMenuComponent::~PresetMenuComponent ()
{
    //DBG ("Preset Menu Component Destroyed");
}

void PresetMenuComponent::resized() {

    auto bounds = getLocalBounds().reduced(5);
    int width = bounds.getWidth () / 8;
    // int height = bounds.getHeight ();

    loadButton.setBounds(bounds.removeFromLeft(width).reduced(1));
    previousButton.setBounds(bounds.removeFromLeft(width).reduced(1));
    saveButton.setBounds(bounds.removeFromRight(width).reduced(1));
    nextButton.setBounds(bounds.removeFromRight(width).reduced(1));
    presetDropdown.setBounds(bounds.reduced(1));



    //coole Dropdown Box machen für Presets! :)

}

void PresetMenuComponent::paint (Graphics& g)
{
    g.fillAll (juce::Colours::seagreen);
}

void PresetMenuComponent::openLoadFileChooser()
{
    File initialDir = File::getSpecialLocation(File::SpecialLocationType::userDocumentsDirectory)
    .getChildFile (ProjectInfo::companyName)
    .getChildFile (ProjectInfo::projectName)
    .getChildFile ("Presets");

    DBG("initialDir: " + initialDir.getFullPathName());

    presetFileChooser = std::make_unique<FileChooser> ("Select Preset", initialDir, "*.json");


    int flags = FileBrowserComponent::openMode | FileBrowserComponent::canSelectFiles; // erstellt quasi eine Bitmask von den Components, die der FileChooser braucht.
    std::function<void(const FileChooser &)> functionToCallWhenFileSelected = [&](const FileChooser& chooser) {
        File presetFile (chooser.getResult());

        DBG ("File chosen: " << presetFile.getFullPathName());

        // TODO: Load preset file
    };

    presetFileChooser->launchAsync(flags, functionToCallWhenFileSelected); //launchAsync = wird erst nach dem Scope geöffnet
    DBG("File Chooser Launched");
}

void PresetMenuComponent::openSaveFileChooser()
{
    auto dir = File::getSpecialLocation(File::userDocumentsDirectory);
    presetFileChooser = std::make_unique<FileChooser> ("Save Preset...", File(), "*.json");

    auto folderChooserFlags = FileBrowserComponent::saveMode;

    presetFileChooser->launchAsync (folderChooserFlags, [this] (const FileChooser& chooser)
    {
        File presetFile (chooser.getResult());

        // TODO: save preset file
    });
}

void PresetMenuComponent::nextPreset() {
    DBG("Next Preset clicked");
    int currentID = presetDropdown.getSelectedId();
    DBG(currentID);
    int availableIDs = presetDropdown.getNumItems();
    DBG(availableIDs);
    if (currentID < availableIDs) {
        int nextID = currentID + 1;
        presetDropdown.setSelectedId(nextID);
    };
}

void PresetMenuComponent::previousPreset() {
    DBG("Previous Preset clicked");
    int currentID = presetDropdown.getSelectedId();
    DBG(currentID);
    int availableIDs = presetDropdown.getNumItems();
    DBG(availableIDs);
    if (currentID > 1) {
        int nextID = currentID - 1;
        presetDropdown.setSelectedId(nextID);
    };
}


/*
void PresetMenuComponent::uniquePtrExample() {
    struct TestStruct
    {
        TestStruct ()
        {
            DBG("TestStruct");
        }

        ~TestStruct ()
        {
            DBG("~TestStruct");
        }

        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PresetMenuComponent);
    };

    auto testStruct = new TestStruct ();

    std::unique_ptr<TestStruct> uniqueTestStructPtr;
    uniqueTestStructPtr.reset (testStruct);
}
*/