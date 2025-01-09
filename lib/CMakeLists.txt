# @brief SandBox main source folder cmake file

add_library(sandbox_lib)

target_include_directories(
  sandbox_lib
  PUBLIC $<BUILD_INTERFACE:${SANDBOX_INCLUDE_DIR}/include>
  PRIVATE ${SANDBOX_INCLUDE_DIR}/lib)

target_sources(sandbox_lib PRIVATE "dummygroup/dummyclass.cc"
                                   "dummygroup/dummygroup.cc")

create_analysis_target(sandbox_lib)
