include_directories(${CMAKE_SOURCE_DIR}/src ${CMAKE_SOURCE_DIR}/src/cli
                    ${CMAKE_SOURCE_DIR}/src/internal)
# generate the header with version numbers
configure_file(general.h.in ${CMAKE_SOURCE_DIR}/src/general.h)

set(ENTRY_SRC entry.c)

add_executable(smoldb ${ENTRY_SRC})
target_link_libraries(smoldb smoldb-cli smoldb-internal compile-opts)

# add the executable to root directory for easier execution
install(TARGETS smoldb DESTINATION ${CMAKE_SOURCE_DIR})
