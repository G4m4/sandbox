# Retrieve all context source files

file(GLOB
     SANDBOX_CONTEXT_SRC
     *.cc
)

# Expose variables to parent CMake files
set(SANDBOX_CONTEXT_SRC
    ${SANDBOX_CONTEXT_SRC}
    PARENT_SCOPE
)

file(GLOB
     SANDBOX_CONTEXT_HDR
     *.h
)

# Expose variables to parent CMake files
set(SANDBOX_CONTEXT_HDR
    ${SANDBOX_CONTEXT_HDR}
    PARENT_SCOPE
)
