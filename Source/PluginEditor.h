/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
//==============================================================================
class XcytheLookAndFeel_v1 : public juce::LookAndFeel_V4
{
public:
    void drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height,
                          float sliderPosProportional, float rotaryStartAngle,
                          float rotaryEndAngle, juce::Slider& slider) override;
    void drawToggleButton(juce::Graphics& g, juce::ToggleButton& togglebutton,
                          bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override;
};
//==============================================================================
class TransientFunctionGraph : public juce::Component, public juce::Timer
{
public:
    void initialize(Clipper<float>* clipper);
    void paint(juce::Graphics& g) override;
    void timerCallback() override;
    void update();
private:
    Clipper<float>* currentClipper{ nullptr };
    juce::uint64 time{ 0 };
    bool needUpdate{ false };
};
//==============================================================================
class DistortionTestAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    DistortionTestAudioProcessorEditor (DistortionTestAudioProcessor&);
    ~DistortionTestAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    XcytheLookAndFeel_v1 newLNF;
    juce::Slider inputGainSlider{ juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag,
                                  juce::Slider::TextEntryBoxPosition::NoTextBox };
    juce::Slider outputGainSlider{ juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag,
                                   juce::Slider::TextEntryBoxPosition::NoTextBox };
    juce::Slider clipSlider{ juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag,
                             juce::Slider::TextEntryBoxPosition::NoTextBox };
    juce::ComboBox clipperBox{ "Clippers" };
    juce::ToggleButton linkButton{ "Link" };
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    DistortionTestAudioProcessor& audioProcessor;
    TransientFunctionGraph graph;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DistortionTestAudioProcessorEditor)
};
