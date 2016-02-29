# @brief SandBox root cmake file

add_subdirectory(implementation)
add_subdirectory(src)

if (SANDBOX_HAS_GTEST)
  add_subdirectory(tests)
endif (SANDBOX_HAS_GTEST)
