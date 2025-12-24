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
 ***     1.0: 2025-12-25/Alexander Trojnin 
 *************************************************************************/

#pragma once

#include "forte/funcbloc.h"
#include "forte/datatypes/forte_bool.h"
#include "forte/datatypes/forte_string.h"
#include "forte/datatypes/forte_time.h"
#include "forte/iec61131_functions.h"
#include "forte/datatypes/forte_array_common.h"
#include "forte/datatypes/forte_array.h"
#include "forte/datatypes/forte_array_fixed.h"
#include "forte/datatypes/forte_array_variable.h"
#pragma region includes
#include <types/EmboxIOBase.h>
#pragma endregion includes

#pragma region base class spec
class FORTE_EmboxIO final : public FORTE_EmboxIOBase {
#pragma endregion base class spec
    DECLARE_FIRMWARE_FB(FORTE_EmboxIO)

  private:
    static const TEventID scmEventINITID = 0;
    static const TEventID scmEventINITOID = 0;

#pragma region remove executeEvent()
    // using FORTE_EmboxIOBase::executeEvent
#pragma endregion remove executeEvent()

    void readInputData(TEventID paEIID) override;
    void writeOutputData(TEventID paEIID) override;
    void setInitialValues() override;

#pragma region define IOs
    static constexpr size_t numberOfIOs = 0;

    void setConfig() override;

  protected:
    void onStartup(CEventChainExecutionThread *const paECET) override;
#pragma endregion define IOs

  public:
    FORTE_EmboxIO(forte::StringId paInstanceNameId, forte::CFBContainer &paContainer);

    CIEC_BOOL var_QI;
    CIEC_TIME var_UpdateInterval;

    CIEC_BOOL var_QO;
    CIEC_STRING var_STATUS;

    CEventConnection conn_INITO;

    CDataConnection *conn_QI;
    CDataConnection *conn_UpdateInterval;

    COutDataConnection<CIEC_BOOL> conn_QO;
    COutDataConnection<CIEC_STRING> conn_STATUS;

    CIEC_ANY *getDI(size_t) override;
    CIEC_ANY *getDO(size_t) override;
    CEventConnection *getEOConUnchecked(TPortId) override;
    CDataConnection **getDIConUnchecked(TPortId) override;
    CDataConnection *getDOConUnchecked(TPortId) override;

    void evt_INIT(const CIEC_BOOL &paQI,
                  const CIEC_TIME &paUpdateInterval,
                  CAnyBitOutputParameter<CIEC_BOOL> paQO,
                  COutputParameter<CIEC_STRING> paSTATUS) {
      COutputGuard guard_paQO(paQO);
      COutputGuard guard_paSTATUS(paSTATUS);
      var_QI = paQI;
      var_UpdateInterval = paUpdateInterval;
      executeEvent(scmEventINITID, nullptr);
      *paQO = var_QO;
      *paSTATUS = var_STATUS;
    }

    void operator()(const CIEC_BOOL &paQI,
                    const CIEC_TIME &paUpdateInterval,
                    CAnyBitOutputParameter<CIEC_BOOL> paQO,
                    COutputParameter<CIEC_STRING> paSTATUS) {
      evt_INIT(paQI, paUpdateInterval, paQO, paSTATUS);
    }
};
