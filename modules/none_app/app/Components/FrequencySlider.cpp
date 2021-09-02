#include "FrequencySlider.h"

#define _USE_MATH_DEFINES
#include <math.h>


using namespace none;
using namespace none::app;

FrequencySlider::FrequencySlider(StateManager *stateManager) : SliderWithState(stateManager) {
    initState();
    state->clientParameter->attachSlider(this);
    int startingVal = 1;


    string postfix = " Cycles";
    string componentId = typeid(*this).name();
    map<string, float> range = map<string, float>();
    range["min"] = 0.01f;
    range["max"] = 30.0f;
    range["interval"] = 0.01f;

    // Build slider
    setComponentID(componentId);
    setRange(range["min"], range["max"], range["interval"]);
    setPopupMenuEnabled(true);
    setValue(startingVal, juce::dontSendNotification);
    setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    setRotaryParameters((float)M_PI * 1.2f, (float)M_PI * 2.8f, true);
    setTextBoxStyle(Slider::TextBoxBelow, false, 70, 20);
    setTextValueSuffix(postfix);
    //setMouseDragSensitivity(500);
    setVelocityBasedMode(false);
    // TODO delete this
/*    parameterAttachment = std::make_unique<juce::SliderParameterAttachment>(
            *static_cast<juce::RangedAudioParameter*>(*state->clientParameter),
            *this,
            nullptr);*/

}

unique_ptr<FrequencySliderState> FrequencySlider::provideState() {
    unique_ptr<FrequencySliderState> frequencySliderState = make_unique<FrequencySliderState>(
            stateManager, getClientParameterUpdateCallback());
    frequencySliderState->setComponent(this);
    return move(frequencySliderState);
}

void FrequencySlider::resized() {
    SliderWithState::resized();
}

void FrequencySlider::paint(juce::Graphics& g) {
    SliderWithState::paint(g);
}

void FrequencySlider::valueChanged() {
    state->setFrequencyMod((float) getValue());
    stateManager->notifyApp(state->getName());
}

void FrequencySlider::initParameterAttachment() {

}

void FrequencySlider::onClientParameterUpdate(float newValue) {
    setValue(newValue);
    valueChanged();
}

void FrequencySliderState::onObservedStateChange(const string& subjectName) {

}

string FrequencySliderState::getName() {
    return "FrequencySlider";
}

FrequencySliderState::FrequencySliderState(
        StateManager *stateManager, std::function<void(float)> newClientParameterUpdateCallback) :
        State(stateManager, newClientParameterUpdateCallback) {
    init();
}

juce::ValueTree FrequencySliderState::getValueTree() {
    juce::ValueTree valueTree((juce::Identifier(getName())));
    valueTree.setProperty(juce::Identifier("modRatio"), getFrequencyMod(), nullptr);
    return valueTree;
}

void FrequencySliderState::setFromValueTree(const juce::ValueTree &valueTree) {
    setFrequencyModExternally((float) valueTree.getProperty("modRatio"));
}

unique_ptr<ParameterBase> FrequencySliderState::provideClientParameter() {
    std::function<void(float)> notifyAppCommand = [this](float newValue){
        //stateManager->notifyApp("FrequencySlider");
        const juce::MessageManagerLock mmLock;
        dynamic_cast<juce::Slider*>(component)->setValue(newValue);
    };
    juce::NormalisableRange<float> normalisableRange = juce::NormalisableRange<float>(0.01f, 30.0f);
    return make_unique<Parameter<float>>(notifyAppCommand, "FrequencyModSpeed", normalisableRange, 1.0f);
}

