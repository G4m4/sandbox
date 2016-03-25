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

set_target_mt(sandbox_lib)

add_compiler_flags(sandbox_lib "-Weffc++")
