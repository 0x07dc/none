#ifndef FRAMEWORK_STATEMANAGER_H
#define FRAMEWORK_STATEMANAGER_H

#include <string>
#include <map>
#include <memory>
#include <queue>
#include "State.h"
#include "StateObserverSubject.h"
#include "HasParameterAttachment.h"


using namespace std;

namespace none {
    class StateManager : public StateObserverSubject {
        typedef string StateType;
        map<IdType, unique_ptr<State>> statesById;
        multimap<string, State*> statesByName;

        vector<juce::AudioProcessorValueTreeState::SliderAttachment*> sliderAttachments;
        vector<juce::AudioProcessorValueTreeState::ButtonAttachment*> buttonAttachments;
        vector<juce::AudioProcessorValueTreeState::ComboBoxAttachment*> comboBoxAttachments;

        IdType currentId = 0;

        IdType getNextId() {
            return currentId++;
        }
    public:

        void addParametersToJUCE(juce::AudioProcessor* audioProcessor){
            // Search the states for non-nullptr clientParameter s
            for(const auto& state : statesById){
                if (state.second->clientParameter)
                    audioProcessor->addParameter(static_cast<juce::AudioProcessorParameter*>(*state.second->clientParameter));

            }
        }


        void addParametersToJUCEVTS(juce::AudioProcessorValueTreeState* processorValueTreeState){
            // Search the states for non-nullptr clientParameter s
            std::function<juce::String(float)> valueToText =
                    [](float v){ return juce::String(v);};
            std::function<float(const juce::String&)> textToValue =
                    [](const juce::String& t){ return t.getFloatValue();};

            for(const auto& state : statesById){
                if (state.second->clientParameter){
                    if(!state.second->clientParameter->isRegisteredWithHost()){
/*                        auto* rangedAudioParameter =
                                static_cast<juce::RangedAudioParameter*>(*state.second->clientParameter);
                        std::unique_ptr<juce::RangedAudioParameter> parameterPtr =
                                std::unique_ptr<juce::RangedAudioParameter>(rangedAudioParameter);
                        processorValueTreeState->createAndAddParameter(move(parameterPtr));*/
                        processorValueTreeState->createAndAddParameter(
                                state.second->clientParameter->getParamRangedUP());
                        state.second->clientParameter->setIsRegisteredWithHost();
                    }

                    /*
                    switch(state.second->clientParameter->paramType){
                        case ParameterBase::ParamType::Float:
                            processorValueTreeState->createAndAddParameter(
                                    state.second->clientParameter->getId(),
                                    state.second->clientParameter->getId(),
                                    state.second->clientParameter->getId(),
                                    dynamic_cast<Parameter<float>*>(state.second->clientParameter.get())
                                        ->getNormalisableRange(),
                                    dynamic_cast<Parameter<float>*>(state.second->clientParameter.get())
                                        ->getDefaultValue(),
                                    valueToText,
                                    textToValue
                                    );
                            break;
                        case ParameterBase::ParamType::Int:
                            processorValueTreeState->createAndAddParameter(
                                    state.second->clientParameter->getId(),
                                    state.second->clientParameter->getId(),
                                    state.second->clientParameter->getId(),
                                    dynamic_cast<Parameter<int>*>(state.second->clientParameter.get())
                                    ->getNormalisableRangeFloat(),
                                    (float)dynamic_cast<Parameter<int>*>(state.second->clientParameter.get())
                                    ->getDefaultValue(),
                                    valueToText,
                                    textToValue
                                    );
                            break;
                        case ParameterBase::ParamType::Bool:
                            processorValueTreeState->createAndAddParameter(
                                    state.second->clientParameter->getId(),
                                    state.second->clientParameter->getId(),
                                    state.second->clientParameter->getId(),
                                    dynamic_cast<Parameter<bool>*>(state.second->clientParameter.get())
                                    ->getNormalisableRangeFloat(),
                                    (bool)dynamic_cast<Parameter<bool>*>(state.second->clientParameter.get())
                                    ->getDefaultValue(),
                                    valueToText,
                                    textToValue
                                    );
                            break;
                    }
                    */

                    // Add any attached components (JUCE takes ownership of pointer)
                    for(auto& slider : state.second->clientParameter->attachedSliders){
                        if(!dynamic_cast<HasParameterAttachment*>(slider.second)->isAttached()){
                            sliderAttachments.push_back(
                                    new juce::AudioProcessorValueTreeState::SliderAttachment(
                                            *processorValueTreeState,
                                            state.second->clientParameter->getId(),
                                            *slider.second));
                            dynamic_cast<HasParameterAttachment*>(slider.second)->setIsAttached();
                        }
                    }
                    for(auto& button : state.second->clientParameter->attachedButtons){
                        if(!dynamic_cast<HasParameterAttachment*>(button.second)->isAttached()){
                            buttonAttachments.push_back(
                                    new juce::AudioProcessorValueTreeState::ButtonAttachment(
                                            *processorValueTreeState,
                                            state.second->clientParameter->getId(),
                                            *button.second));
                            dynamic_cast<HasParameterAttachment*>(button.second)->setIsAttached();

                        }
                    }
                    for(auto& comboBox : state.second->clientParameter->attachedComboBoxes){
                        if(!dynamic_cast<HasParameterAttachment*>(comboBox.second)->isAttached()){
                            comboBoxAttachments.push_back(
                                    new juce::AudioProcessorValueTreeState::ComboBoxAttachment(
                                            *processorValueTreeState,
                                            state.second->clientParameter->getId(),
                                            *comboBox.second));
                            dynamic_cast<HasParameterAttachment*>(comboBox.second)->setIsAttached();

                        }
                    }


                }
            }
        }

        void notifyApp(string observed) override {
            // Go through all states and notify them of who changed
            for(const auto& state : statesByName){
                state.second->onObservedStateChange(observed);
            }
        }

        IdType addState(unique_ptr<State> state){
            IdType nextId = getNextId();
            string stateName = state->getName();
            statesById.emplace(nextId, move(state));
            State* newStatePtr = getState(nextId);
            statesByName.emplace(stateName, newStatePtr);
            return nextId;
        }

        State* getState(IdType stateId) {
            map<IdType, unique_ptr<State>>::iterator it = statesById.find(stateId);
            return it->second.get();
        }

        queue<State*> getStatesByName(const StateType& stateName) {
            pair<multimap<string, State*>::iterator,multimap<StateType, State*>::iterator> statesIter =
                    statesByName.equal_range(stateName);

            queue<State*> result;
            for (auto it=statesIter.first; it!=statesIter.second; ++it){
                result.push(it->second);
            }

            return result;
        }

        juce::ValueTree getValueTree(){
            juce::ValueTree valueTree{juce::Identifier("App")};
            for(const auto& state : statesById){
                valueTree.addChild(state.second->getValueTree(), (int)state.first, nullptr);
            }
            return valueTree;
        }

        void setFromValueTree(const juce::ValueTree& valueTree){
            for(const auto& state : statesById){
                state.second->setFromValueTree(valueTree.getChild((int)state.first));
            }
        }
    };
}

#endif //FRAMEWORK_STATEMANAGER_H
