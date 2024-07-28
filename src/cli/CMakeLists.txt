set(CLI_SRC cli-handler.c)

add_library(smoldb-cli ${CLI_SRC})
target_include_directories(smoldb-cli INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_directories(smoldb-cli INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(smoldb-cli PUBLIC smoldb-general PRIVATE smoldb-compile-opts)
