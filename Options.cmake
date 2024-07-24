# build type
set(CMAKE_BUILD_TYPE
    Debug
    CACHE STRING "Choose a build type" FORCE)
set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release"
                                             "MinSizeRel" "RelWithDebInfo")

option(USE_CCACHE "Use ccache" OFF)
option(USE_LLD "Use lld instead of ld for linking" OFF)
option(USE_LIBCXX "Use libcxx instead of stdlibcxx" OFF)
option(ENABLE_PCH "Enable precompiled header" ON)
option(ENABLE_TESTING "Enable Google test" ON)
option(ENABLE_WARNING "Enable compiler warnings" ON)
option(WARNING_AS_ERROR "Change compiler warnings to errors" ON)
option(ENABLE_ASAN "Compile with AddressSanitizer" OFF)
option(ENABLE_UBSAN "Compile with UndefinedBehaviorSanitizer" OFF)
option(ENABLE_MSAN "Compile with MemorySanitizer" OFF)
option(ENABLE_COVERAGE "Compile with coverage flag" OFF)
option(ENABLE_FUZZ "Enable fuzz testing. Currently only working with clang" OFF)
# configure accordingly to options
if(ENABLE_CCACHE)
    find_program(CCACHE ccache)
    if(NOT CCACHE)
        message("Cannot find ccache")
    else()
        message("Found ccache and is using it")
        set(CMAKE_C_COMPILER_LAUNCHER ${CCACHE})
        set(CMAKE_CXX_COMPILER_LAUNCHER ${CCACHE})
    endif()
endif()

if(${CMAKE_BUILD_TYPE} STREQUAL Debug)
    if(MSVC)
        target_compile_options(smoldb-compile-opts INTERFACE "/Od")
    else(MSVC)
        target_compile_options(smoldb-compile-opts INTERFACE "-O0")
    endif()
endif()

if(USE_LLD)
    find_program(LLD lld REQUIRED)
    if(NOT LLD)
        message(
            FATAL_ERROR
                "Error, LLD not found, please either turn off option USE_LLD or add directory of LLD to PATH"
        )
    endif()
    set(CMAKE_LINKER lld)
endif()

if(USE_LIBCXX)
    if(NOT MSVC)
        target_compile_options(smoldb-compile-opts INTERFACE "-stdlib=libc++")
        target_link_options(smoldb-compile-opts INTERFACE
                            "-stdlib=libc++;-lc++abi")
    endif()
endif()

if(ENABLE_TESTING)
    add_subdirectory(unittest)
endif()
if(ENABLE_WARNING)
    if(MSVC)
        target_compile_options(smoldb-compile-opts INTERFACE "/W4")
    else(MSVC)
        target_compile_options(
            smoldb-compile-opts
            INTERFACE
                "-Wall;-Wextra;-Wformat=2;-fdiagnostics-color=always;-Wshadow;-Wconversion"
        )
    endif()
endif()

if(WARNING_AS_ERROR)
    if(MSVC)
        target_compile_options(smoldb-compile-opts INTERFACE "/WX")
    else(MSVC)
        target_compile_options(smoldb-compile-opts INTERFACE "-Werror")
    endif()
endif()

if(ENABLE_ASAN)
    if(MSVC)
        target_compile_options(smoldb-compile-opts
                               INTERFACE "/fsanitize=address;/Oy")
    else(MSVC)
        target_compile_options(
            smoldb-compile-opts
            INTERFACE "-fsanitize=address;-fno-omit-frame-pointer")
        target_link_options(smoldb-compile-opts INTERFACE "-fsanitize=address")
    endif()
endif()

if(ENABLE_UBSAN)
    if(MSVC)
        message(
            "We don't know if there's this option on MSVC :(. Currently disabling it."
        )
    else(MSVC)
        target_compile_options(smoldb-compile-opts
                               INTERFACE "-fsanitize=undefined")
        target_link_options(smoldb-compile-opts INTERFACE
                            "-fsanitize=undefined")
    endif()
endif()

if(ENABLE_MSAN)
    if("${CMAKE_CXX_COMPILER_FRONTEND_VARIANT}" STREQUAL "MSVC")
        message(
            "We don't know if there's this option on MSVC :(. Currently disabling it."
        )
    else()
        target_compile_options(
            smoldb-compile-opts
            INTERFACE
                "-fsanitize=memory;-fno-omit-frame-pointer;-fno-optimize-sibling-calls"
        )
        target_link_options(smoldb-compile-opts INTERFACE "-fsanitize=memory")
    endif()
endif()

if(ENABLE_COVERAGE)
    if(MSVC)
        target_compile_options("/fsanitize-coverage=edge")
    else(MSVC)
        target_compile_options(smoldb-compile-opts INTERFACE "--coverage")
        target_link_options(smoldb-compile-opts INTERFACE "--coverage")
    endif()
endif()

if(ENABLE_FUZZ)
    if(NOT "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
        message(
            "Note that gcc/g++ won't work with libFuzzer. This is a LLVM-only tool."
        )
    else()
        add_subdirectory(fuzztest)
    endif()
endif()
