# @brief Sandbox implementation root cmake file

include_directories(
  ${SANDBOX_INCLUDE_DIR}
)

# Sources
set(SANDBOX_IMPLEMENTATION_SRC
  main.cc
)

# Target
add_executable(sandbox_implementation
  ${SANDBOX_IMPLEMENTATION_SRC}
)

target_link_libraries(sandbox_implementation
                      sandbox_lib)

set_target_mt(sandbox_lib)
