#ifndef FRAMEWORK_STATEOBSERVER_H
#define FRAMEWORK_STATEOBSERVER_H

#include "TypeDef.h"

namespace none {

    class StateObserver{
    protected:
        virtual void onObservedStateChange(const std::string& subjectName) = 0;

    };
}

#endif //FRAMEWORK_STATEOBSERVER_H
