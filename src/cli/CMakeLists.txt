project(smoldb-cli)
include_directories(${CMAKE_SOURCE_DIR}/src/internal/ ${CMAKE_SOURCE_DIR}/src/)

file(GLOB CLI_SRC "*.c")
add_library(smoldb-cli STATIC ${CLI_SRC})
