#pragma once

#include <JuceHeader.h>

class ChorusPluginAudioProcessor : public juce::AudioProcessor
{
public:
    ChorusPluginAudioProcessor();
    ~ChorusPluginAudioProcessor() override;

    void prepareToPlay(juce::dsp::ProcessSpec&) override;
    void releaseResources() override;
    void processBlock(juce::dsp::ProcessContextReplacing<float>) override;

    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    double getTailLengthSeconds() const override;

    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram(int index) override;
    const juce::String getProgramName(int index) override;
    void changeProgramName(int index, const juce::String& newName) override;

    void getStateInformation(juce::MemoryBlock& destData) override;
    void setStateInformation(const void* data, int sizeInBytes) override;

private:
    juce::AudioParameterFloat* dryWetParameter;
    juce::AudioParameterFloat* delayTimeParameter;
    juce::AudioParameterFloat* depthParameter;
    juce::dsp::DelayLine<float, juce::dsp::DelayLineInterpolationTypes::Linear> delayLine;
    juce::dsp::Chorus<float> chorus;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ChorusPluginAudioProcessor)
};
