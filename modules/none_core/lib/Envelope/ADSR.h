#ifndef FRAMEWORK_ADSR_H
#define FRAMEWORK_ADSR_H

#include "../../framework/Envelope.h"

namespace none {
    namespace lib {
        struct ADSRMemento {
            double attackSeconds, decaySeconds, sustainLevel, releaseSeconds;
            int startSampleNum, sampleRate;

            ADSRMemento(double attackSeconds,
                        double decaySeconds,
                        double sustainLevel,
                        double releaseSeconds);
        };
        class ADSR : public Envelope<ADSR, ADSRMemento> {
            double attackSeconds, decaySeconds, sustainLevel, releaseSeconds;

        public:
            bool getIsFinished() override;

            float getAmplitude(int sampleNum) override;

            ADSR(const int &newStartSampleNum, const int &sampleRate, const ADSRMemento &input);

            ADSR(
                    const double &attackSeconds,
                    const double &decaySeconds,
                    const double &sustainLevel,
                    const double &releaseSeconds,
                    const int &startSampleNum,
                    const int &sampleRate);



        };
    }
}


#endif //FRAMEWORK_ADSR_H
