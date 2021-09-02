#ifndef FRAMEWORK_APP_H
#define FRAMEWORK_APP_H

#include "StateManager.h"
#include "Processor.h"
#include "MainWindow.h"


namespace none{
    template<class ProcessorStateType, class MainWindowStateType>
    class App {
        // Processor
        unique_ptr<Processor<ProcessorStateType>> processor;

        // GUI
        unique_ptr<MainWindow<MainWindowStateType>> mainWindow;

    protected:
        virtual unique_ptr<Processor<ProcessorStateType>> createProcessor() = 0;
        virtual unique_ptr<MainWindow<MainWindowStateType>> createMainWindow() = 0;


        // State management
        StateManager stateManager = StateManager();

        void init(){
            processor = move(createProcessor());
            mainWindow = move(createMainWindow());
        }

    public:
        void runProcess(juce::AudioBuffer<float>& buffer,
                        juce::MidiBuffer& midiMessages,
                        juce::AudioProcessor* parentAudioProcessor,
                        int& currentSampleRate){
            processor->exec(buffer, midiMessages, parentAudioProcessor, currentSampleRate);
        };


        juce::Component* getGUIComponent(){
            return mainWindow.get();
        };

        bool getResizable(){
            return mainWindow->getResizable();
        };

        void addParametersToJUCE(juce::AudioProcessor* audioProcessor){
            stateManager.addParametersToJUCE(audioProcessor);
        }

        void addParametersToJUCEVTS(juce::AudioProcessorValueTreeState* processorValueTreeState){
            stateManager.addParametersToJUCEVTS(processorValueTreeState);
        }

        juce::ValueTree getValueTree(){
            return stateManager.getValueTree();
        }

        void setFromValueTree(const juce::ValueTree& valueTree){
            stateManager.setFromValueTree(valueTree);
        }

    };
}


#endif //FRAMEWORK_APP_H
