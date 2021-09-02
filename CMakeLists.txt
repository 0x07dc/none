cmake_minimum_required(VERSION 3.20)
project(framework)

set(CMAKE_CXX_STANDARD 14)

include_directories(juce_modules)
include_directories(modules)


add_executable(framework
        modules/none_core/none_core.h
        modules/none_core/none_core.cpp
        modules/none_core/framework/App.h
        modules/none_core/framework/State.h
        modules/none_core/framework/ComponentWithState.h
        modules/none_core/framework/StateObserverSubject.h
        modules/none_core/framework/StateManager.h
        modules/none_core/framework/Processor.h
        modules/none_core/framework/MainWindow.h
        modules/none_app/none_app.h
        modules/none_app/none_app.cpp
        modules/none_app/app/NoneApp.cpp
        modules/none_app/app/NoneApp.h
        modules/none_app/app/AppMainWindow.cpp
        modules/none_app/app/AppMainWindow.h
        modules/none_app/app/Components/FrequencySlider.cpp
        modules/none_app/app/Components/FrequencySlider.h
        modules/none_core/framework/ComponentWithState/SliderWithState.h
        modules/none_core/framework/StateObserver.h
        modules/none_app/app/Processors/Generator.cpp
        modules/none_app/app/Processors/Generator.h
        modules/none_app/app/Processors/MainProcessor.cpp
        modules/none_app/app/Processors/MainProcessor.h
        modules/none_core/framework/StateMod.h
        modules/none_app/app/Processors/StateMods/FrequencyMod.cpp
        modules/none_app/app/Processors/StateMods/FrequencyMod.h
        modules/none_core/framework/TypeDef.h
        modules/none_core/framework/HasState.h
        modules/none_app/app/Processors/GeneratorState.h
        modules/none_core/framework/Envelope.h
        modules/none_core/lib/Envelope/ADSR.cpp
        modules/none_core/lib/Envelope/ADSR.h
        modules/none_core/framework/EnvelopeConstructorInput.h modules/none_core/framework/Parameter.h modules/none_core/framework/Parameter.cpp modules/none_core/framework/ParameterDependencies/ParameterFloat.h modules/none_core/framework/ParameterDependencies/ParameterInt.h modules/none_core/framework/ParameterDependencies/ParameterBool.h modules/none_core/framework/HasParameterAttachment.h)

