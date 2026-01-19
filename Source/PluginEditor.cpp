#include "PluginEditor.h"
#include "PluginProcessor.h"

//==============================================================================
AudioPluginAudioProcessorEditor::AudioPluginAudioProcessorEditor(
    DelayAudioProcessor& p)
    : AudioProcessorEditor(&p), processorRef(p) {
  delayGroup.setText("Delay");
  delayGroup.setTextLabelPosition(juce::Justification::horizontallyCentred);
  delayGroup.addAndMakeVisible(delayTimeKnob);
  addAndMakeVisible(delayGroup);

  feedbackGroup.setText("Feedback");
  feedbackGroup.setTextLabelPosition(juce::Justification::horizontallyCentred);
  addAndMakeVisible(feedbackGroup);

  outputGroup.setText("Output");
  outputGroup.setTextLabelPosition(juce::Justification::horizontallyCentred);
  outputGroup.addAndMakeVisible(gainKnob);
  outputGroup.addAndMakeVisible(mixKnob);
  addAndMakeVisible(outputGroup);
  // Make sure that before the constructor has finished, you've set the
  // editor's size to whatever you need it to be.
  setSize(500, 330);
}

AudioPluginAudioProcessorEditor::~AudioPluginAudioProcessorEditor() {}

//==============================================================================
void AudioPluginAudioProcessorEditor::paint(juce::Graphics& g) {
  // (Our component is opaque, so we must completely fill the background with a
  // solid colour)
  g.fillAll(juce::Colours::darkgrey);
}

void AudioPluginAudioProcessorEditor::resized() {
  // This is generally where you'll want to lay out the positions of any
  // subcomponents in your editor..
  auto bounds = getLocalBounds();

  int y = 10;
  int height = bounds.getHeight() - 20;

  // Position the groups
  delayGroup.setBounds(10, y, 110, height);
  outputGroup.setBounds(bounds.getWidth() - 160, y, 150, height);

  feedbackGroup.setBounds(delayGroup.getRight() + 10, y,
                          outputGroup.getX() - delayGroup.getRight() - 20,
                          height);

  // Position the knobs inside the groups
  delayTimeKnob.setTopLeftPosition(20, 20);
  mixKnob.setTopLeftPosition(20, 20);
  gainKnob.setTopLeftPosition(mixKnob.getX(), mixKnob.getBottom() + 10);
}
