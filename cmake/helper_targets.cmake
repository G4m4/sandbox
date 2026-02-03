# Target for setting compiler switches on a per-target basis, rather than
# globally through e.g. Cmake presets

# Recommended warnings
add_library(sandbox_private_compile_options INTERFACE)
add_library(sandbox::private_compile_options ALIAS
            sandbox_private_compile_options)

add_library(sandbox_public_compile_options INTERFACE)
add_library(sandbox::public_compile_options ALIAS
            sandbox_public_compile_options)

if((CMAKE_CXX_COMPILER_ID STREQUAL "MSVC") OR (CMAKE_CXX_SIMULATE_ID STREQUAL
                                               "MSVC"))

  target_compile_options(
    sandbox_private_compile_options
    INTERFACE # Emit __cplusplus macro
              "/Zc:__cplusplus"
              # "enumerator 'identifier' in switch of enum 'enumeration' is not
              # explicitly handled by a case label"
              "/w44061"
              # Standard conformance mode
              "/permissive-")

elseif((CMAKE_CXX_COMPILER_ID STREQUAL "Clang") OR (CMAKE_CXX_COMPILER_ID
                                                    STREQUAL "AppleClang"))
  target_compile_options(
    sandbox_private_compile_options
    INTERFACE
      # https://gcc.gnu.org/onlinedocs/gcc/Warning-Options.html#index-Wswitch-enum
      -Wswitch-enum)

elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  target_compile_options(
    sandbox_private_compile_options
    INTERFACE
      # https://gcc.gnu.org/onlinedocs/gcc/Warning-Options.html#index-Wswitch-enum
      -Wswitch-enum)

endif()

target_compile_features(sandbox_private_compile_options INTERFACE cxx_std_17)
target_compile_features(sandbox_public_compile_options INTERFACE cxx_std_14)
