#include "MainProcessor.h"


using namespace none;
using namespace none::app;

MainProcessor::MainProcessor(StateManager *stateManager) :
    generator(Generator(stateManager)),
    Processor(stateManager) {
    initState();
}

void MainProcessor::runProcess(juce::AudioBuffer<float> &buffer, juce::MidiBuffer &midiMessages) {
    generator.exec(buffer, midiMessages, audioProcessor, sampleRate, true);
}

unique_ptr<MainProcessorState> MainProcessor::provideState() {
    return make_unique<MainProcessorState>(stateManager);
}

void MainProcessorState::onObservedStateChange(const string& /*subjectName*/) {

}

string MainProcessorState::getName() {
    return "MainProcessor";
}

MainProcessorState::MainProcessorState(StateManager *stateManager) : State(stateManager) {}

