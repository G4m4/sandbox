# @brief SandBox implementation root cmake file

add_subdirectory(common)

if (${SANDBOX_HAS_VST} STREQUAL "ON")
  add_subdirectory(plugin)
endif (${SANDBOX_HAS_VST} STREQUAL "ON")

add_subdirectory(standalone)
