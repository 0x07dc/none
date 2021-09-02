#ifndef FRAMEWORK_PARAMETERINT_H
#define FRAMEWORK_PARAMETERINT_H


namespace none {
    class ParameterInt : public juce::AudioParameterInt {
        const int minValue, maxValue, defaultValue;
        int currentValue;
        std::string id;
    public:
        ParameterInt(
                const std::string &parameterId,
                int minValue,
                int maxValue,
                int defaultValue) :
                id(parameterId),
                minValue(minValue),
                maxValue(maxValue),
                defaultValue(defaultValue),
                currentValue(defaultValue),
                AudioParameterInt(
                        parameterId,
                        parameterId,
                        minValue,
                        maxValue,
                        defaultValue) {}

        float getValue() const override {
            return (float)currentValue;
        }

        void setValue(float newValue) override {
            currentValue = (int) newValue;
        }

        float getDefaultValue() const override {
            return (float)defaultValue;
        }

        float getValueForText(const juce::String& /*text*/) const override {
            return 0;
        }
    };
}

#endif //FRAMEWORK_PARAMETERINT_H
