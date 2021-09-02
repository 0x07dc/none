/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
NoneAppAudioProcessor::NoneAppAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ),
    processorValueTreeState(*this, nullptr)
#endif
{
    app.addParametersToJUCE(this);
    // This function is under construction, as an alternative to the above,
    // in an effort to solve the lack of automation issue present (in FL Studio)
    //app.addParametersToJUCEVTS(&processorValueTreeState);
    
}

NoneAppAudioProcessor::~NoneAppAudioProcessor()
{
}

//==============================================================================
const juce::String NoneAppAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool NoneAppAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool NoneAppAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool NoneAppAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double NoneAppAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int NoneAppAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int NoneAppAudioProcessor::getCurrentProgram()
{
    return 0;
}

void NoneAppAudioProcessor::setCurrentProgram (int /*index*/)
{
}

const juce::String NoneAppAudioProcessor::getProgramName (int /*index*/)
{
    return {};
}

void NoneAppAudioProcessor::changeProgramName (int /*index*/, const juce::String& /*newName*/)
{
}

//==============================================================================
void NoneAppAudioProcessor::prepareToPlay (double /*sampleRate*/, int /*samplesPerBlock*/)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..

}

void NoneAppAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool NoneAppAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
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

void NoneAppAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    int sampleRate = (int)getSampleRate();
    app.runProcess(buffer, midiMessages, this, sampleRate);
}

//==============================================================================
bool NoneAppAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* NoneAppAudioProcessor::createEditor()
{
    return new NoneAppAudioProcessorEditor (*this);
}

//==============================================================================
void NoneAppAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    juce::ValueTree valueTree = app.getValueTree();
    juce::XmlElement xml(*valueTree.createXml());
    copyXmlToBinary(xml, destData);
}

void NoneAppAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    std::unique_ptr<juce::XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));

    if (xmlState.get() != nullptr) {
        juce::ValueTree valueTree = juce::ValueTree::fromXml(*xmlState);
        if (valueTree.getType().toString() == "App")
            app.setFromValueTree(valueTree);
    }
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new NoneAppAudioProcessor();
}
