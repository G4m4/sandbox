# Ancillary function retrieving direct sources absolute file path for direct
# library dependencies (no recursion) for the given target
function(get_source_files target_name out_files)
  set(found_files "")
  if(target_name)
    get_target_property(target_source_dir ${target_name} SOURCE_DIR)
    get_target_property(target_sources ${target_name} SOURCES)
    foreach(target_source IN ITEMS ${target_sources})
      cmake_path(SET source_path ${target_source})
      cmake_path(GET source_path EXTENSION source_extension)
      cmake_path(
        ABSOLUTE_PATH
        source_path
        BASE_DIRECTORY
        ${target_source_dir}
        NORMALIZE
        OUTPUT_VARIABLE
        absolute_path)
      list(APPEND found_files "${absolute_path}")
    endforeach()
  endif()
  set(${out_files}
      "${found_files}"
      PARENT_SCOPE)
endfunction()

function(create_analysis_target target_name)
  add_custom_target(${target_name}_analysis DEPENDS ${target_name}_clang_tidy)

  # clang-tidy
  find_program(CLANG_TIDY_COMMAND NAMES clang-tidy)
  find_package(Python COMPONENTS Interpreter)
  add_custom_target(
    ${target_name}_clang_tidy
    COMMAND
      ${Python_EXECUTABLE} "${PROJECT_SOURCE_DIR}/scripts/run-clang-tidy.py"
      "-p${PROJECT_BINARY_DIR}" "-config-file=${PROJECT_SOURCE_DIR}/.clang-tidy"
      "-header-filter=.*sandbox(?!.*_deps|.*cpm_cache).*"
      "-source-filter=.*sandbox(?!.*_deps|.*cpm_cache).*"
    VERBATIM USES_TERMINAL)

  # Include what you use
  find_program(IWYU_COMMAND NAMES iwyu)
  # We feed it the compilation database, however we filter it to direct sources
  # for direct library dependencies (no recursion) for every target
  list(APPEND ${target_name}_sources)
  get_target_property(${target_name}_libs ${target_name}
                      INTERFACE_LINK_LIBRARIES)
  foreach(library IN ITEMS ${${target_name}_libs})
    set(library_sources "")
    get_source_files(${library} library_sources)
    list(APPEND ${target_name}_sources ${library_sources})
  endforeach()
  get_source_files(${target_name} target_sources)
  list(APPEND ${target_name}_sources ${target_sources})

  # We emit clang "errors" so they can be caught easily in the output log
  # (as other passes will rather emit warnings)
  add_custom_target(
    ${target_name}_iwyu
    COMMAND ${Python_EXECUTABLE} ${PROJECT_SOURCE_DIR}/scripts/iwyu_tool.py
            -p${PROJECT_BINARY_DIR} ${${target_name}_sources} -o clang-warning
    VERBATIM USES_TERMINAL)
endfunction()
