include(cmake/cpm.cmake)

# Done as a function so that updates to variables like CMAKE_CXX_FLAGS don't
# propagate out to other targets
function(setup_dependencies)
  
  # doctest
  if(${SANDBOX_ENABLE_TESTS})
    cpmaddpackage(GITHUB_REPOSITORY doctest/doctest GIT_TAG v2.4.11)
  endif()

endfunction()

# CPM licenses target here
cpm_licenses_create_disclaimer_target(
  write-licenses "${CMAKE_BINARY_SOURCE_DIR}/third_party.txt" "${CPM_PACKAGES}")
