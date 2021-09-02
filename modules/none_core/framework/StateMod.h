#ifndef FRAMEWORK_STATEMOD_H
#define FRAMEWORK_STATEMOD_H

#include "HasState.h"

namespace none {
    template<class InternalState, class ExternalState>
    class StateMod : public HasState<InternalState> {
    protected:
        ExternalState* externalState;

        virtual void runMod(int sampleNum) = 0;

        virtual unique_ptr<InternalState> provideState() override = 0;


    public:
        explicit StateMod(StateManager* stateManager, ExternalState* externalState) : 
            HasState<InternalState>(stateManager), externalState(externalState) {};


    };
}

#endif //FRAMEWORK_STATEMOD_H
