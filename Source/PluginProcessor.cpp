
#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
HelloWorldAudioProcessor::HelloWorldAudioProcessor()
    : AudioProcessor(
          BusesProperties()
              .withInput("Input", juce::AudioChannelSet::stereo(), true)
              .withOutput("Output", juce::AudioChannelSet::stereo(), true)),
      state(*this, nullptr, "HelloWorldState", createParameterLayout())
{
  DBG("PluginProcessor ()");
}

HelloWorldAudioProcessor::~HelloWorldAudioProcessor()
{
  DBG("~PluginProcessor ()"); // will be called when an instance of
                              // HelloWorldAudioProcessor is destroyed
}

//==============================================================================
const juce::String HelloWorldAudioProcessor::getName() const
{
  return JucePlugin_Name;
}

//========== MIDI OPTIONS =============
bool HelloWorldAudioProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
  return true;
#else
  return false;
#endif
}

bool HelloWorldAudioProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
  return true;
#else
  return false;
#endif
}

bool HelloWorldAudioProcessor::isMidiEffect() const
{
#if JucePlugin_IsMidiEffect
  return true;
#else
  return false;
#endif
}
//=========== END MIDI OPTIONS ===========

double HelloWorldAudioProcessor::getTailLengthSeconds() const { return 0.0; }

int HelloWorldAudioProcessor::getNumPrograms()
{
  return 1; // NB: some hosts don't cope very well if you tell them there are 0
            // programs, so this should be at least 1, even if you're not really
            // implementing programs.
}

int HelloWorldAudioProcessor::getCurrentProgram() { return 0; }

void HelloWorldAudioProcessor::setCurrentProgram(int index) {}

const juce::String HelloWorldAudioProcessor::getProgramName(int index)
{
  return {};
}

void HelloWorldAudioProcessor::changeProgramName(int index,
                                                 const juce::String &newName)
{
}

//==============================================================================
void HelloWorldAudioProcessor::prepareToPlay(double sampleRate,
                                             int samplesPerBlock)
{
  eq.prepare(sampleRate, samplesPerBlock, 2);
}

void HelloWorldAudioProcessor::releaseResources()
{
  // When playback stops, you can use this as an opportunity to free up any
  // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool HelloWorldAudioProcessor::isBusesLayoutSupported(
    const BusesLayout &layouts) const
{
#if JucePlugin_IsMidiEffect
  juce::ignoreUnused(layouts);
  return true;
#else
  // This is the place where you check if the layout is supported.
  // In this template code we only support mono or stereo.
  // Some plugin hosts, such as certain GarageBand versions, will only
  // load plugins that support stereo bus layouts.
  if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono() &&
      layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
    return false;

  // This checks if the input layout matches the output layout
#if !JucePlugin_IsSynth
  if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
    return false;
#endif

  return true;
#endif
}
#endif

void HelloWorldAudioProcessor::processBlock(juce::AudioBuffer<float> &buffer,
                                            juce::MidiBuffer &midiMessages)
{
  juce::ScopedNoDenormals noDenormals;
  auto totalNumInputChannels = getTotalNumInputChannels();
  auto totalNumOutputChannels = getTotalNumOutputChannels();

  // In case we have more outputs than inputs, this code clears any output
  // channels that didn't contain input data, (because these aren't
  // guaranteed to be empty - they may contain garbage).
  // This is here to avoid people getting screaming feedback
  // when they first compile a plugin, but obviously you don't need to keep
  // this code if your algorithm always overwrites all the output channels.
  for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
    buffer.clear(i, 0, buffer.getNumSamples());

  applyEQState();

  eq.processBlock(buffer);
}

//==============================================================================
bool HelloWorldAudioProcessor::hasEditor() const
{
  return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor *HelloWorldAudioProcessor::createEditor()
{
  return new HelloWorldAudioProcessorEditor(*this);
}

//==============================================================================
void HelloWorldAudioProcessor::getStateInformation(juce::MemoryBlock &destData)
{
  // You should use this method to store your parameters in the memory block.
  // You could do that either as raw data, or use the XML or ValueTree classes
  // as intermediaries to make it easy to save and load complex data.
  auto lState = state.copyState();
  MemoryOutputStream mos(destData, false);
  lState.writeToStream(mos);
}

void HelloWorldAudioProcessor::setStateInformation(const void *data,
                                                   int sizeInBytes)
{
  // You should use this method to restore your parameters from this memory
  // block, whose contents will have been created by the getStateInformation()
  // call.
  state.replaceState(ValueTree::readFromData(data, sizeInBytes));
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor *JUCE_CALLTYPE createPluginFilter()
{
  return new HelloWorldAudioProcessor();
}

void HelloWorldAudioProcessor::applyEQState()
{

  std::vector<float> gains{0.0f, 0.0f, 0.0f, 0.0f};
  std::vector<bool> solos{false, false, false, false};
  std::vector<bool> mutes{false, false, false, false};

  for (int i = 0; i < eq.numBands; i++)
  {
    gains[i] = *state.getRawParameterValue(ID::bandGain(i));
    solos[i] = *state.getRawParameterValue(ID::bandSolo(i));
    mutes[i] = *state.getRawParameterValue(ID::bandMute(i));
  };

  Array<float> bandGains = {0.0f, 0.0f, 0.0f, 0.0f};

  bool anySoloed = std::any_of(solos.begin(), solos.end(), [](bool s) { return s; });

  for (int i = 0; i < eq.numBands; i++)
  {
    // Solo overrides mute, always
    if (!solos[i] && (mutes[i] || anySoloed))
      bandGains.set(i, 0.0f);
    else
    {
      float gain = Decibels::decibelsToGain(gains[i]);
      bandGains.set(i, gain);
    }

  };

  DBG("Applied eq gains: | 1: " << bandGains[0] << " | 2: " << bandGains[1] << " | 3: " << bandGains[2] << " | 4: " << bandGains[3]);

  eq.setBandGains(bandGains);
}

APVTS::ParameterLayout HelloWorldAudioProcessor::createParameterLayout()
{
  auto layout = APVTS::ParameterLayout();
  for (int i = 0; i < eq.numBands; i++)
  {
    layout.add(std::make_unique<AudioParameterBool>(
        ParameterID(ID::bandMute(i), 1), "Mute Band " + std::to_string(i),
        false));
    layout.add(std::make_unique<AudioParameterBool>(
        ParameterID(ID::bandSolo(i), 1), "Solo Band " + std::to_string(i),
        false));

    NormalisableRange<float> gainRange {-69.0f, 24.0f, 0.01f };
    gainRange.setSkewForCentre(0.f);

    layout.add(std::make_unique<AudioParameterFloat>(
        ParameterID(ID::bandGain(i), 1), "Gain Band " + std::to_string(i),
        gainRange, 0.0));
  }

  return layout;
}
