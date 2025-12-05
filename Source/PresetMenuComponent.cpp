/*
  ==============================================================================

    PresetMenuComponent.cpp
    Created: 21 Nov 2025 9:42:48am
    Author:  David Hill

  ==============================================================================
*/

#include "PresetMenuComponent.h"

PresetMenuComponent::PresetMenuComponent ()
{
    // addAndMakeVisible der ganze Buttons
    DBG ("Preset Menu Component Created");
    
    // speichern der buttonClickFunktion in der onClick Methode eines buttons
    loadButton.onClick = [this]()
    {
        DBG ("LOAD CLICKED");
        openLoadFileChooser();
    };
    
    saveButton.onClick = [this]()
    {
        DBG ("SAVE CLICKED");
        openSaveFileChooser();
        uniquePtrExample ();
    };
    
    addAndMakeVisible(loadButton);
    addAndMakeVisible(saveButton);
    addAndMakeVisible(nextButton);
    addAndMakeVisible(previousButton);
    addAndMakeVisible(currentPresetLabel);
}

PresetMenuComponent::~PresetMenuComponent ()
{
    DBG ("Preset Menu Component Destroyed");
}

// 1. was gibt die funktion zurück? 2. zu welcher klasse gehört die funktion? 3. wie heißt die funktion? 4. was für argumente hat die funktion?
void PresetMenuComponent::resized ()
{
    auto area = getLocalBounds ();
    DBG ("Width 1: " << area.getWidth());

//  Rectangle::removeFromLeft macht sozusagen das hier:
//    auto amountToRemove = area.getHeight ();
//    const Rectangle r (area.getX () /*x*/, area.getY () /*x*/, jmin (amountToRemove, area.getWidth ()) /*width*/, area.getHeight () /*height*/);
//    area.setX (area.getX () + r.getWidth ());
//    area.setWidth (area.getWidth() - r.getWidth());
    
    auto reduceFactor{ (10) };
    
    loadButton.setBounds (area.removeFromLeft (area.getHeight()).reduced (reduceFactor));
    DBG ("Width 2: " << area.getWidth());
    
    previousButton.setBounds (area.removeFromLeft (area.getHeight()).reduced (reduceFactor));
    DBG ("Width 3: " << area.getWidth());
    
    saveButton.setBounds(area.removeFromRight(area.getHeight ()).reduced (reduceFactor));
    DBG ("Width 4: " << area.getWidth());
    
    nextButton.setBounds (area.removeFromRight(area.getHeight ()).reduced (reduceFactor));
    DBG ("Width 5: " << area.getWidth());
    
    currentPresetLabel.setBounds (area.reduced (reduceFactor));
}

void PresetMenuComponent::paint (Graphics& g)
{
    g.fillAll (juce::Colours::red);
}

void PresetMenuComponent::openLoadFileChooser()
{
    // initialer pfad, den unser filechooser zeigen soll, wenn er geöffnet wird
    auto initialDirectory = getInitialDirectory();
    fileChooser = std::make_unique<FileChooser> ("Select Preset", initialDirectory);
    
    // die flags aus FileBrowserComponent zeigen dem filechooser, was er können soll.
    // dazu müssen wir verstehen, wie integers und bit operatoren funktionieren.
    
    // BIT OPERATORS
    // FileChooserComponent::openMode        00000001
    // FileChooserComponent::canSelectFiles  00000100
    //
    // openMode | canSelectFiles             00000101
        
    int flags = FileBrowserComponent::openMode | FileBrowserComponent::canSelectFiles;
    
    // wenn eine datei gewählt wurde, möchte unser filechooser eine LAMBDA funktion aufrufen können. schauen
    // wir FileChooser::launchAsync an, sehen wir dass die Funktion so aussehen soll: <void(const FileChooser&)>
    auto functionToCallWhenFileSelected = [&](const FileChooser& chooser)
    {
        auto file = chooser.getResult();
        
        if (file.existsAsFile())
        {
            DBG ("File chosen: " << file.getFullPathName());
        }
    };
    
    // starten unseres fileChoosers mithilfe der flags (openMode | canSelectFiles) und der LAMBDA
    fileChooser->launchAsync(flags, functionToCallWhenFileSelected);
}

void PresetMenuComponent::openSaveFileChooser()
{
    auto initalDirectory = getInitialDirectory();
    fileChooser = std::make_unique<FileChooser> ("Save Preset", initalDirectory);
    
    int flags = FileBrowserComponent::saveMode | FileBrowserComponent::warnAboutOverwriting;
    
    auto functionToCallWhenFileWritten = [&](const FileChooser& chooser)
    {
        auto file = chooser.getResult();
        
        if (file.getFullPathName().isNotEmpty())
        {
            DBG ("File specified by user where we should write our preset: " << file.getFullPathName());
        }
        else
        {
            DBG ("User canceled saving preset");
        }
    };
    
    fileChooser->launchAsync(flags, functionToCallWhenFileWritten);
}


File PresetMenuComponent::getInitialDirectory()
{
    // Geeignete Directory für unsere Presets
    File initialDirectory = File::getSpecialLocation(File::SpecialLocationType::userDocumentsDirectory);
    
    DBG (initialDirectory.getFullPathName());
    // ~/Documents
    
    initialDirectory = initialDirectory.getChildFile (ProjectInfo::companyName);
    DBG (initialDirectory.getFullPathName());
    // ~/Documents/CompanyName
    
    initialDirectory = initialDirectory.getChildFile(ProjectInfo::projectName);
    DBG (initialDirectory.getFullPathName());
    // ~/Documents/CompanyName/ProjectName
    
    initialDirectory = initialDirectory.getChildFile ("Presets");
    DBG (initialDirectory.getFullPathName());
    // ~/Documents/CompanyName/ProjectName/Presets
    
    if (! initialDirectory.exists())
        initialDirectory.createDirectory();

    return initialDirectory;
}


void PresetMenuComponent::uniquePtrExample()
{
    struct TestStruct
    {
        TestStruct ()
        {
            DBG ("TestStruct");
        }
        
        ~TestStruct ()
        {
            DBG ("~TestStruct");
        }
        
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TestStruct)
    };
    
    auto testStruct = new TestStruct ();
    
    std::unique_ptr<TestStruct> uniqueTestStructPtr;
    uniqueTestStructPtr.reset (testStruct);
}

