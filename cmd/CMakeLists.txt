# @brief SandBox standalone root cmake file

add_executable(sandbox_cmd)

target_sources(sandbox_cmd PRIVATE "main.cc")

target_link_libraries(sandbox_cmd PUBLIC sandbox_lib)
