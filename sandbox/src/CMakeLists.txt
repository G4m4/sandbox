# @brief SandBox main source folder cmake file

include_directories(
  SYSTEM
  ${SANDBOX_SFML_INCLUDE_DIR}
)

include_directories(
  ${SANDBOX_INCLUDE_DIR}
)

# Retrieve source files from subdirectories
add_subdirectory(context)

# Group sources
source_group("context"
  FILES
  ${SANDBOX_CONTEXT_SRC}
  ${SANDBOX_CONTEXT_HDR}
)

# Sources
set(SANDBOX_SRC
  ${SANDBOX_CONTEXT_SRC}
)
set(SANDBOX_HDR
  configuration.h
  common.h
  ${SANDBOX_CONTEXT_HDR}
)

# Target
add_library(sandbox_lib
  STATIC # Required as SFML sets the global BUILD_SHARED_LIBS
  ${SANDBOX_SRC}
  ${SANDBOX_HDR}
)

set_target_mt(sandbox_lib)
