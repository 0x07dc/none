
#ifndef FRAMEWORK_STATE_H
#define FRAMEWORK_STATE_H

#include <utility>
#include <vector>
#include <memory>
#include "StateObserver.h"
#include "Parameter.h"

using namespace std;

namespace none {
    class StateManager;
    class State : public StateObserver {

    protected:
        StateManager* stateManager;
        juce::Component* component = nullptr;


    public:

        virtual juce::ValueTree getValueTree(){
            return juce::ValueTree(juce::Identifier(getName()));
        };

        virtual void setFromValueTree(const juce::ValueTree& /*valueTree*/) {

        };

        virtual string getName(){
            return "Unnamed";
        };


        virtual unique_ptr<ParameterBase> provideClientParameter() {
            return nullptr;
        };


        unique_ptr<ParameterBase> clientParameter = nullptr;
        std::function<void(float)> clientParameterUpdateCallback = [](float /*newValue*/) {};

        State() = delete;
        State(const State& state) = default;

        explicit State(
            StateManager* stateManager,
            std::function<void(float)> newClientParameterUpdateCallback = [](float /*newValue*/) {}) :
            stateManager(stateManager),
            clientParameterUpdateCallback(std::move(newClientParameterUpdateCallback)){};

        virtual ~State() = default;

        void init(){
            clientParameter = provideClientParameter();
        }

        void setComponent(juce::Component* newComponent){
            component = newComponent;
        };

        void onObservedStateChange(const std::string& /*subjectName*/) override {

        };


    };
}

#endif //FRAMEWORK_STATE_H
