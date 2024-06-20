# for generator expressions
cmake_minimum_required(VERSION 3.21)
project(
    Smoldb
    LANGUAGES C
    VERSION 0.0)

# MSVC somehow breaks at this option
if(NOT MSVC)
    # enforcing some standards
    set(CMAKE_C_STANDARD 23)
    set(CMAKE_C_STANDARD_REQUIRED True)
endif()

# build steps for this project:

# 1. CMake checks for version requirements, and enforce C standard.
# 2. Some default compile options are added depending on the version built.
# 3. There are 2 versions available, release and debug. Release optimizes the
#    build more while debug optimizes enough to still be easy-to-debug.
# 4. Add sanitization if not on Windows AND is on a debug version.
# 5. Build libraries from the subdirectories added in.
# 6. Add an executable called smoldb (or smoldb.exe on Windows), linking it with
#    all the libraries built in the step above, alongside all the include
#    directories required by the libraries.
# 7. The build is complete.

# compile options depending on build version
set(IS_GCC_LIKE "$<COMPILE_LANG_AND_ID:C,ARMClang,AppleClang,Clang,GNU,LCC>")
set(IS_MSVC "$<COMPILE_LANG_AND_ID:C,MSVC>")

# Check the CMakeCache.txt file generated to know the options
if(CMAKE_BUILD_TYPE STREQUAL Release)
    message("Building a release version")
elseif(CMAKE_BUILD_TYPE STREQUAL Debug)
    message("Building a debug version")
endif()
message(${CMAKE_SYSTEM_NAME})

option(SANITIZE "Whether to turn on sanitization flags on Unix" OFF)
# I tried this flag on Windows and it threw an error, so,
if((NOT (WIN32 OR MSYS)) AND (SANITIZE))
    message("Not windows")
    add_compile_options(-fsanitize=leak)
endif()
if(CMAKE_BUILD_TYPE STREQUAL Debug)
    add_compile_options(-fno-inline -fno-omit-frame-pointer)
endif()

# where all the libraries are
add_subdirectory(src)
# add_subdirectory(src/c-api)
add_subdirectory(src/internal)
add_subdirectory(src/cli)

# enforce C23 to all static libraries
add_library(compile-opts INTERFACE)
if(NOT MSVC)
    target_compile_features(compile-opts INTERFACE c_std_23)
endif()
target_compile_options(
    compile-opts
    INTERFACE "$<${IS_GCC_LIKE}:-Wall;-Wextra;-Wformat=2;-pedantic>"
              "$<${IS_MSVC}:/Wall;/Za>")

# options to be included when debugging
if(CMAKE_BUILD_TYPE STREQUAL "Debug" OR CMAKE_BUILD_TYPE STREQUAL
                                        "RelWithDebInfo")
    target_compile_definitions(
        compile-opts INTERFACE "$<${IS_GCC_LIKE}:-D_FORTIFY_SOURCE=2>"
                               "$<${IS_MSVC}:/GS>")
    # Og is necessary for some reason, due to D_FORTIFY_SOURCE
    target_compile_options(compile-opts INTERFACE "$<${IS_GCC_LIKE}:-Og>"
                                                  "$<${IS_MSVC}:/Og>")
endif()
