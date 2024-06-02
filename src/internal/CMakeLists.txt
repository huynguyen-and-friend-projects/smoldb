project(smoldb-internal)

include_directories(${CMAKE_SOURCE_DIR}/src/)

set(INTERNAL_SRC btree.c sql.c tokens.c token-hash.c)

add_library(smoldb-internal STATIC ${INTERNAL_SRC})
target_link_directories(smoldb-internal INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(smoldb-internal PUBLIC compile-opts)
