#ifndef FRAMEWORK_FREQUENCYSLIDER_H
#define FRAMEWORK_FREQUENCYSLIDER_H

#include <none_core/none_core.h>

namespace none {
    namespace app{
        struct FrequencySliderState : public State {
        protected:
            unique_ptr<ParameterBase> provideClientParameter() override;

        public:
            explicit FrequencySliderState(
                    StateManager *stateManager, std::function<void(float)> newClientParameterUpdateCallback);

            string getName() override;
            void onObservedStateChange(const string& subjectName) override;

            void setFrequencyModExternally(float newFrequencyMod){
                clientParameterUpdateCallback(newFrequencyMod);
/*                setFrequencyMod(newFrequencyMod);
                stateManager->notifyApp(getName());*/
            }

            void setFrequencyMod(float newFrequencyMod){
                getClientParameter()->setValue(newFrequencyMod);

            }

            float getFrequencyMod() {
                return (float)*getClientParameter();
            }

            Parameter<float>* getClientParameter(){
                return dynamic_cast<Parameter<float>*>(clientParameter.get());
            }

            juce::ValueTree getValueTree() override;

            void setFromValueTree(const juce::ValueTree &valueTree) override;



        };

        class FrequencySlider : public SliderWithState<FrequencySliderState> {
        protected:
            unique_ptr<FrequencySliderState> provideState() override;
            void initParameterAttachment() override;

        public:
            explicit FrequencySlider(StateManager* stateManager);

            void resized() override;

            void paint(juce::Graphics &g) override;

            void valueChanged() override;

        protected:
            void onClientParameterUpdate(float newValue) override;

        public:

            State* getState(){
                return state;
            }

        };
    }
}



#endif //FRAMEWORK_FREQUENCYSLIDER_H
