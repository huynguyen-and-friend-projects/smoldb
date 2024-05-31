project(smoldb-internal)
include_directories(${CMAKE_SOURCE_DIR}/src/)

file(GLOB INTERNAL_SRC "*.c")
add_library(smoldb-internal STATIC ${INTERNAL_SRC})
