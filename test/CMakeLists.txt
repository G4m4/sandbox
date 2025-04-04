add_executable(sandbox_test)

set_target_properties(sandbox_test PROPERTIES CXX_STANDARD 11)

target_sources(sandbox_test PRIVATE "test.cpp")

target_link_libraries(sandbox_test PRIVATE doctest sandbox_lib)

install(
  TARGETS sandbox_test
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  INCLUDES
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
