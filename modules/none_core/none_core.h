/*****************************************************************//**
 * \file   none_core.h
 * \brief  None Framework Core
 *
 * \author vossj
 * \date   August 2021
 *********************************************************************/
/*
  ==============================================================================
  BEGIN_JUCE_MODULE_DECLARATION

  ID:            none_core
  vendor:        Paradigm E
  version:       1.0.0
  name:          NONECORE
  description:   The core of the None Framework
  dependencies:  juce_core juce_graphics, juce_audio_utils
  END_JUCE_MODULE_DECLARATION

 ==============================================================================
 */

#ifndef FRAMEWORK_NONE_CORE_H
#define FRAMEWORK_NONE_CORE_H

#include "framework/App.h"
#include "framework/ComponentWithState.h"
#include "framework/StateManager.h"
#include "framework/StateObserver.h"
#include "framework/StateObserverSubject.h"
#include "framework/State.h"
#include "framework/ComponentWithState/SliderWithState.h"
#include "framework/StateMod.h"
#include "framework/Processor.h"
#include "framework/TypeDef.h"
#include "framework/HasState.h"
#include "framework/Envelope.h"
#include "lib/Envelope/ADSR.h"
#include "framework/EnvelopeConstructorInput.h"
#include "framework/Parameter.h"
#include "framework/ParameterDependencies/ParameterFloat.h"
#include "framework/ParameterDependencies/ParameterInt.h"
#include "framework/ParameterDependencies/ParameterBool.h"
#include "framework/HasParameterAttachment.h"

#endif //FRAMEWORK_NONE_CORE_H
