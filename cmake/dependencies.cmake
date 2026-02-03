include(cmake/cpm.cmake)

# Done as a function so that updates to variables like CMAKE_CXX_FLAGS don't
# propagate out to other targets
function(setup_dependencies)

  # doctest
  if(${SANDBOX_ENABLE_TESTS})
    cpmaddpackage(GITHUB_REPOSITORY doctest/doctest GIT_TAG v2.4.11)
  endif()

  # cmake-format: off
  if(${SANDBOX_ENABLE_UI})
    # GLFW
    cpmaddpackage(
      GITHUB_REPOSITORY
      glfw/glfw
      GIT_TAG
      3.4
      OPTIONS
      "GLFW_BUILD_EXAMPLES OFF"
      "GLFW_BUILD_TESTS OFF"
      "GLFW_BUILD_DOCS OFF"
      "GLFW_INSTALL OFF")

    # imgui
    cpmaddpackage(
      GITHUB_REPOSITORY
      ocornut/imgui
      GIT_TAG
      v1.91.9b)

    # cmake-format: on

    if(imgui_ADDED)
      add_library(imgui)
      target_sources(
        imgui
        PUBLIC FILE_SET
               header
               TYPE
               HEADERS
               BASE_DIRS
               ${imgui_SOURCE_DIR}
               FILES
               ${imgui_SOURCE_DIR}/imgui.h)
      target_sources(
        imgui
        PRIVATE ${imgui_SOURCE_DIR}/imgui.cpp
                ${imgui_SOURCE_DIR}/imgui_demo.cpp
                ${imgui_SOURCE_DIR}/imgui_draw.cpp
                ${imgui_SOURCE_DIR}/imgui_tables.cpp
                ${imgui_SOURCE_DIR}/imgui_widgets.cpp
                ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
                ${imgui_SOURCE_DIR}/backends/imgui_impl_vulkan.cpp)
      target_include_directories(
        imgui PUBLIC $<BUILD_INTERFACE:${imgui_SOURCE_DIR}>
                     $<BUILD_INTERFACE:${imgui_SOURCE_DIR}>/backends)
      target_link_libraries(imgui PUBLIC glfw Vulkan::Vulkan)
      # if(UNIX) find_package(Threads REQUIRED) target_link_libraries(miniaudio
      # PUBLIC ${CMAKE_DL_LIBS} ${CMAKE_THREAD_LIBS_INIT}) endif()
    endif()

    # Vulkan
    find_package(Vulkan REQUIRED)
  endif()
endfunction()

setup_dependencies()

# CPM licenses target here
CPMAddPackage(
  NAME CPMLicenses.cmake
  GITHUB_REPOSITORY cpm-cmake/CPMLicenses.cmake
  VERSION 0.0.7
)

cpm_licenses_create_disclaimer_target(
  write-licenses "${PROJECT_SOURCE_DIR}/third_party.txt" "${CPM_PACKAGES}")
