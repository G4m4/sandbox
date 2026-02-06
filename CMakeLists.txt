# @brief Required for building SandBox

cmake_minimum_required(VERSION 3.22)

project(sandbox VERSION 1.0.0)

set(CMAKE_CXX_EXTENSIONS OFF)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

option(SANDBOX_ENABLE_CLI "Build CLI executables" ON)
option(SANDBOX_ENABLE_TESTS "Build tests" ON)
option(SANDBOX_BUILD_UI "Build UI executables" ON)

set(SANDBOX_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(SANDBOX_TARGETS_EXPORT_NAME "${PROJECT_NAME}Targets")

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

include(cmake/static_analysis.cmake)
include(GNUInstallDirs)

include(cmake/dependencies.cmake)
include(cmake/helper_targets.cmake)

if(${SANDBOX_ENABLE_CLI})
  add_subdirectory(cmd)
endif()

add_subdirectory(lib)

if(${SANDBOX_ENABLE_TESTS})
  add_subdirectory(test)
endif()

if(${SANDBOX_ENABLE_UI})
  add_subdirectory(ui)
endif()

# Config files, borrowed from https://github.com/schweitzer/modern-cmake-tutorial
include(CMakePackageConfigHelpers)

set(SANDBOX_CONFIGVERSION_FILE "${CMAKE_CURRENT_BINARY_DIR}/generated/${PROJECT_NAME}ConfigVersion.cmake")
set(SANDBOX_CONFIG_FILE "${CMAKE_CURRENT_BINARY_DIR}/generated/${PROJECT_NAME}Config.cmake")
set(SANDBOX_CONFIG_INSTALL_DIR "${PROJECT_SOURCE_DIR}/lib/cmake/${PROJECT_NAME}")

write_basic_package_version_file(
    "${SANDBOX_CONFIGVERSION_FILE}" VERSION ${PROJECT_VERSION} COMPATIBILITY SameMajorVersion
)

configure_file("${PROJECT_SOURCE_DIR}/cmake/Config.cmake.in" "${SANDBOX_CONFIG_FILE}" @ONLY)

install(
    FILES "${SANDBOX_CONFIG_FILE}" "${SANDBOX_CONFIGVERSION_FILE}"
    DESTINATION "${SANDBOX_CONFIG_INSTALL_DIR}")

install(
    EXPORT "${SANDBOX_TARGETS_EXPORT_NAME}"
    NAMESPACE "sandbox"
    DESTINATION "${SANDBOX_CONFIG_INSTALL_DIR}")
