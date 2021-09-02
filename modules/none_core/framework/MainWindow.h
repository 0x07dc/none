#ifndef FRAMEWORK_MAINWINDOW_H
#define FRAMEWORK_MAINWINDOW_H

namespace none {
    template<class StateType>
    class MainWindow : public juce::Component, public HasState<StateType> {
        bool resizable = false;

    protected:
        virtual bool setResizeable() = 0;
        virtual unique_ptr<StateType> provideState() = 0;

    public:
        // Inherited via Component
        virtual void resized() override = 0;
        virtual void paint(juce::Graphics& g) override = 0;


        explicit MainWindow(StateManager* stateManager) : HasState<StateType>(stateManager){};

        MainWindow(const MainWindow<StateType>& oldMainWindow){
            HasState<StateType>::stateManager = oldMainWindow.stateManager;
            HasState<StateType>::state = oldMainWindow.state;
        };

        bool getResizable(){
            return resizable;
        };


    };
}

#endif //FRAMEWORK_MAINWINDOW_H
