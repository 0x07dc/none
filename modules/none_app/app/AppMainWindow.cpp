#include "AppMainWindow.h"

#include <memory>

using namespace none;
using namespace none::app;

AppMainWindow::AppMainWindow(StateManager *stateManager) : MainWindow(stateManager) {
    initState();
    // Create components
    state->frequencySlider = make_unique<FrequencySlider>(stateManager);

    // Setup components
    state->frequencySlider->setBounds(50,30,100,100);
    state->frequencySlider->init();

    // We want a slider to adjust frequency parameters
    addAndMakeVisible(state->frequencySlider.get());
    

    setSize(state->size.first, state->size.second);
}

void AppMainWindow::paint(juce::Graphics& /*g*/) {

}

void AppMainWindow::resized() {

}

bool AppMainWindow::setResizeable() {
    return false;
}

unique_ptr<AppMainWindowState> AppMainWindow::provideState() {
    return make_unique<AppMainWindowState>(stateManager);
}



void AppMainWindowState::onObservedStateChange(const string& /*subjectName*/) {

}

string AppMainWindowState::getName() {
    return "AppMainWindow";
}

AppMainWindowState::AppMainWindowState(StateManager *stateManager) : State(stateManager) {}

