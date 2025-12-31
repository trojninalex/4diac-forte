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

forte_register_architecture(Embox)

if("${FORTE_ARCHITECTURE}" STREQUAL "Embox")
  set(FORTE_LOGLEVEL "NOLOG" CACHE STRING "Loglevel to use" FORCE)
  set(FORTE_EMBOX_INCLUDES "" CACHE STRING "Folders to include from the Embox OS")
  
  target_include_directories(forte-core PUBLIC "${FORTE_EMBOX_INCLUDES}")

  add_subdirectory(include)
  add_subdirectory(src)

endif()
