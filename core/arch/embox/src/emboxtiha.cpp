/************************************************************************************
 Copyright (c) 2025 Alexander Trojnin
 This program and the accompanying materials are made available under the
 terms of the Eclipse Public License 2.0 which is available at
 http://www.eclipse.org/legal/epl-2.0.

 SPDX-License-Identifier: EPL-2.0

 Contributors:
  Alexander Trojnin - initial API and implementation and/or initial documentation
 ************************************************************************************/

#include "emboxtiha.h"
#include "forte/devexec.h"

#include "../../common/src/utils/timespec_utils.h"
#include "forte/timerhandlerfactory.h"

using namespace forte::literals;

namespace forte::arch {
  namespace {
    [[maybe_unused]] const TimerHandlerFactory::EntryImpl<CEMBOXTimerHandler> entry("default"_STRID);
  }

  CEMBOXTimerHandler::CEMBOXTimerHandler(CDeviceExecution &paDeviceExecution) : CTimerHandler(paDeviceExecution) {
    mTimer =
        xTimerCreate("FORTETimer", pdMS_TO_TICKS(1000 / getTicksPerSecond()), pdTRUE, (void *) this, vCallbackFunction);
  }

  CEMBOXTimerHandler::~CEMBOXTimerHandler() {
    disableHandler();
    xTimerDelete(mTimer, 0);
  }

  void CEMBOXTimerHandler::enableHandler() {
    xTimerStart(mTimer, 0);
  }

  void CEMBOXTimerHandler::disableHandler() {
    xTimerStop(mTimer, 0);
  }

  void CEMBOXTimerHandler::vCallbackFunction(TimerHandle_t paTimer) {
    static_cast<CEMBOXTimerHandler *>(pvTimerGetTimerID(paTimer))->nextTick();
  }
} // namespace forte::arch
