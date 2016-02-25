# Retrieve all physics source files

file(GLOB
     SANDBOX_PHYSICS_SRC
     *.cc
)

# Expose variables to parent CMake files
set(SANDBOX_PHYSICS_SRC
    ${SANDBOX_PHYSICS_SRC}
    PARENT_SCOPE
)

file(GLOB
     SANDBOX_PHYSICS_HDR
     *.h
)

# Expose variables to parent CMake files
set(SANDBOX_PHYSICS_HDR
    ${SANDBOX_PHYSICS_HDR}
    PARENT_SCOPE
)
