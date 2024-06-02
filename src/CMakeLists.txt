project(smoldb-entry)

include_directories(${CMAKE_SOURCE_DIR}/src ${CMAKE_SOURCE_DIR}/src/cli
                    ${CMAKE_SOURCE_DIR}/src/internal)
# generate the header with version numbers
configure_file(general.h.in ${CMAKE_SOURCE_DIR}/src/general.h)

set(ENTRY_SRC entry.c)

add_library(smoldb-entry STATIC ${ENTRY_SRC})
target_link_directories(smoldb-entry INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(smoldb-entry PUBLIC compile-opts)
