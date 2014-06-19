# Retrieve all implementation common source files

file(GLOB
     SANDBOX_IMPLEMENTATION_SRC
     *.cc
)

# Expose variables to parent CMake files
set(SANDBOX_IMPLEMENTATION_SRC
    ${SANDBOX_IMPLEMENTATION_SRC}
    PARENT_SCOPE
)

file(GLOB
     SANDBOX_IMPLEMENTATION_HDR
     *.h
)

# Expose variables to parent CMake files
set(SANDBOX_IMPLEMENTATION_HDR
    ${SANDBOX_IMPLEMENTATION_HDR}
    PARENT_SCOPE
)
