#ifndef FRAMEWORK_PARAMETER_H
#define FRAMEWORK_PARAMETER_H

#include <juce_audio_utils/juce_audio_utils.h>

#include <utility>
#include "ParameterDependencies/ParameterFloat.h"
#include "ParameterDependencies/ParameterInt.h"
#include "ParameterDependencies/ParameterBool.h"
#include "TypeDef.h"


namespace none {
    class ParameterBase {
        IdType currentAttachmentId = 0;
        std::string id;
        bool _isRegisteredWithHost = false;

    protected:
        std::function<void(float)> notifyAppCommand;
    public:
        enum class ParamType{ Float, Int, Bool };

        ParamType paramType;

        explicit ParameterBase(std::function<void(float)> notifyAppCommand, std::string id, ParameterFloat* parameter) :
            notifyAppCommand(std::move(notifyAppCommand)), paramType(ParamType::Float), id(id), paramFloat(parameter){};

        explicit ParameterBase(std::function<void(float)> notifyAppCommand, std::string id, ParameterInt* parameter) :
            notifyAppCommand(std::move(notifyAppCommand)), paramType(ParamType::Int), id(id), paramInt(parameter){};

        explicit ParameterBase(std::function<void(float)> notifyAppCommand, std::string id, ParameterBool* parameter) :
            notifyAppCommand(std::move(notifyAppCommand)), paramType(ParamType::Bool), id(id), paramBool(parameter){};

        virtual ~ParameterBase() = default;

        std::map<IdType, juce::Slider*> attachedSliders;
        std::map<IdType, juce::Button*> attachedButtons;
        std::map<IdType, juce::ComboBox*> attachedComboBoxes;

        // JUCE takes ownership of the parameter
        ParameterFloat* paramFloat = nullptr;
        ParameterInt* paramInt = nullptr;
        ParameterBool* paramBool = nullptr;

        bool paramIsOwned = false;

        void attachSlider(juce::Slider* newSlider){
            attachedSliders[currentAttachmentId++] = newSlider;
        }
        void attachButton(juce::Button* newButton){
            attachedButtons[currentAttachmentId++] = newButton;
        }
        void attachComboBox(juce::ComboBox* newComboBox){
            attachedComboBoxes[currentAttachmentId++] = newComboBox;
        }
        std::string getId(){
            return id;
        }

        /// Sets that the parameter has been registered with host (no undo)
        void setIsRegisteredWithHost(){
            _isRegisteredWithHost = true;
        }

        bool isRegisteredWithHost() const{
            return _isRegisteredWithHost;
        }


        juce::AudioProcessorParameter* getParam() const {
            switch(paramType){
                case ParamType::Float:
                    return paramFloat;
                case ParamType::Int:
                    return paramInt;
                case ParamType::Bool:
                    return paramBool;
            }
            throw std::runtime_error("Invalid parameter type (paramType)");
        }

        juce::RangedAudioParameter* getParamRanged() const {
            switch(paramType){
                case ParamType::Float:
                    return paramFloat;
                case ParamType::Int:
                    return paramInt;
                case ParamType::Bool:
                    return paramBool;
            }
            throw std::runtime_error("Invalid parameter type (paramType)");
        }

        std::unique_ptr<juce::RangedAudioParameter> getParamRangedUP() {
            if(!paramIsOwned){
                paramIsOwned = true;
                switch(paramType){
                    case ParamType::Float:
                        return std::unique_ptr<juce::RangedAudioParameter>(paramFloat);
                    case ParamType::Int:
                        return std::unique_ptr<juce::RangedAudioParameter>(paramInt);
                    case ParamType::Bool:
                        return std::unique_ptr<juce::RangedAudioParameter>(paramBool);
                }
                throw std::runtime_error("Invalid parameter type (paramType)");
            } else {
                throw std::runtime_error("Parameter is already owned");
            }
        }

        explicit operator juce::AudioProcessorParameter*() const {
            return getParam();
        }
        explicit operator juce::RangedAudioParameter*() const {
            return getParamRanged();
        }
    };
    template<class T>
    class Parameter : public ParameterBase {
        T currentValue;
        T defaultValue;
        juce::NormalisableRange<T> normalisableRange{(T)0, (T)10};

    public:
        Parameter<T>() = delete;
        Parameter<T>(
                std::function<void(float)> notifyAppCommand,
                const std::string& id,
                const juce::NormalisableRange<T>& normalisableRange,
                T defaultValue);
        Parameter<T>(std::function<void(float)> notifyAppCommand,
                     const std::string& id, T min, T max, T defaultValue);
        Parameter<T>(std::function<void(float)> notifyAppCommand,
                     const std::string& id, T defaultValue);

        T getDefaultValue(){
            return defaultValue;
        }

        juce::NormalisableRange<T> getNormalisableRange(){
            return normalisableRange;
        }

        juce::NormalisableRange<float> getNormalisableRangeFloat(){
            return {(float)normalisableRange.start, (float)normalisableRange.end};
        }

        void setValue(float newValue) {
            if(currentValue == newValue) return;
            T updatedValue = (T) newValue;
            currentValue = updatedValue;
            switch (paramType) {
                case ParameterBase::ParamType::Bool:
                {
                    auto* parameter = dynamic_cast<ParameterBool*>(getParam());
                    parameter->setValueNotifyingHost((float)(bool)updatedValue);
                }
                    break;
                case ParameterBase::ParamType::Int:
                {
                    auto* parameter = dynamic_cast<ParameterInt*>(getParam());
                    parameter->setValueNotifyingHost((float)(int)updatedValue);
                }
                    break;
                case ParameterBase::ParamType::Float:
                {
                    auto* parameter = dynamic_cast<ParameterFloat*>(getParam());
                    parameter->setValueNotifyingHost((float)updatedValue);
                }
                    break;
            }
            notifyAppCommand(updatedValue);

        }


        explicit operator float(){
            return (float) currentValue;
        }
        explicit operator bool(){
            return (bool) currentValue;
        }
        explicit operator int(){
            return (int) currentValue;
        }



    };




}


#endif //FRAMEWORK_PARAMETER_H
