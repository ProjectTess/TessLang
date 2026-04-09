# +++++++ SubProject Initialization +++++++
project(
	"TessLang Test"
	DESCRIPTION "An executable with unit-tests for debugging Compiler and STD libraries"
)

# +++++++ External Libraries +++++++
FetchContent_Declare(
		"google-test"
		GIT_REPOSITORY "https://github.com/google/googletest.git"
		GIT_TAG "v1.16.0"
)
FetchContent_MakeAvailable("google-test")

# +++++++ Collecting Source Files +++++++
file(
	GLOB_RECURSE
	SRC
	"${CMAKE_CURRENT_SOURCE_DIR}/*.cxx"
)

# +++++++ Creating Executable +++++++
add_executable(
	"tess-test"
	${SRC}
)

target_link_libraries(
	"tess-test"
	PRIVATE "GTest::gtest_main" "tess-core" # "tess-compiler" "tess-runtime"
)