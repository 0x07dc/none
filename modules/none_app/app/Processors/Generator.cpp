#include "Generator.h"

using namespace none;
using namespace none::app;

Generator::Generator(StateManager *stateManager) : Processor(stateManager) {
    initState();
    frequencyMod = make_unique<FrequencyMod>(stateManager, state);
}

void Generator::runProcess(juce::AudioBuffer<float> &buffer, juce::MidiBuffer &midiMessages) {
    // Update state (for state interaction)
    state->sampleRate = sampleRate;
    state->ppqPosition = ppqPosition;
    state->bpm = bpm;

    assert(sampleRate != 0);

    lib::ADSRMemento adsrMemento = lib::ADSRMemento(
            0.3,
            0.7, 
            0.5,
            0.1);
    lib::ADSR::readMidiMessages(sampleRate,midiMessages, adsrs, adsrMemento);
    // Go through ADSR and run addNote to add the note to the buffer
    for(auto& adsr : adsrs){
        addNote(buffer, adsr.first, adsr.second);
        adsr.second.nextBuffer();
    }


}

float Generator::getFrequencyModRatio() const {
    return state->frequencyModRatio;
}

void Generator::setFrequencyModRatio(float newFrequencyModRatio) {
    state->frequencyModRatio = newFrequencyModRatio;
}

unique_ptr<GeneratorState> Generator::provideState() {
    return make_unique<GeneratorState>(stateManager);
}

void Generator::addNote(juce::AudioBuffer<float> &buffer, Generator::midiNoteNum midiNoteNum, lib::ADSR& adsr) {
    // Run process
    double frequencyOfNewNote = 440 * pow(2, (midiNoteNum - 69) / 12);

    // Fill buffer with sine wave at frequency
    float newSample;
    adsr.resizeLongBufferIdx(totalNumOutputChannels);
    for (int channel = 0; channel < totalNumOutputChannels; ++channel)
    {
        state->currentChannel = channel;

        auto* channelData = buffer.getWritePointer (channel);
        auto* channelDataRead = buffer.getReadPointer(channel);
        for(int sampleNum = 0; sampleNum < buffer.getNumSamples(); ++sampleNum){
            frequencyMod->runMod(sampleNum);

            LargeNum newSampleNum = adsr.getAndIncrementLongBufferIdx(channel);



            newSample = 0.5f *
                    adsr.getAmplitude(sampleNum) * 
                    (float)cos(
                                (double) newSampleNum /
                                (double) sampleRate * 
                                M_PI * 2.0 *
                                frequencyOfNewNote * 2.0 * (double)state->frequencyModRatio);

            newSample += channelDataRead[sampleNum];
            newSample = newSample > 1 ? 1 : newSample < -1 ? -1 : newSample;
            
            channelData[sampleNum] = newSample;
        }

    }
}


void GeneratorState::onObservedStateChange(const string& /*subjectName*/) {

}

string GeneratorState::getName() {
    return "Generator";
}

GeneratorState::GeneratorState(StateManager *stateManager) : State(stateManager) {}

