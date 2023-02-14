#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

class ChorusPluginAudioEditor : public juce::AudioProcessorEditor
{
public:
    ChorusPluginAudioEditor(ChorusPluginAudioProcessor&);
    ~ChorusPluginAudioEditor() override;

    void paint(juce::Graphics&) override;
    void resized() override;

private:
    ChorusPluginAudioProcessor& audioProcessor;
    juce::Slider dryWetSlider;
    juce::Slider delayTimeSlider;
    juce::Slider depthSlider;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ChorusPluginAudioEditor)
};
