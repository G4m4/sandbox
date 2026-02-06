# @brief SandBox UI executable root cmake file

cmake_minimum_required(VERSION 3.22)

project(SandboxUI)

set(CMAKE_CXX_EXTENSIONS OFF)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

option(SANDBOX_BUILD_ANDROID "Build Android targets" OFF)

# Parent dependency
if(NOT TARGET sandbox::lib)
  message("Building as a standalone")
  find_package(sandbox REQUIRED)
else()
  message("Building as a  subproject of the main library")
endif()

include(cmake/dependencies.cmake)

if(${SANDBOX_BUILD_ANDROID})
  # On Android this is a shared library that gets loaded
  add_library(sandbox_ui SHARED)
  add_library(sandbox::ui ALIAS sandbox_ui)

  target_sources(sandbox_ui PRIVATE "main_android.cc")

  target_link_options(sandbox_ui PRIVATE -u ANativeActivity_onCreate)
else()
  add_executable(sandbox_ui)
  add_executable(sandbox::ui ALIAS sandbox_ui)

  target_sources(sandbox_ui PRIVATE "main_vulkan.cc")
endif()

target_link_libraries(sandbox_ui PUBLIC imgui sandbox::lib)
target_link_libraries(sandbox_ui PRIVATE sandbox::private_compile_options)
target_link_libraries(sandbox_ui INTERFACE sandbox::public_compile_options)

add_custom_command(
  TARGET sandbox_ui
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E echo
          "sandbox_ui runtime dependencies: $<TARGET_RUNTIME_DLLS:sandbox_ui>")

set(have_runtime_dlls $<BOOL:$<TARGET_RUNTIME_DLLS:sandbox_ui>>)

set(runtime_dlls_command
    ${CMAKE_COMMAND} -E copy_if_different $<TARGET_RUNTIME_DLLS:sandbox_ui>
    $<TARGET_FILE_DIR:sandbox_ui>)

add_custom_command(
  TARGET sandbox_ui
  POST_BUILD
  COMMAND "$<${have_runtime_dlls}:${runtime_dlls_command}>"
  COMMAND_EXPAND_LISTS)

install(
  TARGETS sandbox_ui
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  INCLUDES
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
