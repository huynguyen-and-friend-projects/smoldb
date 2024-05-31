cmake_minimum_required(VERSION 3.12)
project(Smoldb LANGUAGES C)

add_definitions(-pedantic)
set(DEBUG "Add debug flags" ON)
if(DEBUG)
  add_definitions(-Og -g)
else()
  add_definitions(-O2)
endif(DEBUG)

add_subdirectory(src)
# add_subdirectory(src/c-api)
add_subdirectory(src/internal)
add_subdirectory(src/cli)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}src/ ${CMAKE_CURRENT_SOURCE_DIR}src/c-api
  ${CMAKE_CURRENT_SOURCE_DIR}src/internal ${CMAKE_CURRENT_SOURCE_DIR}src/cli)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED False)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")
