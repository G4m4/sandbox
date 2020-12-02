# @brief SandBox main source folder cmake file

include_directories(
  SYSTEM
  ${GLEW_INCLUDE_DIRS}
  ${GLM_INCLUDE_DIRS}
  ${Vulkan_INCLUDE_DIRS}
)

include_directories(
  ${SANDBOX_INCLUDE_DIR}
)

# Retrieve source files from subdirectories
add_subdirectory(context)

# Group sources
source_group("context"
  FILES
  ${SANDBOX_CONTEXT_SRC}
  ${SANDBOX_CONTEXT_HDR}
)

# Sources
set(SANDBOX_SRC
  ${SANDBOX_CONTEXT_SRC}
)
set(SANDBOX_HDR
  configuration.h
  common.h
  ${SANDBOX_CONTEXT_HDR}
)

# Target
add_library(sandbox_lib
  SHARED
  ${SANDBOX_SRC}
  ${SANDBOX_HDR}
)

# Export symbols
add_compiler_flags(sandbox_lib "-DDLL_EXPORT")

if (${SYSTEM_IS_WINDOWS})
target_link_libraries(sandbox_lib
                      glfw
                      ${GLFW_LIBRARIES}
                      ${Vulkan_LIBRARIES}
)
elseif (${SYSTEM_IS_LINUX})
target_link_libraries(sandbox_lib
                      glfw
                      ${GLFW_LIBRARIES}
                      ${Vulkan_LIBRARIES}
                      ${X11_LIBRARIES}
                      ${X11_Xxf86vm_LIB}
                      ${CMAKE_THREAD_LIBS_INIT}
                      dl
)
endif()
