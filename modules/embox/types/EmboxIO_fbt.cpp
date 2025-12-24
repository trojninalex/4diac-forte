/*************************************************************************
 *** Copyright (c) 2025 Alexander Trojnin
 ***
 *** This program and the accompanying materials are made
 *** available under the terms of the Eclipse Public License 2.0
 *** which is available at https://www.eclipse.org/legal/epl-2.0/
 ***
 *** SPDX-License-Identifier: EPL-2.0
 ***
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter V1.0.x NG!
 ***
 *** Name: EmboxIO
 *** Description: Template for Modular IO with boards running Embox OS
 *** Version:
 ***     1.0: 2025-12-25/Alexander Trojnin -  -
 *************************************************************************/

#include "EmboxIO_fbt.h"

using namespace forte::literals;

#include "forte/datatypes/forte_time.h"
#include "forte/iec61131_functions.h"
#include "forte/datatypes/forte_array_common.h"
#include "forte/datatypes/forte_array.h"
#include "forte/datatypes/forte_array_fixed.h"
#include "forte/datatypes/forte_array_variable.h"
#pragma region includes
#include <handler/IOHandleGPIODescriptor.h>
#include <handler/IOHandleADCDescriptor.h>
#include "handler/IODeviceController.h"
#pragma endregion includes

DEFINE_FIRMWARE_FB(FORTE_EmboxIO, "EmboxIO"_STRID)

namespace {
  const auto cDataInputNames = std::array{"QI"_STRID, "UpdateInterval"_STRID};
  const auto cDataOutputNames = std::array{"QO"_STRID, "STATUS"_STRID};
  const auto cEventInputNames = std::array{"INIT"_STRID};
  const auto cEventInputTypeIds = std::array{"EInit"_STRID};
  const auto cEventOutputNames = std::array{"INITO"_STRID};
  const auto cEventOutputTypeIds = std::array{"EInit"_STRID};
  const SFBInterfaceSpec cFBInterfaceSpec = {
      .mEINames = cEventInputNames,
      .mEITypeNames = cEventInputTypeIds,
      .mEONames = cEventOutputNames,
      .mEOTypeNames = cEventOutputTypeIds,
      .mDINames = cDataInputNames,
      .mDONames = cDataOutputNames,
      .mDIONames = {},
      .mSocketNames = {},
      .mPlugNames = {},
  };
} // namespace

FORTE_EmboxIO::FORTE_EmboxIO(const forte::StringId paInstanceNameId, forte::CFBContainer &paContainer) :
#pragma region base class spec
    FORTE_EmboxIOBase(paContainer, cFBInterfaceSpec, paInstanceNameId),
#pragma endregion base class spec
    var_QI(0_BOOL),
    var_UpdateInterval(40000000_TIME),
    var_QO(0_BOOL),
    var_STATUS(""_STRING),
    conn_INITO(*this, 0),
    conn_QI(nullptr),
    conn_UpdateInterval(nullptr),
    conn_QO(*this, 0, var_QO),
    conn_STATUS(*this, 1, var_STATUS) {};

void FORTE_EmboxIO::setInitialValues() {
  var_QI = 0_BOOL;
  var_UpdateInterval = 40000000_TIME;
  var_QO = 0_BOOL;
  var_STATUS = ""_STRING;
}

#pragma region remove executeEvent()
// using FORTE_EmboxIOBase::executeEvent
#pragma endregion remove executeEvent()

void FORTE_EmboxIO::readInputData(const TEventID paEIID) {
  switch (paEIID) {
    case scmEventINITID: {
      readData(0, var_QI, conn_QI);
      readData(1, var_UpdateInterval, conn_UpdateInterval);
      break;
    }
    default: break;
  }
}

void FORTE_EmboxIO::writeOutputData(const TEventID paEIID) {
  switch (paEIID) {
    case scmEventINITOID: {
      writeData(cFBInterfaceSpec.getNumDIs() + 0, var_QO, conn_QO);
      writeData(cFBInterfaceSpec.getNumDIs() + 1, var_STATUS, conn_STATUS);
      break;
    }
    default: break;
  }
}

CIEC_ANY *FORTE_EmboxIO::getDI(const size_t paIndex) {
  switch (paIndex) {
    case 0: return &var_QI;
    case 1: return &var_UpdateInterval;
  }
  return nullptr;
}

CIEC_ANY *FORTE_EmboxIO::getDO(const size_t paIndex) {
  switch (paIndex) {
    case 0: return &var_QO;
    case 1: return &var_STATUS;
  }
  return nullptr;
}

CEventConnection *FORTE_EmboxIO::getEOConUnchecked(const TPortId paIndex) {
  switch (paIndex) {
    case 0: return &conn_INITO;
  }
  return nullptr;
}

CDataConnection **FORTE_EmboxIO::getDIConUnchecked(const TPortId paIndex) {
  switch (paIndex) {
    case 0: return &conn_QI;
    case 1: return &conn_UpdateInterval;
  }
  return nullptr;
}

CDataConnection *FORTE_EmboxIO::getDOConUnchecked(const TPortId paIndex) {
  switch (paIndex) {
    case 0: return &conn_QO;
    case 1: return &conn_STATUS;
  }
  return nullptr;
}

#pragma region define IOs
void FORTE_EmboxIO::setConfig() {
  IODeviceController::Config config;
  config.updateInterval =
      static_cast<CIEC_TIME *>(getDI(FORTE_EmboxIOBase::initialDIOffset + FORTE_EmboxIO::numberOfIOs))
          ->getInMilliSeconds();
  getDeviceController()->setConfig(&config);
}

void FORTE_EmboxIO::onStartup(CEventChainExecutionThread *const paECET) {
  // Initialize handles
  for (size_t i = 0; i < FORTE_EmboxIO::numberOfIOs; i++) {
    const auto id = std::string(*static_cast<CIEC_STRING *>(getDI(FORTE_EmboxIOBase::initialDIOffset + i)));
    // do not use verbatim, only for reference to copy & paste in FBT instance class:
    const gpio_dt_spec *spec = nullptr;
    gpio_flags_t flags = 0;
    if (!spec) {
      DEVLOG_ERROR("FORTE_EmboxIO::onStartup: id %s, device spec is null\n", id.c_str());
      continue;
    }
    IOHandleGPIODescriptor descr(id, IOMapper::Out, spec, flags);
    initHandle(descr);
  }

  FORTE_EmboxIOBase::onStartup(paECET);
}
#pragma endregion define IOs
