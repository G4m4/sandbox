# @brief Required for building SandBox

cmake_minimum_required(VERSION 3.8)

project(sandbox)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS OFF)

# Paths definitions
set(SANDBOX_INCLUDE_DIR
  ${CMAKE_CURRENT_SOURCE_DIR}
)

# Default parameters

if (NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()

# Various detection, to be used as shortcuts below

# Compilers
set(COMPILER_IS_CLANG
    0)
set(COMPILER_IS_GCC
    0)
set(COMPILER_IS_MSVC
    0)
if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  set(COMPILER_IS_CLANG
      1)
  message("Compiler detected as Clang")
elseif (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
  set(COMPILER_IS_GCC
      1)
  message("Compiler detected as gcc")
elseif (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
  set(COMPILER_IS_MSVC
      1)
  message("Compiler detected as MSVC")
else()
  message(SEND_ERROR "Could not deduce compiler")
endif()

# Systems
set(SYSTEM_IS_WINDOWS
    0)
set(SYSTEM_IS_MACOSX
    0)
set(SYSTEM_IS_LINUX
    0)
if (CMAKE_SYSTEM_NAME MATCHES "Windows")
  set(SYSTEM_IS_WINDOWS
      1)
  message("System detected as Windows")
elseif (CMAKE_SYSTEM_NAME MATCHES "Darwin")
  set(SYSTEM_IS_MACOSX
      1)
  message("System detected as Mac OS X")
else()
  # ${CMAKE_SYSTEM_NAME} MATCHES "Linux" may be true on Mac!
  set(SYSTEM_IS_LINUX
      1)
  message("System detected as Linux")
endif()

# Build configuration
set(BUILD_IS_DEBUG
    0)
if (CMAKE_BUILD_TYPE MATCHES "Debug")
  set(BUILD_IS_DEBUG
      1)
  message("Build configuration set to Debug")
else()
  message("Build configuration set to Release")
endif()

# Functions

# @brief For the specified target, append compiler flags to the existing ones
#
# @param _TARGET_NAME           target name
# @param _FLAGS                 flags to set
function(add_compiler_flags _TARGET_NAME _FLAGS)
  set_property(TARGET ${_TARGET_NAME}
               APPEND_STRING PROPERTY COMPILE_FLAGS " ${_FLAGS}"
               )
endfunction(add_compiler_flags)

# @brief For the specified target, append linker flags to the existing ones
#
# @param _TARGET_NAME           target name
# @param _FLAGS                 flags to set
function(add_linker_flags _TARGET_NAME _FLAGS)
  set_property(TARGET ${_TARGET_NAME}
               APPEND PROPERTY LINK_FLAGS " ${_FLAGS}"
               )
endfunction(add_linker_flags)

# @brief For the whole project, append debug compiler flags
#
# @param _FLAGS                 flags to set
function(add_debug_flags _FLAGS)
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${_FLAGS}"
      PARENT_SCOPE)
endfunction(add_debug_flags)

# @brief For the whole project, append release compiler flags
#
# @param _FLAGS                 flags to set
function(add_release_flags _FLAGS)
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${_FLAGS}"
      PARENT_SCOPE)
  # Same for the "symbol" configuration
  set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} ${_FLAGS}"
      PARENT_SCOPE)
endfunction(add_release_flags)

# @brief For the whole project, append release linker flags
#
# @param _FLAGS                 flags to set
function(add_release_linker_flags _FLAGS)
  set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} ${_FLAGS}"
      PARENT_SCOPE)
  # Same for the "symbol" configuration
  set(CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO "${CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO} ${_FLAGS}"
      PARENT_SCOPE)
endfunction(add_release_linker_flags)

# @brief For the given list of files, disable all warnings
#
# @param _TARGETS      List of files
function(disable_warnings_files _TARGETS)
 if (COMPILER_IS_GCC OR COMPILER_IS_CLANG)
   set(FLAG
       "-w")
 else()
   set(FLAG
       "/W0")
 endif()
 SET_SOURCE_FILES_PROPERTIES(${_TARGETS}
                             PROPERTIES COMPILE_FLAGS " ${FLAG}"
                             )
endfunction(disable_warnings_files)

# @brief For the given target, disable all warnings
#
# @param _TARGET      target name
function(disable_warnings_target _TARGET)
 if (COMPILER_IS_CLANG)
   set(FLAG
       "-Wno-everything")
 elseif(COMPILER_IS_GCC OR COMPILER_IS_MSVC)
   set(FLAG
       "-w")
 endif()
 add_compiler_flags(${_TARGET} ${FLAG})
endfunction(disable_warnings_target)

# @brief (MSVC only) Set one specific target to use MT runtime library,
# or MTd in debug configuration
#
# @param _TARGET_NAME           target name
function(set_target_mt _TARGET_NAME)
  if(COMPILER_IS_MSVC)
    # Cannot use "add_CONFIG_flags" function here due to variable scoping
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd"
        PARENT_SCOPE)
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT"
        PARENT_SCOPE)
    set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} /MT"
        PARENT_SCOPE)
  endif(COMPILER_IS_MSVC)
endfunction(set_target_mt)

option(SANDBOX_HAS_TEST "Allowing to use the test framework (the test framework submodule should have been initialised and updated)." ON)
message(STATUS "Test framework: ${SANDBOX_HAS_TEST}")

# Project-wide various options
if (COMPILER_IS_MSVC)
  # Multithreaded build
  add_definitions("/MP")
endif (COMPILER_IS_MSVC)

# Project-wide warning options
if(COMPILER_IS_GCC OR COMPILER_IS_CLANG)
  add_definitions(-pedantic)
  add_definitions(-Wall)
  add_definitions(-Wextra)
  add_definitions(-Wpointer-arith)
  add_definitions(-Wcast-qual)
elseif(COMPILER_IS_MSVC)
  add_definitions(/W4)
  add_definitions(/WX)
  # This disable useless msvc warnings about checked iterators
  add_definitions(-D_SCL_SECURE_NO_WARNINGS)
endif(COMPILER_IS_GCC OR COMPILER_IS_CLANG)

# Debug-only options
if(COMPILER_IS_GCC OR COMPILER_IS_CLANG)
  add_debug_flags("-ggdb")
elseif(COMPILER_IS_MSVC)
endif(COMPILER_IS_GCC OR COMPILER_IS_CLANG)

# Release-only options
if(COMPILER_IS_GCC OR COMPILER_IS_CLANG)
  add_release_flags("-Ofast")
  add_release_flags("-march=native")
elseif(COMPILER_IS_MSVC)
  add_release_linker_flags("/LTCG")
  add_release_flags("/O2")
  add_release_flags("/GL")
  add_release_flags("/fp:fast")
endif(COMPILER_IS_GCC OR COMPILER_IS_CLANG)


# Various includes


    )
    )

add_subdirectory(sandbox)
