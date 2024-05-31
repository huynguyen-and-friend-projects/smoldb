project(smoldb-entry)
include_directories(${CMAKE_SOURCE_DIR}/src ${CMAKE_SOURCE_DIR}/src/cli
                    ${CMAKE_SOURCE_DIR}/src/internal)

set(ENTRY_SRC entry.c)
add_executable(smoldb ${ENTRY_SRC})
