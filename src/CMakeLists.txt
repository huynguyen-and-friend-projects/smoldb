project(smoldb-entry)
include_directories(${CMAKE_SOURCE_DIR}/src ${CMAKE_SOURCE_DIR}/src/cli
                    ${CMAKE_SOURCE_DIR}/src/internal)

file(GLOB ENTRY_SRC "*.c")
add_executable(Smoldb ${ENTRY_SRC})
target_link_libraries(Smoldb PRIVATE smoldb-internal smoldb-cli)
