#ifndef FRAMEWORK_PARAMETERBOOL_H
#define FRAMEWORK_PARAMETERBOOL_H

namespace none {
    class ParameterBool : public juce::AudioParameterBool {
        const bool defaultValue;
        bool currentValue;
        std::string id;
    public:
        ParameterBool(
                const std::string &parameterId,
                bool defaultValue) :
                id(parameterId),
                defaultValue(defaultValue),
                currentValue(defaultValue),
                AudioParameterBool(
                        parameterId,
                        parameterId,
                        defaultValue) {}

        float getValue() const override {
            return (float)currentValue;
        }

        void setValue(float newValue) override {
            currentValue = (bool)newValue;
        }

        float getDefaultValue() const override {
            return (float)defaultValue;
        }

        float getValueForText(const juce::String &text) const override {
            return 0;
        }
    };
}

#endif //FRAMEWORK_PARAMETERBOOL_H
