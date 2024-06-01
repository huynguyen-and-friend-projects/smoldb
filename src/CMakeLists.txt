project(smoldb-entry)
include_directories(${CMAKE_SOURCE_DIR}/src ${CMAKE_SOURCE_DIR}/src/cli
                    ${CMAKE_SOURCE_DIR}/src/internal)
configure_file(general.h.in ${CMAKE_SOURCE_DIR}/src/general.h)
set(ENTRY_SRC entry.c)
add_executable(smoldb ${ENTRY_SRC})
target_link_libraries(smoldb PUBLIC smoldb-cli smoldb-internal)
