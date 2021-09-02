#ifndef FRAMEWORK_STATEOBSERVERSUBJECT_H
#define FRAMEWORK_STATEOBSERVERSUBJECT_H

#include "StateObserver.h"
#include "TypeDef.h"

namespace none {
    class StateObserverSubject {
    public:
        virtual void notifyApp(std::string subjectName) = 0;
    };
}
#endif //FRAMEWORK_STATEOBSERVERSUBJECT_H
