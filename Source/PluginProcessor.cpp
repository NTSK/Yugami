/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
YugamiAudioProcessor::YugamiAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
}

YugamiAudioProcessor::~YugamiAudioProcessor()
{
    UserParams[MasterByPass] = 0.0f;
    UserParams[Gain] = 0.7f;
    UserParams[Threshold] = 1.0f;
    UserParams[Volume] = 0.7f;
}

//==============================================================================
const String YugamiAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool YugamiAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool YugamiAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

double YugamiAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int YugamiAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int YugamiAudioProcessor::getCurrentProgram()
{
    return 0;
}

void YugamiAudioProcessor::setCurrentProgram (int index)
{
}

const String YugamiAudioProcessor::getProgramName (int index)
{
    return {};
}

void YugamiAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void YugamiAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void YugamiAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool YugamiAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void YugamiAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    const int totalNumInputChannels  = getTotalNumInputChannels();
    const int totalNumOutputChannels = getTotalNumOutputChannels();

    for (int i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    if (UserParams[MasterByPass] == 1.0f) {
        return;
    }
    
    buffer.applyGain(pow(UserParams[Gain], 2)* 2.0f);
    float threshold = pow(UserParams[Threshold], 2);

    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        float* channelData = buffer.getWritePointer (channel);

        for (long buffNum = 0; buffNum<buffer.getNumSamples(); buffNum++)
        {
            float threshold = 0.7f;
            if (channelData[buffNum] >= threshold) {
                channelData[buffNum] = threshold;
            }
            else if (channelData[buffNum] <= threshold)
            {
                channelData[buffNum] = -threshold;
            }
        }
    }
    buffer.applyGain(pow(UserParams[Volume], 2) * 2.0f);
}

//==============================================================================
bool YugamiAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* YugamiAudioProcessor::createEditor()
{
    return new YugamiAudioProcessorEditor (*this);
}

//==============================================================================
void YugamiAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    XmlElement root("Root");
    XmlElement *el;
    el = root.createNewChildElement("Bypass");
    el->addTextElement(String(UserParams[MasterByPass]));
    el = root.createNewChildElement("Gain");
    el->addTextElement(String(UserParams[Gain]));
    el = root.createNewChildElement("Threshold");
    el->addTextElement(String(UserParams[Threshold]));
    el = root.createNewChildElement("Volume");
    el->addTextElement(String(UserParams[Volume]));
    copyXmlToBinary(root, destData);
    
}

void YugamiAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    XmlElement* pRoot = getXmlFromBinary(data, sizeInBytes);
    if (pRoot != NULL) {
        forEachXmlChildElement((*pRoot), pChild) {
            if (pChild->hasTagName("Bypass")) {
                String text = pChild->getAllSubText();
                setParameter(MasterByPass, text.getFloatValue());
            } else if (pChild->hasTagName("Gain")) {
                String text = pChild->getAllSubText();
                setParameter(Gain, text.getFloatValue());
            } else if (pChild->hasTagName("Threshold")) {
                String text = pChild->getAllSubText();
                setParameter(Threshold, text.getFloatValue());
            } else if (pChild->hasTagName("Volume")) {
                String text = pChild->getAllSubText();
                setParameter(Volume, text.getFloatValue());
            }
        }
        delete pRoot;
    }
}
//==============================================================================
int YugamiAudioProcessor::getNumParameters() { return totalNumParam; }

float YugamiAudioProcessor::getParameter(int index){
    if (index >= 0 && index < totalNumParam)
        return UserParams[index];
    else return 0;
}

void YugamiAudioProcessor::setParameter(int index, float value)
{
    switch (index) {
        case MasterByPass:
            UserParams[MasterByPass] = value;
            break;
        case Gain:
            UserParams[Gain] = value;
            break;
        case Threshold:
            UserParams[Threshold] = value;
            break;
        case Volume:
            UserParams[Volume] = value;
            break;
        default: return;
    }
}

const String YugamiAudioProcessor::getParameterName(int index)
{
    switch (index) {
        case MasterByPass: return "Master Bypass";
        case Gain: return "Gain";
        case Threshold: return "Threshold";
        case Volume: return "Volume";
        default: return String::empty;
    }
}
//==============================================================================
const String YugamiAudioProcessor::getParameterText(int index){
    switch (index) {
        case MasterByPass: return UserParams[MasterByPass] == 1.0f ? "BYPASS" : "EFFECT";
        case Gain: return String(Decibels::gainToDecibels(pow(UserParams[Gain], 2) * 2.0f), 1) + "db";
        case Threshold: return String(Decibels::gainToDecibels(pow(UserParams[Threshold], 2)), 1) + "db";
        case Volume: return String(Decibels::gainToDecibels(pow(UserParams[Volume], 2) * 2.0f), 1) + "db";
        default:return String::empty;
    }
}
//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new YugamiAudioProcessor();
}
