#ifndef FRAMEWORK_PROCESSOR_H
#define FRAMEWORK_PROCESSOR_H

#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_audio_basics/juce_audio_basics.h>
#include "StateMod.h"
#include "HasState.h"

namespace none {
    template<class StateType>
    class Processor : public HasState<StateType>{
        double simulatedPPQPosition = 0;

    protected:
        int sampleRate = 10;
        int totalNumInputChannels = 0;
        int totalNumOutputChannels = 0;
        double ppqPosition = 0.0;
        double bpm = 1.0;


        juce::AudioProcessor* audioProcessor{};

        unique_ptr<StateType> provideState() override{
            return make_unique<StateType>(HasState<StateType>::stateManager);
        };

        virtual void runProcess(
                juce::AudioBuffer<float>& buffer,
                juce::MidiBuffer& midiMessages) = 0;


    public:
        Processor() = delete;
        explicit Processor(StateManager *stateManager) : HasState<StateType>(stateManager) {}
        virtual ~Processor() = default;

        void exec(
                juce::AudioBuffer<float>& buffer,
                juce::MidiBuffer& midiMessages,
                juce::AudioProcessor* parentAudioProcessor,
                int& currentSampleRate,
                bool clearBufferFirst = false) {
            if(!this->isInitialized){
                this->initState();
            }

            audioProcessor = parentAudioProcessor;
            sampleRate = currentSampleRate;
            juce::ScopedNoDenormals noDenormals;

            totalNumInputChannels  = static_cast<int>(audioProcessor->getTotalNumInputChannels());
            totalNumOutputChannels = static_cast<int>(audioProcessor->getTotalNumOutputChannels());

            // Get length of buffer
            int bufferNumSamples = buffer.getNumSamples();
            double bufferLengthSeconds = (double)bufferNumSamples / (double)sampleRate;

            // Get current position information
            juce::AudioPlayHead* audioPlayHead = parentAudioProcessor->getPlayHead();
            juce::AudioPlayHead::CurrentPositionInfo currentPositionInfo;
            bool isPlaying = false;

            if (audioPlayHead != nullptr) {
                audioPlayHead->getCurrentPosition(currentPositionInfo);
                bpm = currentPositionInfo.bpm;
                ppqPosition = currentPositionInfo.ppqPosition;
                if (!currentPositionInfo.isPlaying) {
                    isPlaying = false;
                }
                else {
                    isPlaying = true;
                }
            }
            else {
                bpm = 130;
                ppqPosition = 0;
                isPlaying = false;
            }

            double beatLengthSeconds = 60 / bpm ;
            double beatsPerBuffer = bufferLengthSeconds / beatLengthSeconds;


            // If not playing, simulate playing
            if (!isPlaying) {
                simulatedPPQPosition += beatsPerBuffer;
                simulatedPPQPosition = simulatedPPQPosition > 1000000000 ? 1 : simulatedPPQPosition;
                ppqPosition = simulatedPPQPosition;
            }
            else {
                simulatedPPQPosition = 0;
            }



            if(clearBufferFirst)
                for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
                    buffer.clear (i, 0, buffer.getNumSamples());



            runProcess(buffer, midiMessages);

        };

    };
}

#endif //FRAMEWORK_PROCESSOR_H
