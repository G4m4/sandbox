# @brief SandBox main source folder cmake file

include_directories(
  SYSTEM
  ${BULLET_INCLUDE_DIRS}
)

include_directories(
  ${SANDBOX_INCLUDE_DIR}
)

# Retrieve source files from subdirectories
add_subdirectory(physics)

# Group sources
source_group("physics"
  FILES
  ${SANDBOX_PHYSICS_SRC}
  ${SANDBOX_PHYSICS_HDR}
)

# Sources
set(SANDBOX_SRC
  ${SANDBOX_PHYSICS_SRC}
)
set(SANDBOX_HDR
  configuration.h
  common.h
  ${SANDBOX_PHYSICS_HDR}
)

# Target
add_library(sandbox_lib
  SHARED
  ${SANDBOX_SRC}
  ${SANDBOX_HDR}
)

add_compiler_flags(sandbox_lib "-DDLL_EXPORT")
set_target_mt(sandbox_lib)

target_link_libraries(sandbox_lib
                      ${BULLET_LIBRARIES}
)
