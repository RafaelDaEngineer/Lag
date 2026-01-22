#pragma once

#include "LookAndFeel.h"
#include "Parameters.h"
#include "PluginProcessor.h"
#include "RotaryKnob.h"
#include <juce_gui_basics/juce_gui_basics.h>

//==============================================================================
class AudioPluginAudioProcessorEditor final
    : public juce::AudioProcessorEditor {
public:
  explicit AudioPluginAudioProcessorEditor(DelayAudioProcessor&);
  ~AudioPluginAudioProcessorEditor() override;

  //==============================================================================
  void paint(juce::Graphics&) override;
  void resized() override;

private:
  // This reference is provided as a quick way for your editor to
  // access the processor object that created it.
  DelayAudioProcessor& processorRef;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AudioPluginAudioProcessorEditor)

  RotaryKnob gainKnob{"Gain", processorRef.apvts, gainParamID, true};
  RotaryKnob mixKnob{"Mix", processorRef.apvts, mixParamID};
  RotaryKnob delayTimeKnob{"Time", processorRef.apvts, delayTimeParamID};

  juce::GroupComponent delayGroup, feedbackGroup, outputGroup;

  MainLookAndFeel mainLF;
};
