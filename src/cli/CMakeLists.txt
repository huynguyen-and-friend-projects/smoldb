project(smoldb-cli)

include_directories(${CMAKE_SOURCE_DIR}/src/internal/ ${CMAKE_SOURCE_DIR}/src/)

set(CLI_SRC cli-handler.c)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_library(smoldb-cli STATIC ${CLI_SRC})
target_link_directories(smoldb-cli INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(smoldb-cli PUBLIC compile-opts)
if(Threads)
    target_compile_options(smoldb-cli PRIVATE "-pthread")
endif()
