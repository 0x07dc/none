/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
NoneAppAudioProcessorEditor::NoneAppAudioProcessorEditor (NoneAppAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    Component* appGUI = audioProcessor.app.getGUIComponent();
    addAndMakeVisible(appGUI);

    setResizable(audioProcessor.app.getResizable(), audioProcessor.app.getResizable());
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize(appGUI->getWidth(), appGUI->getHeight());
}

NoneAppAudioProcessorEditor::~NoneAppAudioProcessorEditor()
{
}

//==============================================================================
void NoneAppAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

}

void NoneAppAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
