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
    
    addAndMakeVisible (gainSlider);
    addAndMakeVisible (textButton);
    addAndMakeVisible (comboBox);
    addAndMakeVisible (bypassToggleButton);
    addAndMakeVisible (channelStrip1);
    addAndMakeVisible (channelStrip2);
    addAndMakeVisible (channelStrip3);
    addAndMakeVisible (channelStrip4);
    addAndMakeVisible (presetMenu);
    
    // TODO 8 & 10:
    // set levels in plugin processor, when channelStripX.onLevelChanged was called
    // Example: channelStrip1.onLevelChanged = [this] (float levelInDecibels) { audioProcessor.setBandAGain ( convert edcibels to gain ); }

    // Step 6 -> mute callbacks
    channelStrip1.onMuteChanged = [this](bool isMuted)
    {
        audioProcessor.setLowMute (isMuted);
    };
    channelStrip2.onMuteChanged = [this](bool isMuted)
    {
        audioProcessor.setLowMidMute (isMuted);
    };
    channelStrip3.onMuteChanged = [this](bool isMuted)
    {
        audioProcessor.setHighMidMute (isMuted);
    };
    channelStrip4.onMuteChanged = [this](bool isMuted)
    {
        audioProcessor.setHighMute (isMuted);
    };

    // Step 7 -> Solo Callbacks
    channelStrip1.onSoloChanged = [this](bool s)
    {
        audioProcessor.setLowSolo (s);
    };

    channelStrip2.onSoloChanged = [this](bool s)
    {
        audioProcessor.setLowMidSolo (s);
    };

    channelStrip3.onSoloChanged = [this](bool s)
    {
        audioProcessor.setHighMidSolo (s);
    };

    channelStrip4.onSoloChanged = [this](bool s)
    {
        audioProcessor.setHighSolo (s);
    };

    channelStrip1.onLevelChanged = [this] (float dB)
    {
        audioProcessor.setLowGain (
            juce::Decibels::decibelsToGain (dB)
        );
    };

    channelStrip2.onLevelChanged = [this] (float dB)
    {
        audioProcessor.setLowMidGain (
            juce::Decibels::decibelsToGain (dB)
        );
    };

    channelStrip3.onLevelChanged = [this] (float dB)
    {
        audioProcessor.setHighMidGain (
            juce::Decibels::decibelsToGain (dB)
        );
    };

    channelStrip4.onLevelChanged = [this] (float dB)
    {
        audioProcessor.setHighGain (
            juce::Decibels::decibelsToGain (dB)
        );
    };

    
    textButton.setColour (TextButton::buttonColourId, Colours::purple);
    textButton.setColour (TextButton::textColourOffId, Colours::black);
    textButton.setColour (TextButton::textColourOnId, Colours::white);
    textButton.setClickingTogglesState(true);
    
    bypassToggleButton.setTitle("Bypass");
    bypassToggleButton.setButtonText("Bypass");

    addAndMakeVisible(presetMenu);
    
    // Nothing selected - Text
    comboBox.setTextWhenNothingSelected("Select Preset");

    // Add items
    comboBox.addItem ("Cool Gain Slider", 1);
    comboBox.addItem ("Groovy Bypass Toggle", 2);
    comboBox.addItem ("Funky Clicky Textbutton", 3);
    comboBox.addItem ("Awesome ComboBox", 4);

    // Optionally set a default selection:
    comboBox.setSelectedId (0);

    gainSlider.setSliderStyle (Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    gainSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, false, 100, 10);

    // add redBox
    // addAndMakeVisible (redBox);
    // addAndMakeVisible (blueBox);
    // addAndMakeVisible (greenBox);
    
    setSize (500, 400);
    setResizeLimits(300, 200, 900, 600);
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
}

void HelloWorldAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    auto area = getLocalBounds();
    auto channelStripWidth = area.getWidth()/4;
    
    presetMenu.setBounds(area.removeFromTop(30));
    
    channelStrip1.setBounds (area.removeFromLeft (channelStripWidth));
    channelStrip2.setBounds (area.removeFromLeft (channelStripWidth));
    channelStrip3.setBounds (area.removeFromLeft (channelStripWidth));
    channelStrip4.setBounds (area.removeFromLeft (channelStripWidth));
}
