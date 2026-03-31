# +++++++ Project Initialization +++++++
cmake_minimum_required(VERSION 3.71)
project(
        "TessLang"
        VERSION 1.0.0
        LANGUAGES C CXX
        DESCRIPTION "A programming language with modern code-style")

# +++++++ CMake Setup +++++++
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(BUILD_SHARED_LIBS ON)

if (MSVC)
    add_compile_options("/W4")
else ()
    add_compile_options("-Wall" "-Wextra" "-Wpedantic")
endif ()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_definitions("DEBUG")
else()
    if (MSVC)
        add_compile_options("/O2")
    else ()
        add_compile_options("-O3")
    endif ()
endif ()

# +++++++ External Libraries +++++++
set(FETCHCONTENT_BASE_DIR "${CMAKE_SOURCE_DIR}/.extern")

include(FetchContent)

FetchContent_Declare(
        "libfmt"
        GIT_REPOSITORY "https://github.com/fmtlib/fmt.git"
        GIT_TAG "11.2.0"
)
FetchContent_MakeAvailable("libfmt")

FetchContent_Declare(
        "libCLI11"
        GIT_REPOSITORY "https://github.com/CLITools/CLI11.git"
        GIT_TAG "v2.6.2"
)

FetchContent_MakeAvailable("libCLI11")

# +++++++ Including Subdirectories +++++++
add_subdirectory("lib/")
add_subdirectory("app/")

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    enable_testing()
    add_subdirectory("tests/")
endif ()
