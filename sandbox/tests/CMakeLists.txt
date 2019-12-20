# @brief Build SandBox tests executable

# preventing warnings from external source files
include_directories(
  SYSTEM
  ${GTEST_INCLUDE_DIRS}
)

include_directories(
  ${SANDBOX_INCLUDE_DIR}
)

# Include all subdirectories tests source files
add_subdirectory(dummygroup)

# Group sources
source_group("dummygroup"
  FILES
  ${SANDBOX_TESTS_DUMMYGROUP_SRC}
)

# Source files
set(SANDBOX_TESTS_SRC
    main.cc
    ${SANDBOX_TESTS_DUMMYGROUP_SRC}
)

# Target
add_executable(sandbox_tests
  ${SANDBOX_TESTS_SRC}
)

set_target_mt(sandbox_tests)

target_link_libraries(sandbox_tests
  sandbox_lib
  gtest_main
)
