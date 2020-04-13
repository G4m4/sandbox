# @brief SandBox standalone root cmake file

set(SANDBOX_STANDALONE_DIR
  ${CMAKE_CURRENT_SOURCE_DIR}
)

include_directories(
  ${SANDBOX_INCLUDE_DIR}
)

# Look for all standalone-specific files
set (SANDBOX_STANDALONE_SRC
  ${SANDBOX_STANDALONE_DIR}/main.cc
)
set (SANDBOX_STANDALONE_HDR
  # Nothing in here for now
)

source_group("sandbox" FILES ${SANDBOX_SRC} ${SANDBOX_HDR})
source_group("sandbox_implementation" FILES ${SANDBOX_IMPLEMENTATION_SRC} ${SANDBOX_IMPLEMENTATION_HDR})
source_group("standalone_specifics" FILES ${SANDBOX_STANDALONE_SRC} ${SANDBOX_STANDALONE_HDR})

add_executable(sandbox
  ${SANDBOX_SRC}
  ${SANDBOX_HDR}
  ${SANDBOX_IMPLEMENTATION_SRC}
  ${SANDBOX_IMPLEMENTATION_HDR}
  ${SANDBOX_STANDALONE_SRC}
  ${SANDBOX_STANDALONE_HDR}
)

target_link_libraries(sandbox
                      sandbox_lib
                      sfml-system
                      sfml-window
)

sfml_copy_library(sfml-system sandbox)
sfml_copy_library(sfml-window sandbox)

set_target_mt(sandbox)
