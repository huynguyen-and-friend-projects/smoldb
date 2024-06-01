cmake_minimum_required(VERSION 3.12)
project(Smoldb LANGUAGES C VERSION 0.0)

add_compile_options(-pedantic -Og -g -Wall)
# sanitization
if(WIN32)
  message("Windows")
else()
  add_compile_options(-fsanitize=leak)
endif()

add_subdirectory(src)
# add_subdirectory(src/c-api)
add_subdirectory(src/internal)
add_subdirectory(src/cli)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}src/ ${CMAKE_CURRENT_SOURCE_DIR}src/c-api
  ${CMAKE_CURRENT_SOURCE_DIR}src/internal ${CMAKE_CURRENT_SOURCE_DIR}src/cli)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")
set(CMAKE_GENERATOR Ninja)

add_executable(smoldb dummy-file.c)

target_link_libraries(smoldb PUBLIC smoldb-entry smoldb-cli smoldb-internal)
