add_subdirectory(general)
add_subdirectory(cli)
add_subdirectory(c-api)

set(ENTRY_SRC entry.c)

add_executable(smoldb ${ENTRY_SRC})
target_link_libraries(smoldb PRIVATE smoldb-cli smoldb-compile-opts)
target_include_directories(smoldb INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
