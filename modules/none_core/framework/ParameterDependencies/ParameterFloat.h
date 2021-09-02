#include <utility>

#ifndef FRAMEWORK_PARAMETERFLOAT_H
#define FRAMEWORK_PARAMETERFLOAT_H


namespace none {
    class ParameterFloat : public juce::AudioParameterFloat {
        std::function<void(float)> notifyAppCommand;
        const float minValue, maxValue, defaultValue;
        float currentValue;
        const juce::NormalisableRange<float> normalisableRange;
        std::string parameterId;
    protected:
        void valueChanged(float newValue) override {
            currentValue = newValue;
            notifyAppCommand(newValue);
        }

    public:
        ParameterFloat(
                std::function<void(float)> notifyAppCommand,
                const std::string &newParameterId,
                const juce::NormalisableRange<float>& newNormalisableRange,
                float newDefaultValue) :
                notifyAppCommand(std::move(notifyAppCommand)),
                minValue(newNormalisableRange.start),
                maxValue(newNormalisableRange.end),
                normalisableRange(newNormalisableRange),
                defaultValue(newDefaultValue),
                currentValue(newDefaultValue),
                parameterId(newParameterId),
                AudioParameterFloat(
                        newParameterId,
                        newParameterId,
                        newNormalisableRange,
                        newDefaultValue) {}

        bool isAutomatable() const override {
            return true;
        }
        float getValue() const override {
            return currentValue;
        }

        void setValue(float newValue) override {
            currentValue = newValue;
            notifyAppCommand(newValue);
        }

        float getDefaultValue() const override {
            return defaultValue;
        }

        float getValueForText(const juce::String &text) const override {
            return 0;
        }
    };
}

#endif //FRAMEWORK_PARAMETERFLOAT_H
