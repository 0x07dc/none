#ifndef FRAMEWORK_ENVELOPE_H
#define FRAMEWORK_ENVELOPE_H

#include <limits>
#include <juce_audio_basics/juce_audio_basics.h>
#include "TypeDef.h"
#include "EnvelopeConstructorInput.h"

namespace none {
    template<class ThisType, class ConstructorMementoType>
    class Envelope {
        std::vector<LargeNum> longBufferIdx{0};
        // Max of LargeNum (aka unsigned long long int) is less than that of double
        // Should be const, although that requires a custom copy/move constructor
        int maxLongBufferIdx = (int)std::numeric_limits<LargeNum>::max();

    protected:
        LargeNum newBuffersSinceStart = 0;
        int sampleRate;
        int startSampleNum;
        int releaseSampleNum, releaseBufferNum = 0;
        bool isFinished = false;
        bool isInRelease = false;

    public:
        virtual float getAmplitude(int sampleNum) = 0;
        virtual bool getIsFinished(){
            return isFinished;
        };

        Envelope() = delete;
        Envelope(int startSampleNum, int sampleRate) :
            startSampleNum(startSampleNum), sampleRate(sampleRate){};
        Envelope(int startSampleNum, int sampleRate, const ConstructorMementoType& /*input*/) : startSampleNum(startSampleNum) {}


        void nextBuffer(){
            // Modulo max numeric size, will glitch, but should never happen (will prevent possible overflow)
            newBuffersSinceStart = (newBuffersSinceStart + 1) % std::numeric_limits<LargeNum>::max();
        };

        void setReleaseSampleNum(int newReleaseSampleNum) {
            releaseSampleNum = newReleaseSampleNum;
            isInRelease = true;
        };

        static void readMidiMessages(
                const int& sampleRate,
                juce::MidiBuffer &midiMessages,
                std::map<float, ThisType>& output,
                ConstructorMementoType& constructorMemento){

            // Go through midiMessages
            // midiMessages is sorted by timestamp
            for(auto msg : midiMessages){
                juce::MidiMessage midi = msg.getMessage();
                // find noteOns, and create new ADSRs
                if(midi.isNoteOn()){
                    // Replace any duplicate notes
                    auto it = output.find((float)midi.getNoteNumber());
                    if(it != output.end()){
                        it->second = ThisType((int)midi.getTimeStamp(), sampleRate, constructorMemento);
                    } else {
                        output.emplace(
                                (float)midi.getNoteNumber(),
                                ThisType((int)midi.getTimeStamp(), sampleRate, constructorMemento)
                                );
                    }
                }

                // find noteOffs, and update relevant ADSRs
                if(midi.isNoteOff()){
                    auto it = output.find((float)midi.getNoteNumber());
                    if(it != output.end()){
                        it->second.setReleaseSampleNum((int)midi.getTimeStamp());

                    }
                }
            }

            // Check through output and remove any instances where the release has finished
            std::map<float, ThisType> newOutput;
            for(std::pair<const float, ThisType>& adsr : output){
                if(!adsr.second.getIsFinished())
                    newOutput.insert(adsr);
            }
            output = newOutput;
        }

        LargeNum getAndIncrementLongBufferIdx(int channel){
            LargeNum result = longBufferIdx[channel];
            longBufferIdx[channel] = (longBufferIdx[channel] + 1) % maxLongBufferIdx;
            return result;
        }

        void resizeLongBufferIdx(int newSize){
            // TODO handle downsizing
            if(longBufferIdx.size() < newSize)
                longBufferIdx.resize(newSize, longBufferIdx[0]);
        }

    };
}

#endif //FRAMEWORK_ENVELOPE_H
