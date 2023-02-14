#include "PluginEditor.h"

ChorusPluginAudioEditor::ChorusPluginAudioEditor(ChorusPluginAudioProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p)
{
    setSize(400, 300);

    dryWetSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    dryWetSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    dryWetSlider.setRange(0.0f, 1.0f, 0.01f);
    dryWetSlider.setValue(0.5f);
    dryWetSlider.setSkewFactorFromMidPoint(0.5f);
    addAndMakeVisible(dryWetSlider);
    dryWetSlider.addListener(this);

    delayTimeSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    delayTimeSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    delayTimeSlider.setRange(0.0f, 1.0f, 0.01f);
    delayTimeSlider.setValue(0.5f);
    delayTimeSlider.setSkewFactorFromMidPoint(0.5f);
    addAndMakeVisible(delayTimeSlider);
    delayTimeSlider.addListener(this);

    depthSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    depthSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    depthSlider.setRange(0.0f, 1.0f, 0.01f);
    depthSlider.setValue(0.5f);
    depthSlider.setSkewFactorFromMidPoint(0.5f);
    addAndMakeVisible(depthSlider);
    depthSlider.addListener(this);
}

ChorusPluginAudioEditor::~ChorusPluginAudioEditor()
{
}

void ChorusPluginAudioEditor::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);

    g.setColour(juce::Colours::white);
    g.setFont(15.0f);
    g.drawText("Chorus Plugin", getLocalBounds(), juce::Justification::centredTop);
}

void ChorusPluginAudioEditor::resized()
{
    auto area = getLocalBounds();

    auto sliders = area.removeFromTop(area.getHeight() / 2);

    dryWetSlider.setBounds(sliders.removeFromLeft(sliders.getWidth() / 3).reduced(10));
    delayTimeSlider.setBounds(sliders.removeFromLeft(sliders.getWidth() / 2).reduced(10));
    depthSlider.setBounds(sliders.reduced(10));
}
