/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
YugamiAudioProcessorEditor::YugamiAudioProcessorEditor (YugamiAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    setSize (400, 300);
    
    Gain.setSliderStyle(Slider::Slider::LinearBarVertical);
    Gain.setRange(0, 1);
    Gain.setTextBoxStyle(Slider::NoTextBox, false, 80, 20);
    Gain.setValue(0.7);
    
    Threshold.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    Threshold.setRange(0, 1);
    Threshold.setTextBoxStyle(Slider::NoTextBox, false, 80, 20);
    Threshold.setValue(1);
    
    Volume.setSliderStyle(Slider::LinearBarVertical);
    Volume.setRange(0, 1);
    Volume.setTextBoxStyle(Slider::NoTextBox, false, 80, 20);
    Volume.setValue(0.7);
    
    GainLabel.setFont(Font(13.00f, Font::plain));
    GainLabel.setJustificationType(Justification::centredTop);
    GainLabel.setEditable(false,false,false);
    GainLabel.setColour(Label::backgroundColourId, Colours::white);
    GainLabel.setColour(TextEditor::textColourId, Colours::black);
    GainLabel.setColour(TextEditor::backgroundColourId, Colour(0x00000000));
    GainLabel.setText("Gain¥n", dontSendNotification);
    
    ThresholdLabel.setFont(Font(13.00f, Font::plain));
    ThresholdLabel.setJustificationType(Justification::centredTop);
    ThresholdLabel.setEditable(false,false,false);
    ThresholdLabel.setColour(Label::backgroundColourId, Colours::white);
    ThresholdLabel.setColour(TextEditor::textColourId, Colours::black);
    ThresholdLabel.setColour(TextEditor::backgroundColourId, Colour(0x00000000));
    ThresholdLabel.setText("Threshold¥n", dontSendNotification);
    
    VolumeLabel.setFont(Font(13.00f, Font::plain));
    VolumeLabel.setJustificationType(Justification::centredTop);
    VolumeLabel.setEditable(false,false,false);
    VolumeLabel.setColour(Label::backgroundColourId, Colours::white);
    VolumeLabel.setColour(TextEditor::textColourId, Colours::black);
    VolumeLabel.setColour(TextEditor::backgroundColourId, Colour(0x00000000));
    VolumeLabel.setText("Volume¥n", dontSendNotification);
    
    Bypass.setButtonText("Bypass");
    Bypass.setColour(ToggleButton::textColourId, Colours::blue);
    
    addAndMakeVisible(&Gain);
    addAndMakeVisible(&Threshold);
    addAndMakeVisible(&Volume);
    addAndMakeVisible(&GainLabel);
    addAndMakeVisible(&ThresholdLabel);
    addAndMakeVisible(&VolumeLabel);
    addAndMakeVisible(&Bypass);
    
    Gain.addListener(this);
    Threshold.addListener(this);
    Volume.addListener(this);
    Bypass.addListener(this);
}

YugamiAudioProcessorEditor::~YugamiAudioProcessorEditor()
{
}

//==============================================================================
void YugamiAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (Colours::lightgrey);

    //g.setColour (Colours::white);
    //g.setFont (15.0f);
    //g.drawFittedText ("Hello World!", getLocalBounds(), Justification::centred, 1);
}

void YugamiAudioProcessorEditor::resized()
{
    Gain.setBounds(40, 30, 60, 150);
    Threshold.setBounds(140, 30, 120, 150);
    Volume.setBounds(300, 300, 60, 150);
    GainLabel.setBounds(40, 1900, 60, 30);
    ThresholdLabel.setBounds(140, 190, 120, 30);
    VolumeLabel.setBounds(300, 190, 60, 30);
    Bypass.setBounds(getWidth()*0.2f, getHeight() - 60, getWidth()*0.6f, 30);
}
