
#include "../../Components/FrequencySlider.h"
#include "FrequencyMod.h"

using namespace none;
using namespace none::app;

FrequencyMod::FrequencyMod(StateManager* stateManager, GeneratorState* externalState) :
    StateMod<FrequencyModState, GeneratorState>(stateManager, externalState) {
    initState();
}

void FrequencyMod::runMod(int sampleNum) {
    const double& bps = externalState->bpm / 60;
    const double& sampleRate = externalState->sampleRate;
    const double& samplesPerBeat = sampleRate / bps;
    const double& newPPQPosition = externalState->ppqPosition + (sampleNum / samplesPerBeat);
    state->appliedFreqModRatio += ((float)state->modRatio - state->appliedFreqModRatio) / (float) sampleRate;

    externalState->frequencyModRatio = 1.0f + 0.01f *
            sinf( (
                    (float)newPPQPosition * 2.0f * (float)M_PI * state->appliedFreqModRatio
                    )
                );

}

unique_ptr<FrequencyModState> FrequencyMod::provideState() {
    return make_unique<FrequencyModState>(stateManager);
}


void FrequencyModState::onObservedStateChange(const string& subjectName) {
    if(subjectName == "FrequencySlider"){
        // Update this state
        auto* subjectState = dynamic_cast<FrequencySliderState*>(stateManager->getStatesByName(subjectName).front());
        modRatio = subjectState->getFrequencyMod();
    }
}

string FrequencyModState::getName() {
    return "FrequencyMod";
}

FrequencyModState::FrequencyModState(StateManager *stateManager) : State(stateManager) {
}


