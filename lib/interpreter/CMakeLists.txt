# ========= SubProject Configuration =========
project(
        "Tess Library (Interpreter)"
        VERSION 1.0.0
)

# ========= Collecting Source Files =========
file(
        GLOB_RECURSE
        SRC
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cxx"
)

# ========= Creating Shared Library =========
add_library(
        "tess-interpreter"
        SHARED
        ${SRC}
)

# ========= Target Include Directory =========
target_include_directories(
        "tess-interpreter"
        PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/"
)

# ========= Library Configuration =========
set_target_properties(
        "tess-interpreter"
        PROPERTIES PREFIX ""
                   IMPORT_PREFIX ""
                   OUTPUT_NAME "libinterpreter-tess-${PROJECT_VERSION}"
                   WINDOWS_EXPORT_ALL_SYMBOLS TRUE
                   POSITION_INDEPENDENT_CODE TRUE
)