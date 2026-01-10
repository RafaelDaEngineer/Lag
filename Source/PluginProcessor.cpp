#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
DelayAudioProcessor::DelayAudioProcessor()
    : AudioProcessor(
          BusesProperties()
              .withInput("Input", juce::AudioChannelSet::stereo(), true)
              .withOutput("Output", juce::AudioChannelSet::stereo(), true)),
      params(apvts) {
  // do nothing
}

DelayAudioProcessor::~DelayAudioProcessor() {}

//==============================================================================
const juce::String DelayAudioProcessor::getName() const {
  return JucePlugin_Name;
}

bool DelayAudioProcessor::acceptsMidi() const {
#if JucePlugin_WantsMidiInput
  return true;
#else
  return false;
#endif
}

bool DelayAudioProcessor::producesMidi() const {
#if JucePlugin_ProducesMidiOutput
  return true;
#else
  return false;
#endif
}

bool DelayAudioProcessor::isMidiEffect() const {
#if JucePlugin_IsMidiEffect
  return true;
#else
  return false;
#endif
}

double DelayAudioProcessor::getTailLengthSeconds() const { return 0.0; }

int DelayAudioProcessor::getNumPrograms() {
  return 1; // NB: some hosts don't cope very well if you tell them there are 0
            // programs,
  // so this should be at least 1, even if you're not really implementing
  // programs.
}

int DelayAudioProcessor::getCurrentProgram() { return 0; }

void DelayAudioProcessor::setCurrentProgram(int index) {
  juce::ignoreUnused(index);
}

const juce::String DelayAudioProcessor::getProgramName(int index) {
  juce::ignoreUnused(index);
  return {};
}

void DelayAudioProcessor::changeProgramName(int index,
                                            const juce::String& newName) {
  juce::ignoreUnused(index, newName);
}

//==============================================================================
void DelayAudioProcessor::prepareToPlay(double sampleRate,
                                        int samplesPerBlock) {
  // Use this method as the place to do any pre-playback
  // initialisation that you need..
  juce::ignoreUnused(sampleRate, samplesPerBlock);
  params.prepareToPlay(sampleRate);
  params.reset();
}

void DelayAudioProcessor::releaseResources() {
  // When playback stops, you can use this as an opportunity to free up any
  // spare memory, etc.
}

bool DelayAudioProcessor::isBusesLayoutSupported(
    const BusesLayout& layouts) const {
  return layouts.getMainOutputChannelSet() == juce::AudioChannelSet::stereo();
}

void DelayAudioProcessor::processBlock(
    juce::AudioBuffer<float>& buffer,
    [[maybe_unused]] juce::MidiBuffer& midiMessages) {
  juce::ignoreUnused(midiMessages);

  juce::ScopedNoDenormals noDenormals;
  auto totalNumInputChannels = getTotalNumInputChannels();
  auto totalNumOutputChannels = getTotalNumOutputChannels();

  for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
    buffer.clear(i, 0, buffer.getNumSamples());

 params.update();

  float* channelDataL = buffer.getWritePointer(0);
  float* channelDataR = buffer.getWritePointer(1);

  float gain = params.gain;

 for (int sample = 0; sample < buffer.getNumSamples(); ++sample) {
   params.smoothen();

   channelDataL[sample] *= params.gain;
   channelDataR[sample] *= params.gain;
 }
}

//==============================================================================
bool DelayAudioProcessor::hasEditor() const {
  return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* DelayAudioProcessor::createEditor() {
  return new AudioPluginAudioProcessorEditor(*this);
}

//==============================================================================
void DelayAudioProcessor::getStateInformation(juce::MemoryBlock& destData) {
  // You should use this method to store your parameters in the memory block.
  // You could do that either as raw data, or use the XML or ValueTree classes
  // as intermediaries to make it easy to save and load complex data.
  copyXmlToBinary(*apvts.copyState().createXml(), destData);
  // DBG(apvts.copyState().toXmlString());
}

void DelayAudioProcessor::setStateInformation(const void* data,
                                              int sizeInBytes) {
  // You should use this method to restore your parameters from this memory
  // block, whose contents will have been created by the getStateInformation()
  // call.
  std::unique_ptr<juce::XmlElement> xml(getXmlFromBinary(data, sizeInBytes));
  if (xml.get() != nullptr && xml->hasTagName(apvts.state.getType())) {
    apvts.replaceState(juce::ValueTree::fromXml(*xml));
  }
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter() {
  return new DelayAudioProcessor();
}

juce::AudioProcessorValueTreeState::ParameterLayout
Parameters::createParameterLayout() {
  juce::AudioProcessorValueTreeState::ParameterLayout layout;

  layout.add(std::make_unique<juce::AudioParameterFloat>(
      gainParamID, "Output Gain", juce::NormalisableRange<float>{-12.0f, 12.0f},
      0.0f));

  return layout;
}