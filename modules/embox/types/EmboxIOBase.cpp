/************************************************************************************
 Copyright (c) 2025 Alexander Trojnin
 This program and the accompanying materials are made available under the
 terms of the Eclipse Public License 2.0 which is available at
 http://www.eclipse.org/legal/epl-2.0.

 SPDX-License-Identifier: EPL-2.0

 Contributors:
  Alexander Trojnin - initial API and implementation and/or initial documentation
 ************************************************************************************/

#include "EmboxIOBase.h"
#include "handler/IODeviceController.h"

FORTE_EmboxIOBase::FORTE_EmboxIOBase(forte::CFBContainer &paContainer,
                                       const SFBInterfaceSpec &paInterfaceSpec,
                                       const forte::StringId paInstanceNameId) :
    forte::io::IOConfigFBController(paContainer, paInterfaceSpec, paInstanceNameId) {};

FORTE_EmboxIOBase::~FORTE_EmboxIOBase() {
  DEVLOG_INFO("FORTE_EmboxIOBase dtor\n");
}

forte::io::IODeviceController *FORTE_EmboxIOBase::createDeviceController(CDeviceExecution &paDeviceExecution) {
  return new IODeviceController(paDeviceExecution);
}

void FORTE_EmboxIOBase::onStartup(CEventChainExecutionThread *const paECET) {
  /*
    // Initialize handles
    for (size_t i = 0; i < FORTE_EmboxIOBase::numberOfIOs; i++) {
      const auto id = std::string(*static_cast<CIEC_STRING*>(getDI(FORTE_EmboxIOBase::initialDIOffset + i)));
      // do not use verbatim, only for reference to copy & paste in FBT instance class:
      const gpio_dt_spec* spec = nullptr;
      gpio_flags_t flags = 0;
      if (!spec) {
        DEVLOG_ERROR("FORTE_EmboxIO::onStartup: id %s, device spec is null\n", id.c_str());
        continue;
      }
      IOHandleGPIODescriptor descr(id, IOMapper::Out, spec, flags);
      initHandle(descr);
    }
  */

  started(paECET);
}
