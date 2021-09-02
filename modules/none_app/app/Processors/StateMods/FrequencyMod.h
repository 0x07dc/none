#ifndef FRAMEWORK_FREQUENCYMOD_H
#define FRAMEWORK_FREQUENCYMOD_H


#include "../GeneratorState.h"

namespace none {
    namespace app {
        struct FrequencyModState : public State {
            float modRatio = 1;
            float appliedFreqModRatio = 1.0f;

        public:
            explicit FrequencyModState(StateManager *stateManager);

            void onObservedStateChange(const std::string& subjectName) override;

            string getName() override;
        };

        class FrequencyMod : public StateMod<FrequencyModState, GeneratorState> {
        protected:
            unique_ptr<FrequencyModState> provideState() override;

        public:
            FrequencyMod(StateManager* stateManager, GeneratorState* externalState);
            void runMod(int sampleNum) override;

        };
    }
}

#endif //FRAMEWORK_FREQUENCYMOD_H
