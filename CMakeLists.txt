# @brief Required for building SandBox

cmake_minimum_required(VERSION 3.22)

project(sandbox)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Paths definitions
set(SANDBOX_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

include(cmake/static_analysis.cmake)
include(GNUInstallDirs)

add_subdirectory(cmd)
add_subdirectory(lib)
