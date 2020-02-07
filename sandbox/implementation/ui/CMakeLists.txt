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
  cmake_policy(SET CMP0020 NEW)
endif()

find_package(Qt5Widgets)

get_target_property(QMAKE_EXECUTABLE Qt5::qmake IMPORTED_LOCATION)
get_filename_component(QT_BIN_DIR "${QMAKE_EXECUTABLE}" DIRECTORY)
if (SYSTEM_IS_WINDOWS)
  set(DEPLOYQT_EXE_NAME windeployqt)
elseif(SYSTEM_IS_MAC)
  set(DEPLOYQT_EXE_NAME macdeployqt)
endif()
find_program(DEPLOYQT_EXECUTABLE ${DEPLOYQT_EXE_NAME} HINTS "${QT_BIN_DIR}")

# @brief For the specified target, invoke the Qt binary deploy executable
#
# @param _TARGET_NAME           target name
function(deployqt _TARGET_NAME)
if (SYSTEM_IS_LINUX)
else()
  set(DEPLOYQT_EXE_NAME macdeployqt)
  add_custom_command(
    TARGET ${_TARGET_NAME}
    POST_BUILD
    COMMAND cd "${CMAKE_CURRENT_BINARY_DIR}"
    COMMAND "${DEPLOYQT_EXECUTABLE}" --verbose 0 --no-compiler-runtime --no-translations --no-angle --no-opengl-sw --no-webkit2 --no-system-d3d-compiler --no-quick-import "$<$<CONFIG:Debug>:--debug>$<$<CONFIG:Release>:--release>" "$<TARGET_FILE:${_TARGET_NAME}>"
  )
endif()
endfunction()

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

deployqt(sandbox_ui)
