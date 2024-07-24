# for generator expressions
cmake_minimum_required(VERSION 3.21)
project(
    Smoldb
    LANGUAGES C CXX
    VERSION 0.0.1)

if(NOT CMAKE_C_STANDARD)
    set(CMAKE_C_STANDARD 23)
    set(CMAKE_C_STANDARD_REQUIRED ON)
endif()

if(NOT CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 23)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
endif()

add_library(smoldb-compile-opts INTERFACE)
target_compile_features(smoldb-compile-opts
                        INTERFACE cxx_std_${CMAKE_CXX_STANDARD})
if(NOT MSVC)
    target_compile_features(smoldb-compile-opts
                            INTERFACE c_std_${CMAKE_C_STANDARD})
endif()

include(Options.cmake)
add_subdirectory(submodule)
add_subdirectory(src)
