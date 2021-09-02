#ifndef FRAMEWORK_SLIDERWITHSTATE_H
#define FRAMEWORK_SLIDERWITHSTATE_H

#include "../HasParameterAttachment.h"

namespace none {
    template<class StateType>
    class SliderWithState : public HasState<StateType>, public juce::Slider, public HasParameterAttachment {
        bool sliderIsChanging = false;
    protected:
        virtual unique_ptr<StateType> provideState() override = 0;

        void startedDragging() override {
            if(sliderIsChanging) return;
            if(HasState<StateType>::state != nullptr && HasState<StateType>::state->clientParameter != nullptr){
                sliderIsChanging = true;
                static_cast<juce::AudioProcessorParameter*>(*HasState<StateType>::state->clientParameter)->beginChangeGesture();
            }
        }

        void stoppedDragging() override {
            if(!sliderIsChanging) return;
            if(HasState<StateType>::state != nullptr && HasState<StateType>::state->clientParameter != nullptr){
                static_cast<juce::AudioProcessorParameter*>(*HasState<StateType>::state->clientParameter)->endChangeGesture();
                sliderIsChanging = false;
            }
        }


    public:
        explicit SliderWithState(StateManager* stateManager) : HasState<StateType>(stateManager){};

        void init(){
            initParameterAttachment();
        }



        // Inherited via Component
        virtual void resized() override {
            juce::Slider::resized();
        };
        virtual void paint(juce::Graphics& g) override {
            juce::Slider::paint(g);
        };

        // Inherited via Slider
        virtual void valueChanged() override = 0;




    };
}

#endif //FRAMEWORK_SLIDERWITHSTATE_H
