# @brief SandBox standalone root cmake file

set(SANDBOX_STANDALONE_DIR
  ${CMAKE_CURRENT_SOURCE_DIR}
)

include_directories(
  ${SANDBOX_INCLUDE_DIR}
)

# Look for all standalone-specific files
set (SANDBOX_STANDALONE_SRC
  ${SANDBOX_STANDALONE_DIR}/main.cc
)
set (SANDBOX_STANDALONE_HDR
  # Nothing in here for now
)

source_group("sandbox" FILES ${SANDBOX_SRC} ${SANDBOX_HDR})
source_group("sandbox_implementation" FILES ${SANDBOX_IMPLEMENTATION_SRC} ${SANDBOX_IMPLEMENTATION_HDR})
source_group("standalone_specifics" FILES ${SANDBOX_STANDALONE_SRC} ${SANDBOX_STANDALONE_HDR})

add_executable(sandbox
  ${SANDBOX_SRC}
  ${SANDBOX_HDR}
  ${SANDBOX_IMPLEMENTATION_SRC}
  ${SANDBOX_IMPLEMENTATION_HDR}
  ${SANDBOX_STANDALONE_SRC}
  ${SANDBOX_STANDALONE_HDR}
)

target_link_libraries(sandbox
                      sandbox_lib
)

if (COMPILER_IS_MSVC)
  set_target_properties(sandbox PROPERTIES
      VS_GLOBAL_RunCodeAnalysis false

      # Use visual studio core guidelines
      VS_GLOBAL_EnableMicrosoftCodeAnalysis false

      # Use clang-tidy
      VS_GLOBAL_EnableClangTidyCodeAnalysis true
      VS_GLOBAL_ClangTidyChecks "--config-file=${SANDBOX_LIB_INCLUDE_DIR}/.clang-tidy" 
  )
  target_compile_options(sandbox PRIVATE $<$<CONFIG:Debug>:-fsanitize-address>)
elseif (COMPILER_IS_GCC OR COMPILER_IS_CLANG)
  target_compile_options(sandbox PRIVATE $<$<CONFIG:Debug>:-fsanitize=address,leak>)
  target_link_options(sandbox PRIVATE $<$<CONFIG:Debug>:-fsanitize=address,leak>)
endif()

set_target_mt(sandbox)
