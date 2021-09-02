#ifndef FRAMEWORK_COMPONENTWITHSTATE_H
#define FRAMEWORK_COMPONENTWITHSTATE_H

namespace none{
    template<class StateType>
    class ComponentWithState  : public juce::Component, public HasState<StateType> {
    protected:
        virtual unique_ptr<StateType> provideState() override = 0;

    public:
        ComponentWithState() = delete;
        explicit ComponentWithState(StateManager* stateManager) : HasState<StateType>(stateManager){};

        // Inherited via Component
        void resized() override = 0;

        void paint(juce::Graphics& g) override = 0;

    };
}

#endif //FRAMEWORK_COMPONENTWITHSTATE_H
