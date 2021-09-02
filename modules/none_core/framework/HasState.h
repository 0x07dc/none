#ifndef FRAMEWORK_HASSTATE_H
#define FRAMEWORK_HASSTATE_H

namespace none {
    template<class StateType>
    class HasState{

    protected:
        StateManager* stateManager;
        StateType* state;
        bool isInitialized = false;

        virtual unique_ptr<StateType> provideState() = 0;

        explicit HasState(StateManager* stateManager) : stateManager(stateManager){};

        void initState(){
            IdType stateId = stateManager->addState(provideState());
            //State* newState = stateManager->getState(stateId);
            //state = dynamic_cast<StateType*>(newState);
            state = static_cast<StateType*>(stateManager->getState(stateId));
            isInitialized = true;
        };
    };
}


#endif //FRAMEWORK_HASSTATE_H
