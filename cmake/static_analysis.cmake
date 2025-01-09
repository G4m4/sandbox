function(create_analysis_target target_name)
  add_custom_target(${target_name}_analysis DEPENDS ${target_name}_clang_tidy)

  # clang-tidy
  find_program(CLANG_TIDY_COMMAND NAMES clang-tidy)
  find_package(Python COMPONENTS Interpreter)
  add_custom_target(
    ${target_name}_clang_tidy
    COMMAND
      ${Python_EXECUTABLE} "${CMAKE_SOURCE_DIR}/scripts/run-clang-tidy.py"
      "-p${CMAKE_BINARY_DIR}" "-config-file=${CMAKE_SOURCE_DIR}/.clang-tidy"
      "-header-filter=.*sandbox(?!.*_deps).*"
      "-source-filter=.*sandbox(?!.*_deps).*"
    VERBATIM USES_TERMINAL)
endfunction()
