
file(GLOB
     SANDBOX_GEOMETRY_SRC
     *.cc
)

# Expose variables to parent CMake files
set(SANDBOX_GEOMETRY_SRC
    ${SANDBOX_GEOMETRY_SRC}
    PARENT_SCOPE
)

file(GLOB
     SANDBOX_GEOMETRY_HDR
     *.h
)

# Expose variables to parent CMake files
set(SANDBOX_GEOMETRY_HDR
    ${SANDBOX_GEOMETRY_HDR}
    PARENT_SCOPE
)
