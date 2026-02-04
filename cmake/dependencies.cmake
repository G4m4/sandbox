include(cmake/cpm.cmake)

# Done as a function so that updates to variables like CMAKE_CXX_FLAGS don't
# propagate out to other targets
function(setup_dependencies)

  # doctest
  if(${SANDBOX_ENABLE_TESTS})
    cpmaddpackage(GITHUB_REPOSITORY doctest/doctest GIT_TAG v2.4.11)
  endif()

  if(${SANDBOX_ENABLE_UI})
    if(NOT ${SANDBOX_BUILD_ANDROID})
      # GLFW is required on desktop
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
    endif()

    # imgui
    cpmaddpackage(GITHUB_REPOSITORY ocornut/imgui GIT_TAG v1.92.5)

    if(imgui_ADDED)
      add_library(imgui)
      target_sources(imgui PUBLIC ${imgui_SOURCE_DIR}/imgui.h)

      target_include_directories(
        imgui PUBLIC $<BUILD_INTERFACE:${imgui_SOURCE_DIR}>
                     $<BUILD_INTERFACE:${imgui_SOURCE_DIR}>/backends)

      # if(UNIX) find_package(Threads REQUIRED) target_link_libraries(miniaudio
      # PUBLIC ${CMAKE_DL_LIBS} ${CMAKE_THREAD_LIBS_INIT}) endif()

      target_sources(
        imgui
        PRIVATE ${imgui_SOURCE_DIR}/imgui.cpp
                ${imgui_SOURCE_DIR}/imgui_demo.cpp
                ${imgui_SOURCE_DIR}/imgui_draw.cpp
                ${imgui_SOURCE_DIR}/imgui_tables.cpp
                ${imgui_SOURCE_DIR}/imgui_widgets.cpp)

      # Different sources on mobile vs desktop
      if(${SANDBOX_BUILD_ANDROID})
        target_sources(
          imgui
          PRIVATE
            ${imgui_SOURCE_DIR}/backends/imgui_impl_android.cpp
            ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
            ${ANDROID_NDK}/sources/android/native_app_glue/android_native_app_glue.c
        )
        target_link_libraries(imgui PUBLIC android EGL GLESv3 log)
      else()
        # Vulkan everywhere else than on Android
        target_sources(
          imgui PRIVATE ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
                        ${imgui_SOURCE_DIR}/backends/imgui_impl_vulkan.cpp)
        target_link_libraries(imgui PUBLIC glfw Vulkan::Vulkan)
      endif()
    endif()

    # Vulkan
    find_package(Vulkan REQUIRED)
  endif()
endfunction()

setup_dependencies()

# CPM licenses target here
cpmaddpackage(NAME CPMLicenses.cmake GITHUB_REPOSITORY
              cpm-cmake/CPMLicenses.cmake VERSION 0.0.7)

cpm_licenses_create_disclaimer_target(
  write-licenses "${PROJECT_SOURCE_DIR}/third_party.txt" "${CPM_PACKAGES}")
