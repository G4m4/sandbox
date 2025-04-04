# @brief SandBox main source folder cmake file

add_library(sandbox_lib)
add_library(sandbox::lib ALIAS sandbox_lib)

target_include_directories(
  sandbox_lib
  PUBLIC $<BUILD_INTERFACE:${SANDBOX_INCLUDE_DIR}/include>
         $<INSTALL_INTERFACE:include>
  PRIVATE ${SANDBOX_INCLUDE_DIR}/lib)

# Private sources
set(dummygroup "dummygroup/dummyclass.cc" "dummygroup/dummygroup.cc")

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${dummygroup})

target_sources(sandbox_lib PRIVATE ${dummygroup})

# Public headers
set(sandbox_headers
    ${SANDBOX_INCLUDE_DIR}/include/sandbox/dummygroup/dummygroup.h
    ${SANDBOX_INCLUDE_DIR}/include/sandbox/common.h
    ${SANDBOX_INCLUDE_DIR}/include/sandbox/configuration.h)

create_analysis_target(sandbox_lib)

install(
  TARGETS sandbox_lib
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})

# Headers are treated separately so the folder hierarchy gets preserved
install(
  DIRECTORY ${SANDBOX_INCLUDE_DIR}/include/
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
  COMPONENT header_files
  FILES_MATCHING
  PATTERN "*.h")
