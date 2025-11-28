/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


#define MYMACRO DBG("My Macro Print")

//==============================================================================
HelloWorldAudioProcessorEditor::HelloWorldAudioProcessorEditor (HelloWorldAudioProcessor& p)
:
AudioProcessorEditor (&p),
audioProcessor (p),
gainSlider()
{    
    setResizable(true, true);

    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (500, 400);

    //gainSlider.setVisible (true);
    //addChildComponent (gainSlider);

    addAndMakeVisible (gainSlider);
    addAndMakeVisible (clickTextButton);
    clickTextButton.setColour (TextButton::buttonColourId, Colours::purple);
    clickTextButton.setColour (TextButton::textColourOffId, Colours::black);
    clickTextButton.setColour (TextButton::textColourOnId, Colours::white);
    clickTextButton.setClickingTogglesState(true);

    addAndMakeVisible (selectComboBox);

    addAndMakeVisible(presetMenu);
    
    // Nothing selected - Text
    selectComboBox.setTextWhenNothingSelected( "Select Preset" );


    // Add items
    selectComboBox.addItem ("Cool Gain Slider", 1);
    selectComboBox.addItem ("Groovy Bypass Toggle", 2);
    selectComboBox.addItem ("Funky Clicky Textbutton", 3);
    selectComboBox.addItem ("Awesome ComboBox", 4);

    // Optionally set a default selection:
    selectComboBox.setSelectedId (0);

    addAndMakeVisible (bypassToggleButton);

    //clickTextButton::TextButton ()

    gainSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    //gainSlider.hideTextBox(true);
    gainSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, false, 100, 10);

    // add redBox
    addAndMakeVisible (redBox);
    addAndMakeVisible (blueBox);
    addAndMakeVisible (greenBox);
    
    DBG ("PluginEditor ()");
}

HelloWorldAudioProcessorEditor::~HelloWorldAudioProcessorEditor()
{
    DBG ("~PluginEditor ()");
}

//==============================================================================
void HelloWorldAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (juce::FontOptions (15.0f));
    // g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void HelloWorldAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

    auto bounds = getLocalBounds ();
    
    presetMenu.setBounds (bounds.removeFromTop (60).reduced(3));
    
    auto centre = bounds.getCentre ();
    DBG ("Centre: " << centre.getX () << ", " << centre.getY ());

    int width = bounds.getWidth ();
    int height = bounds.getHeight ();

    int xPos = centre.getX ();
    int yPos = centre.getY ();

    int smallestSide = jmin (width, height);
    DBG ("smallestSide: " << smallestSide);

    int sliderSide = smallestSide / 3;
    DBG ("sliderSide: " << sliderSide);

    // Reactivate again once the other elements are figured out!
    gainSlider.setBounds(xPos - (sliderSide / 2), yPos - (sliderSide / 2), sliderSide, sliderSide);
    //gainSlider.setBounds(50, 50, 100, 100);

//   JUCE_LIVE_CONSTANT example. Mehrere JUCE_LIVE_CONSTANT müssen in unterschiedliche Zeilen
//   bypassToggleButton.setBounds(JUCE_LIVE_CONSTANT (25),
//                                JUCE_LIVE_CONSTANT (25), 25, 25);
   
    // bypassToggleButton.setBounds(25, 25, 25, 25);
    selectComboBox.setBounds(xPos - 150, 25, 300, 25);
    clickTextButton.setBounds(xPos - (width / 8), yPos + (sliderSide / 2) + (sliderSide / 10), width / 4, height / 6);
    
    // redbox
    auto boxBounds = gainSlider.getBounds ().withWidth (gainSlider.getWidth () / 2).withHeight (gainSlider.getHeight() / 2).translated (- gainSlider.getWidth() - 5, 0);
    
    redBox.setBounds (boxBounds);
    blueBox.setBounds (boxBounds.translated (boxBounds.getWidth (), 0));
    greenBox.setBounds (boxBounds.translated (0, boxBounds.getHeight ()));
}
