project(smoldb-cli)
include_directories(${CMAKE_SOURCE_DIR}/src/internal/ ${CMAKE_SOURCE_DIR}/src/)

set(CLI_SRC cli-handler.c)
add_library(smoldb-cli STATIC ${CLI_SRC})
