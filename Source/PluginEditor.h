/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"


//==============================================================================
/**
*/
class YugamiAudioProcessorEditor  : public AudioProcessorEditor,
                                    private Slider::Listener,
                                    private Button::Listener
{
public:
    YugamiAudioProcessorEditor (YugamiAudioProcessor&);
    ~YugamiAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    void sliderValueChanged(Slider *changeSlider) override;
    void buttonClicked(Button* clickedButton) override;
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    YugamiAudioProcessor& processor;
    
    Slider Gain;
    Slider Threshold;
    Slider Volume;
    Label GainLabel;
    Label ThresholdLabel;
    Label VolumeLabel;
    ToggleButton Bypass;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (YugamiAudioProcessorEditor)
};
