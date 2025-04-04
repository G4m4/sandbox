# @brief Required for building SandBox

cmake_minimum_required(VERSION 3.22)

project(sandbox)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

option(SANDBOX_ENABLE_CLI "Build CLI executables" ON)
option(SANDBOX_ENABLE_TESTS "Build tests" ON)

set(SANDBOX_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

include(cmake/static_analysis.cmake)
include(GNUInstallDirs)

include(cmake/dependencies.cmake)
setup_dependencies()

if(${SANDBOX_ENABLE_CLI})
  add_subdirectory(cmd)
endif()

add_subdirectory(lib)

if(${SANDBOX_ENABLE_TESTS})
  add_subdirectory(test)
endif()
