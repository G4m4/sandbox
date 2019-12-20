# Retrieve all dummygroup tests source files

file(GLOB
     SANDBOX_TESTS_DUMMYGROUP_SRC
     *.cc
)

# Expose variables to parent CMake files
set(SANDBOX_TESTS_DUMMYGROUP_SRC
    ${SANDBOX_TESTS_DUMMYGROUP_SRC}
    PARENT_SCOPE
)