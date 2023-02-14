#include "PluginProcessor.h"
#include "PluginEditor.h"

ChorusPluginAudioProcessor::ChorusPluginAudioProcessor()
{
    dryWetParameter = new juce::AudioParameterFloat("drywet", "DryWet", 0.0f, 1.0f, 0.5f);
    delayTimeParameter = new juce::AudioParameterFloat("delaytime", "DelayTime", 0.0f, 1.0f, 0.5f);
    depthParameter = new juce::AudioParameterFloat("depth", "Depth", 0.0f, 1.0f, 0.5f);

    addParameter(dryWetParameter);
    addParameter(delayTimeParameter);
    addParameter(depthParameter);

    delayLine.reset(getSampleRate(), getBlockSize());
    chorus.reset();
}

ChorusPluginAudioProcessor::~ChorusPluginAudioProcessor()
{
}

void ChorusPluginAudioProcessor::prepareToPlay(juce::dsp::ProcessSpec& spec)
{
    delayLine.prepare(spec);
    chorus.prepare(spec);
}

void ChorusPluginAudioProcessor::releaseResources()
{
}

void ChorusPluginAudioProcessor::processBlock(juce::dsp::ProcessContextReplacing<float> context)
{
    auto delayTime = *delayTimeParameter;
    auto depth = *depthParameter;
    auto dryWet = *dryWetParameter;

    chorus.setDepth(depth);
    chorus.setRate(1.0f / delayTime);

    juce::dsp::ProcessContextNonReplacing<float> delayContext(context);
    delayLine.process(delayContext);

    juce::dsp::AudioBlock<float> block(context.getInputBlock());
    chorus.process(context, block);

    block.multiplyBy(dryWet);
    block.add(context.getInputBlock().getChannelPointer(0), context.getOutputBlock().getNumSamples(), 1 - dryWet);

    context.getOutputBlock().copyFrom(block);
}

juce::AudioProcessorEditor* ChorusPluginAudioProcessor::createEditor()
{
    return new ChorusPluginAudioEditor(*this);
}

bool ChorusPluginAudioProcessor::hasEditor() const
{
    return true;
}

const juce::String ChorusPluginAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool ChorusPluginAudioProcessor::acceptsMidi() const
{
    return false;
}

bool ChorusPluginAudioProcessor::producesMidi() const
{
    return false;
}

double ChorusPluginAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int ChorusPluginAudioProcessor::getNumPrograms()
{
    return 1;
}

int ChorusPluginAudioProcessor::getCurrentProgram()
{
    return 0;
}

void ChorusPluginAudioProcessor::setCurrentProgram(int index)
{
}

const juce::String ChorusPluginAudioProcessor::getProgramName(int index)
{
    return {};
}

void ChorusPluginAudioProcessor::changeProgramName(int index, const juce::String& newName)
{
}

void ChorusPluginAudioProcessor::getStateInformation(juce::MemoryBlock& destData)
{
}

void ChorusPluginAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
}

