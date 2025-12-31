/************************************************************************************
 Copyright (c) 2025 Alexander Trojnin
 This program and the accompanying materials are made available under the
 terms of the Eclipse Public License 2.0 which is available at
 http://www.eclipse.org/legal/epl-2.0.

 SPDX-License-Identifier: EPL-2.0

 Contributors:
  Alexander Trojnin - initial API and implementation and/or initial documentation
 ************************************************************************************/

#pragma once

#include <embox/embox.h>
#include <embox/timers.h>

#include "forte/timerha.h"

namespace forte::arch {
  /*! \brief External event handler for the EMBOX Timer.
   * \ingroup EMBOX-HAL
   *
   */
  class CEMBOXimerHandler : public CTimerHandler {
    public:
      explicit CEMBOXTimerHandler(CDeviceExecution &paDeviceExecution);

      ~CEMBOXTimerHandler() override;

      /*!\brief Enables this event source
       *
       */
      void enableHandler() override;
      /*!\brief Disable this event source
       */
      void disableHandler() override;

    private:
      static void vCallbackFunction(TimerHandle_t paTimer);

      TimerHandle_t mTimer;
  };
} // namespace forte::arch
