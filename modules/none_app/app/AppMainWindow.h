#ifndef FRAMEWORK_APPMAINWINDOW_H
#define FRAMEWORK_APPMAINWINDOW_H


#include <none_core/none_core.h>
#include "Components/FrequencySlider.h"

namespace none{
    namespace app {
        struct AppMainWindowState : public State {
            unique_ptr<FrequencySlider> frequencySlider;
            pair<int, int> size = {200,200};

        public:
            explicit AppMainWindowState(StateManager *stateManager);

            string getName() override;
            void onObservedStateChange(const string& subjectName) override;
        };

        class AppMainWindow : public MainWindow<AppMainWindowState> {
        protected:
            unique_ptr<AppMainWindowState> provideState() override;

            bool setResizeable() override;

        public:
            explicit AppMainWindow(StateManager *stateManager);

            void paint(juce::Graphics& g) override;

            void resized() override;

        };
    }
}


#endif //FRAMEWORK_APPMAINWINDOW_H
