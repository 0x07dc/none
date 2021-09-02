#include "ADSR.h"

using namespace none::lib;

ADSR::ADSR(
        const double &attackSeconds,
        const double &decaySeconds,
        const double &sustainLevel,
        const double &releaseSeconds,
        const int &startSampleNum,
        const int &sampleRate) :
    attackSeconds(attackSeconds),
    decaySeconds(decaySeconds),
    sustainLevel(sustainLevel),
    releaseSeconds(releaseSeconds),
    Envelope(startSampleNum, sampleRate){

}

ADSR::ADSR(const int &newStartSampleNum, const int &sampleRate, const ADSRMemento &input) :
    Envelope<ADSR, ADSRMemento>(newStartSampleNum, sampleRate)
{
    attackSeconds = input.attackSeconds;
    decaySeconds = input.decaySeconds;
    sustainLevel = input.sustainLevel;
    releaseSeconds = input.releaseSeconds;
}


float ADSR::getAmplitude(int sampleNum) {
    // Get time in seconds it currently is
    LargeNum currentSampleNum = newBuffersSinceStart * sampleRate + (sampleRate - startSampleNum) + sampleNum;
    double currentTimeSeconds = (double)currentSampleNum / (double)sampleRate;
    // Determine which phase the envelope is in (attack, decay, sustain, release)
    if(isInRelease){
        // Is in release
        // Get time in release
        unsigned int releaseSampleDistance = releaseBufferNum * sampleRate + (sampleRate - releaseSampleNum) + sampleNum;
        double releaseTimeSeconds = (double)releaseSampleDistance / (double) sampleRate;
        // If releaseTimeSeconds is greater than releaseSeconds, return 0
        if(releaseTimeSeconds > releaseSeconds){
            isFinished = true;
            return 0.0f;
        }
        // Calculate line mx+b
        // The line goes from sustain level to 0 in releaseSeconds time
        // slope = -sustainLevel/releaseSeconds;
        double slopeSeconds = -sustainLevel/releaseSeconds;
        // y = slopeSeconds * releaseTimeSeconds
        return static_cast<float>(slopeSeconds * releaseTimeSeconds);
    } else {
        if(currentTimeSeconds < attackSeconds){
            // Is in attack phase
            // Goes 0 to 1 in attackSeconds time
            // slope = 1 / attackSeconds
            return static_cast<float>(1.0/attackSeconds * currentTimeSeconds);
        } else if (currentTimeSeconds < decaySeconds){
            // Is in decay
            // Goes from 1 to sustainLevel in decaySeconds
            // slope = (sustainLevel - 1)/decaySeconds
            return static_cast<float>((sustainLevel - 1) / decaySeconds);
        } else {
            // Is sustain
            return static_cast<float>(sustainLevel);
        }
    }
}

bool ADSR::getIsFinished() {
    // Check if finished
    if(isFinished) return true;
    if(isInRelease){
        // Get time in release
        unsigned int releaseSampleDistance = releaseBufferNum * sampleRate + (sampleRate - releaseSampleNum);
        double releaseTimeSeconds = (double)releaseSampleDistance / (double) sampleRate;
        // If releaseTimeSeconds is greater than releaseSeconds, return 0
        if(releaseTimeSeconds > releaseSeconds){
            isFinished = true;
            return true;
        }
    }
    return false;
}


ADSRMemento::ADSRMemento(
        double attackSeconds,
        double decaySeconds,
        double sustainLevel,
        double releaseSeconds) :
        attackSeconds(attackSeconds),
        decaySeconds(decaySeconds),
        sustainLevel(sustainLevel),
        releaseSeconds(releaseSeconds){}
