# @brief SandBox main source folder cmake file

include_directories(
  ${SANDBOX_INCLUDE_DIR}
)

# Retrieve source files from subdirectories
add_subdirectory(dummygroup)

# Group sources
source_group("dummygroup"
  FILES
  ${SANDBOX_DUMMYGROUP_SRC}
  ${SANDBOX_DUMMYGROUP_HDR}
)

# Sources
set(SANDBOX_SRC
  ${SANDBOX_DUMMYGROUP_SRC}
)
set(SANDBOX_HDR
  configuration.h
  common.h
  ${SANDBOX_DUMMYGROUP_HDR}
)

# Target
add_library(sandbox_lib
  ${SANDBOX_SRC}
  ${SANDBOX_HDR}
)

# Those are configuration files we want to include in e.g. msvc generated files
set(SANDBOX_GLOBAL
  ${SANDBOX_INCLUDE_DIR}/.clang-format
  ${SANDBOX_INCLUDE_DIR}/.clang-tidy
  ${SANDBOX_INCLUDE_DIR}/.clangd
)

target_sources(sandbox_lib
    PRIVATE
    ${SANDBOX_GLOBAL}
)

source_group(global
    FILES
    ${SANDBOX_GLOBAL}
)

if (COMPILER_IS_MSVC)
  set_target_properties(sandbox_lib PROPERTIES
      VS_GLOBAL_RunCodeAnalysis false

      # Use visual studio core guidelines
      VS_GLOBAL_EnableMicrosoftCodeAnalysis false

      # Use clang-tidy
      VS_GLOBAL_EnableClangTidyCodeAnalysis true
      VS_GLOBAL_ClangTidyChecks "--config-file=${SANDBOX_LIB_INCLUDE_DIR}/.clang-tidy" 
  )
  target_compile_options(sandbox_lib PRIVATE $<$<CONFIG:Debug>:-fsanitize-address>)
elseif (COMPILER_IS_GCC OR COMPILER_IS_CLANG)
  target_compile_options(sandbox_lib PRIVATE $<$<CONFIG:Debug>:-fsanitize=address,leak>)
  target_link_options(sandbox_lib PRIVATE $<$<CONFIG:Debug>:-fsanitize=address,leak>)
endif()

set_target_mt(sandbox_lib)
