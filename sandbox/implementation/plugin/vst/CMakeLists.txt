# Retrieve all VST-specifics source files

file(GLOB
     SANDBOX_PLUGIN_VST_SRC
     *.cc
     *.cpp
)

# Expose variables to parent CMake files
set(SANDBOX_PLUGIN_VST_SRC
    ${SANDBOX_PLUGIN_VST_SRC}
    PARENT_SCOPE
)

file(GLOB
     SANDBOX_PLUGIN_VST_HDR
     *.h
)

# Expose variables to parent CMake files
set(SANDBOX_PLUGIN_VST_HDR
    ${SANDBOX_PLUGIN_VST_HDR}
    PARENT_SCOPE
)
