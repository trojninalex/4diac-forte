# ############################################################################
# Copyright (c) 2025 This program and the accompanying
# materials are made available under the terms of the Eclipse Public License
# 2.0 which is available at http://www.eclipse.org/legal/epl-2.0.
#
# SPDX-License-Identifier: EPL-2.0
#
# Contributors: Alexander Trojnin - initial API and implementation and/or initial
# documentation
# ############################################################################

if (NOT FORTE_ARCHITECTURE STREQUAL "Embox")
    return()
endif ()

# ############################################################################
# Embox FBs Base
# ############################################################################

# ############################################################################
# Embox template FBs
# ############################################################################

option(FORTE_MODULE_EMBOX "Support for the Embox template board" OFF)

if (NOT FORTE_MODULE_EMBOX)
    return()
endif ()

# ############################################################################
# ESP32 Ethernet Kit FBs
# ############################################################################

option(FORTE_MODULE_ESP32ETHERNETKIT "Support for the Esp32EthernetKit board" OFF)

if (NOT FORTE_MODULE_ESP32ETHERNETKIT)
    return()
endif ()

# ############################################################################
add_library(forte-embox
            types/EmboxIOBase.h types/EmboxIOBase.cpp types/EmboxIO_fbt.h
            types/EmboxIO_fbt.cpp types/Esp32EthernetKitIO_fbt.h
            types/Esp32EthernetKitIO_fbt.cpp
)
target_link_libraries(forte-embox PUBLIC forte-core)
target_link_libraries(forte PUBLIC $<IF:$<BOOL:${BUILD_SHARED_LIBS}>,forte-embox,$<LINK_LIBRARY:WHOLE_ARCHIVE,forte-embox>>)

add_subdirectory(handler)
add_subdirectory(handle)

install(TARGETS forte-embox EXPORT forte-export FILE_SET HEADERS)
