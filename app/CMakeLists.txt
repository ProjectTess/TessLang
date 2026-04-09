# ========= SubProject Configuration =========
project(
        "Tess Executable"
        VERSION 1.0.0
)

# ========= Collecting Source Files =========
file(
        GLOB_RECURSE
        SRC
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cxx"
)

# ========= Creating Executable =========
add_executable(
        "tess"
        ${SRC}
)

# ========= Linking =========
target_link_libraries(
        "tess"
        PRIVATE "tess-core" # "tess-compiler" "tess-runtime"
)