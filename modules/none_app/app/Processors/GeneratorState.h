#ifndef FRAMEWORK_GENERATORSTATE_H
#define FRAMEWORK_GENERATORSTATE_H

namespace none {
    namespace app{
        struct GeneratorState : public State {
            float frequencyModRatio = 1.0f;
            int sampleRate = 10;
            int currentChannel = 0;
            double ppqPosition = 0;
            double bpm = 0;

        public:
            explicit GeneratorState(StateManager *stateManager);
            string getName() override;
            void onObservedStateChange(const string& subjectName) override;
        };
    }
}

#endif //FRAMEWORK_GENERATORSTATE_H
