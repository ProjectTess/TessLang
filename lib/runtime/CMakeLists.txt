# ========= SubProject Configuration =========
project(
        "Tess Library (Runtime)"
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
        "tess-runtime"
        SHARED
        ${SRC}
)

# ========= Target Include Directory =========
target_include_directories(
        "tess-runtime"
        PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/"
)

# ========= Library Configuration =========
set_target_properties(
        "tess-runtime"
        PROPERTIES PREFIX ""
                   IMPORT_PREFIX ""
                   OUTPUT_NAME "libruntime-tess-${PROJECT_VERSION}"
                   WINDOWS_EXPORT_ALL_SYMBOLS TRUE
                   POSITION_INDEPENDENT_CODE TRUE
)