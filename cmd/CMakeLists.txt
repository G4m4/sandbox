# @brief SandBox standalone root cmake file

add_executable(sandbox_cmd)
add_executable(sandbox::cmd ALIAS sandbox_cmd)

target_sources(sandbox_cmd PRIVATE "main.cc")

target_link_libraries(sandbox_cmd PUBLIC sandbox::lib)

add_custom_command(
  TARGET sandbox_cmd
  POST_BUILD
  COMMAND
    ${CMAKE_COMMAND} -E echo
    "sandbox_cmd runtime dependencies: $<TARGET_RUNTIME_DLLS:sandbox_cmd>")

set(have_runtime_dlls $<BOOL:$<TARGET_RUNTIME_DLLS:sandbox_cmd>>)

set(runtime_dlls_command
    ${CMAKE_COMMAND} -E copy_if_different $<TARGET_RUNTIME_DLLS:sandbox_cmd>
    $<TARGET_FILE_DIR:sandbox_cmd>)

add_custom_command(
  TARGET sandbox_cmd
  POST_BUILD
  COMMAND "$<${have_runtime_dlls}:${runtime_dlls_command}>"
  COMMAND_EXPAND_LISTS)

install(
  TARGETS sandbox_cmd
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  INCLUDES
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
