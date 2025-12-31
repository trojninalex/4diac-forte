#/************************************************************************************
# Copyright (c) 2025 Alexander Trojnin
# This program and the accompanying materials are made available under the
# terms of the Eclipse Public License 2.0 which is available at
# http://www.eclipse.org/legal/epl-2.0.
#
# SPDX-License-Identifier: EPL-2.0
#
# Contributors:
#  Alexander Trojnin - initial API and implementation and/or initial documentation
# ************************************************************************************/

SET(SOURCE_GROUP ${SOURCE_GROUP}\\Embox)

forte_register_architecture(Embox)

if("${FORTE_ARCHITECTURE}" STREQUAL "Embox")

  forte_add_include_directories(${CMAKE_CURRENT_SOURCE_DIR})

  set(FORTE_LOGLEVEL "NOLOG" CACHE STRING "Loglevel to use" FORCE)
  SET(FORTE_EMBOX_INCLUDES "" CACHE STRING "Folders to include from the Embox OS")

  forte_add_sourcefile_hcpp(forte_thread forte_sync forte_sem)

  forte_add_timerhandler(CEmboxTimerHandler emboxtiha )
  forte_add_sourcefile_hcpp(embox)

  forte_add_sourcefile_cpp(./forte_architecture_time.cpp)

  forte_add_sourcefile_cpp(../common/forte_specific_architecture.cpp)
  forte_add_sourcefile_cpp(../genforte_printer.cpp)
  forte_add_sourcefile_cpp(emboxforte_fileio.cpp)

  forte_add_include_system_directories(${FORTE_EMBOX_INCLUDES})

  if(FORTE_COM_ETH)
    forte_add_handler(CFDSelectHandler sockhand)
    forte_add_sourcefile_hcpp( ../fdselecthand ../bsdsocketinterf)
    forte_add_sourcefile_h(../gensockhand.h)
    forte_add_sourcefile_hcpp(sockhand)
  endif(FORTE_COM_ETH)

endif()
