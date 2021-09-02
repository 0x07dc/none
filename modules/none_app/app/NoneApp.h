#ifndef FRAMEWORK_NONEAPP_H
#define FRAMEWORK_NONEAPP_H

#include <none_core/none_core.h>
#include "Processors/MainProcessor.h"
#include "AppMainWindow.h"

namespace none{
    namespace app {
        class NoneApp : public App<MainProcessorState, AppMainWindowState> {
            unique_ptr<Processor<MainProcessorState>> createProcessor() override;
            unique_ptr<MainWindow<AppMainWindowState>> createMainWindow() override;

        public:
            NoneApp();
        };
    }
}



#endif //FRAMEWORK_NONEAPP_H
