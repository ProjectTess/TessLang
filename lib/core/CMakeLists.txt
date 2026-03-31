# ========= SubProject Configuration =========
project(
        "Tess Library (Core)"
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
        "tess-core"
        SHARED
        ${SRC}
)

# ========= Target Library Setup =========
target_include_directories(
        "tess-core"
        PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/"
)

target_link_libraries(
        "tess-core"
        PUBLIC "fmt::fmt"
)

# ========= Library Configuration =========
set_target_properties(
        "tess-core"
        PROPERTIES PREFIX ""
                   IMPORT_PREFIX ""
                   OUTPUT_NAME "libcore-tess-${PROJECT_VERSION}"
                   WINDOWS_EXPORT_ALL_SYMBOLS TRUE
                   POSITION_INDEPENDENT_CODE TRUE
)