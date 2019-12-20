# @brief sandbox UI standalone root cmake file

set(SANDBOX_STANDALONEUI_DIR
  ${CMAKE_CURRENT_SOURCE_DIR}
)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

if(POLICY CMP0020)
  # "Automatically link Qt executables to qtmain target on Windows"
  cmake_policy(SET CMP0020 NEW)
endif()

find_package(Qt5Widgets)

include_directories(
  ${SANDBOX_INCLUDE_DIR}
)

# Look for all standalone-specific files
set (SANDBOX_STANDALONEUI_SRC
  ${SANDBOX_STANDALONEUI_DIR}/main.cc
  ${SANDBOX_STANDALONEUI_DIR}/sandbox.cc
)
set (SANDBOX_STANDALONEUI_HDR
  ${SANDBOX_STANDALONEUI_DIR}/sandbox.h
)
set (SANDBOX_STANDALONEUI_UI
  ${SANDBOX_STANDALONEUI_DIR}/sandbox.ui
)

source_group("sandbox" FILES ${SANDBOX_SRC} ${SANDBOX_HDR})
source_group("sandbox_implementation" FILES ${SANDBOX_IMPLEMENTATION_SRC} ${SANDBOX_IMPLEMENTATION_HDR})
source_group("standalone_ui_specifics" FILES ${SANDBOX_STANDALONEUI_SRC} ${SANDBOX_STANDALONEUI_HDR} ${SANDBOX_STANDALONEUI_UI})

add_executable(sandbox_ui
  ${SANDBOX_SRC}
  ${SANDBOX_HDR}
  ${SANDBOX_IMPLEMENTATION_SRC}
  ${SANDBOX_IMPLEMENTATION_HDR}
  ${SANDBOX_STANDALONEUI_SRC}
  ${SANDBOX_STANDALONEUI_HDR}
  ${SANDBOX_STANDALONEUI_UI}
)

target_link_libraries(sandbox_ui
  sandbox_lib
  Qt5::Core
  Qt5::Widgets
)

set_target_mt(sandbox_ui)
