# @brief SandBox main source folder cmake file

include_directories(
  SYSTEM
  ${SANDBOX_SFML_INCLUDE_DIR}
  ${SANDBOX_IMGUI_INCLUDE_DIR}
  ${SANDBOX_IMGUISFML_INCLUDE_DIR}
)

include_directories(
  ${SANDBOX_INCLUDE_DIR}
)

# Retrieve source files from subdirectories
add_subdirectory(context)
add_subdirectory(geometry)

# Imgui-related files
set (SANDBOX_EXTERNALS_IMGUI_SRC
  ${SANDBOX_EXTERNALS_IMGUI_DIR}/imgui.cpp
  ${SANDBOX_EXTERNALS_IMGUI_DIR}/imgui_demo.cpp
  ${SANDBOX_EXTERNALS_IMGUI_DIR}/imgui_draw.cpp
  ${SANDBOX_EXTERNALS_IMGUI_DIR}/imgui_widgets.cpp
)
set (SANDBOX_EXTERNALS_IMGUI_HDR
  ${SANDBOX_EXTERNALS_IMGUI_DIR}/imconfig.h
  ${SANDBOX_EXTERNALS_IMGUI_DIR}/imgui.h
)
source_group("imgui" FILES ${SANDBOX_EXTERNALS_IMGUI_SRC} ${SANDBOX_EXTERNALS_IMGUI_HDR})

# Imgui-SFML
set (SANDBOX_EXTERNALS_IMGUISFML_SRC
  ${SANDBOX_EXTERNALS_IMGUISFML_DIR}/imgui-sfml.cpp
)
set (SANDBOX_EXTERNALS_IMGUISFML_HDR
  ${SANDBOX_EXTERNALS_IMGUISFML_DIR}/imconfig-SFML.h
  ${SANDBOX_EXTERNALS_IMGUISFML_DIR}/imgui-sfml.h
)
source_group("imgui-sfml" FILES ${SANDBOX_EXTERNALS_IMGUISFML_SRC} ${SANDBOX_EXTERNALS_IMGUISFML_HDR})

# Group sources
source_group("context"
  FILES
  ${SANDBOX_CONTEXT_SRC}
  ${SANDBOX_CONTEXT_HDR}
)
source_group("geometry"
  FILES
  ${SANDBOX_GEOMETRY_SRC}
  ${SANDBOX_GEOMETRY_HDR}
)

# Sources
set(SANDBOX_SRC
  ${SANDBOX_EXTERNALS_IMGUI_SRC}
  ${SANDBOX_EXTERNALS_IMGUISFML_SRC}
  ${SANDBOX_CONTEXT_SRC}
  ${SANDBOX_GEOMETRY_SRC}
)
set(SANDBOX_HDR
  configuration.h
  common.h
  ${SANDBOX_EXTERNALS_IMGUI_HDR}
  ${SANDBOX_EXTERNALS_IMGUISFML_HDR}
  ${SANDBOX_CONTEXT_HDR}
  ${SANDBOX_GEOMETRY_HDR}
)

# Target
add_library(sandbox_lib
  STATIC # Required as SFML sets the global BUILD_SHARED_LIBS
  ${SANDBOX_SRC}
  ${SANDBOX_HDR}
)

target_compile_definitions(sandbox_lib
  PUBLIC
    IMGUI_USER_CONFIG="imconfig-SFML.h"
)

set_target_mt(sandbox_lib)
