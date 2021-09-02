#include "NoneApp.h"

using namespace none;
using namespace none::app;

NoneApp::NoneApp() {
    init();
}

unique_ptr<Processor<MainProcessorState>> NoneApp::createProcessor() {
    return make_unique<MainProcessor>(&stateManager);
}

unique_ptr<MainWindow<AppMainWindowState>> NoneApp::createMainWindow() {
    return make_unique<AppMainWindow>(&stateManager);

}


