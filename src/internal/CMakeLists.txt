project(smoldb-internal)
include_directories(${CMAKE_SOURCE_DIR}/src/)

set(INTERNAL_SRC btree.c sql.c tokens.c token-hash.c)
add_library(smoldb-internal STATIC ${INTERNAL_SRC})
