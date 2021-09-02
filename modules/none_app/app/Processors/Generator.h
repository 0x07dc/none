#ifndef FRAMEWORK_GENERATOR_H
#define FRAMEWORK_GENERATOR_H

#include <none_core/none_core.h>
#include <assert.h>
#include "StateMods/FrequencyMod.h"
#include "GeneratorState.h"

namespace none {
    namespace app{
        class Generator : public Processor<GeneratorState> {
            unique_ptr<FrequencyMod> frequencyMod;
            typedef float midiNoteNum;
            map<midiNoteNum, lib::ADSR> adsrs;

        protected:
            unique_ptr<GeneratorState> provideState() override;
            void runProcess(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages) override;
            void addNote(juce::AudioBuffer<float>& buffer, midiNoteNum midiNoteNum, lib::ADSR& adsr);


        public:
            explicit Generator(StateManager* stateManager);

            float getFrequencyModRatio() const;
            void setFrequencyModRatio(float frequencyModRatio);



        };
    }
}



#endif //FRAMEWORK_GENERATOR_H
