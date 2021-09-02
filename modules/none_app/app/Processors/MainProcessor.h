#ifndef FRAMEWORK_MAINPROCESSOR_H
#define FRAMEWORK_MAINPROCESSOR_H

#include <none_core/none_core.h>
#include "Generator.h"

namespace none {
    namespace app {
        struct MainProcessorState : public State {
        public:
            explicit MainProcessorState(StateManager *stateManager);

            string getName() override;
            void onObservedStateChange(const string& subjectName) override;
        };
        class MainProcessor : public Processor<MainProcessorState> {
            Generator generator;
        protected:
            void runProcess(juce::AudioBuffer<float> &buffer, juce::MidiBuffer &midiMessages) override;
            unique_ptr<MainProcessorState> provideState() override;

        public:
            explicit MainProcessor(StateManager *stateManager);

        };
    }
}




#endif //FRAMEWORK_MAINPROCESSOR_H
