#include "Parameter.h"

#include <utility>

using namespace std;
using namespace none;

template<class T>
Parameter<T>::Parameter(
        std::function<void(float)> notifyAppCommand,
        const std::string &id,
        const juce::NormalisableRange<T>& normalisableRange,
        T defaultValue) {
    std::string typeName(typeid(T).name());
    throw std::runtime_error("Invalid Parameter Type (" + typeName + ")");
}

template<class T>
Parameter<T>::Parameter(
        std::function<void(float)> notifyAppCommand,
        const std::string &id, T min, T max, T defaultValue) {
    std::string typeName(typeid(T).name());
    throw std::runtime_error("Invalid Parameter Type (" + typeName + ")");
}

template<class T>
Parameter<T>::Parameter(
        std::function<void(float)> notifyAppCommand,
        const std::string &id, T defaultValue) {
    std::string typeName(typeid(T).name());
    throw std::runtime_error("Invalid Parameter Type (" + typeName + ")");
}

template<>
Parameter<float>::Parameter(
        std::function<void(float)> notifyAppCommand,
        const string& newId,
        const juce::NormalisableRange<float>& newNormalisableRange,
        float newDefaultValue) :
        currentValue(newDefaultValue),
        defaultValue(newDefaultValue),
        normalisableRange(newNormalisableRange),
        ParameterBase(
                std::move(notifyAppCommand),
                newId,
                new ParameterFloat(
                    [this](float newValue){setValue(newValue);},
                    newId,
                    newNormalisableRange,
                    newDefaultValue)){

}

template<>
Parameter<int>::Parameter(
        std::function<void(float)> notifyAppCommand,
        const string& newId,
        int min,
        int max,
        int newDefaultValue) :
        currentValue(newDefaultValue),
        defaultValue(newDefaultValue),
        normalisableRange(juce::NormalisableRange<int> (min, max)),
        ParameterBase(
                std::move(notifyAppCommand),
                newId,
                new ParameterInt(newId, min, max, newDefaultValue)){}

template<>
Parameter<bool>::Parameter(
        std::function<void(float)> notifyAppCommand,
        const string& newId,
        bool newDefaultValue) :
        currentValue(newDefaultValue),
        defaultValue(newDefaultValue),
        ParameterBase(
                std::move(notifyAppCommand),
                newId,
                new ParameterBool(newId, newDefaultValue)){}
