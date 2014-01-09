# Retrieve all dummygroup source files

file(GLOB
     SANDBOX_DUMMYGROUP_SRC
     *.cc
)

# Expose variables to parent CMake files
set(SANDBOX_DUMMYGROUP_SRC
    ${SANDBOX_DUMMYGROUP_SRC}
    PARENT_SCOPE
)

file(GLOB
     SANDBOX_DUMMYGROUP_HDR
     *.h
)

# Expose variables to parent CMake files
set(SANDBOX_DUMMYGROUP_HDR
    ${SANDBOX_DUMMYGROUP_HDR}
    PARENT_SCOPE
)
