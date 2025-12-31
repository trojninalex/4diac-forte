/************************************************************************************
 Copyright (c) 2025 Alexander Trojnin
 This program and the accompanying materials are made available under the
 terms of the Eclipse Public License 2.0 which is available at
 http://www.eclipse.org/legal/epl-2.0.

 SPDX-License-Identifier: EPL-2.0

 Contributors:
  Alexander Trojnin - initial API and implementation and/or initial documentation
 ************************************************************************************/

#include "forte/devexec.h"
#include "emboxtiha.h"
#include "forte/util/forte_constants.h"

#ifndef K_FP_REGS
#define K_FP_REGS 0
#endif // K_FP_REGS

CEmboxTimerHandler::CEmboxTimerHandler(CDeviceExecution &paDeviceExecution) : CTimerHandler(paDeviceExecution) {
  k_timer_init(&timer, NULL, NULL);
  constexpr size_t stackSize = 1024;
  stack = k_thread_stack_alloc(stackSize, 0);
  if (stack == nullptr) {
    return;
  }
  thread = static_cast<k_thread *>(k_malloc(sizeof(struct k_thread)));
  if (thread == nullptr) {
    return;
  }
  thread_id = k_thread_create(thread, stack, stackSize, thread_fn, this, NULL, NULL, 1, K_FP_REGS, K_FOREVER);
  if (thread_id)
    k_thread_name_set(thread_id, "forte_tiha");
}

CEmboxTimerHandler::~CEmboxTimerHandler() {
  disableHandler();
  if (thread) {
    k_thread_abort(thread_id);
    k_free(thread);
  }
  if (stack) {
    k_thread_stack_free(stack);
  }
}

void CEmboxTimerHandler::enableHandler() {
  if (thread == nullptr) {
    return;
  }
  const auto period = K_NSEC(forte::util::constants::cNanosecondsPerSecond / getTicksPerSecond());
  k_timer_start(&timer, period, period);
  k_thread_start(thread_id);
}

void CEmboxTimerHandler::disableHandler() {
  k_timer_stop(&timer);
}

void CEmboxTimerHandler::thread_fn(void *arg1, void *arg2, void *arg3) {
  auto self = static_cast<CEmboxTimerHandler *>(arg1);
  while (true) {
    for (auto status = k_timer_status_sync(&self->timer); status > 0; --status) {
      self->nextTick();
    }
  }
}
