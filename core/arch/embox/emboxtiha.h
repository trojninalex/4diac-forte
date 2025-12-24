/************************************************************************************
 Copyright (c) 2025 Alexander Trojnin
 This program and the accompanying materials are made available under the
 terms of the Eclipse Public License 2.0 which is available at
 http://www.eclipse.org/legal/epl-2.0.

 SPDX-License-Identifier: EPL-2.0

 Contributors:
  Alexander Trojnin - initial API and implementation and/or initial documentation
 ************************************************************************************/

#ifndef SRC_ARCH_EMBOX_EMBOXTIHA_H_
#define SRC_ARCH_EMBOX_EMBOXTIHA_H_

#include "forte/timerha.h"

#include <embox/kernel.h>

/*! \brief External event handler for the Embox Timer.
 * \ingroup EMBOX-HAL
 *
 */
class CEmboxTimerHandler : public CTimerHandler {
  public:
    explicit CEmboxTimerHandler(CDeviceExecution &paDeviceExecution);

    ~CEmboxTimerHandler() override;

    /*!\brief Enables this event source
     *
     */
    void enableHandler() override;
    /*!\brief Disable this event source
     */
    void disableHandler() override;

  private:
    struct k_timer timer;
    k_thread_stack_t *stack{0};
    struct k_thread *thread{0};
    static void thread_fn(void *arg1, void *arg2, void *arg3);
    k_tid_t thread_id;
};

#endif /* SRC_ARCH_EMBOX_EMBOXTIHA_H_ */
