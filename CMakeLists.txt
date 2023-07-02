cmake_minimum_required(VERSION 3.16)

project(Search VERSION 1.0 DESCRIPTION "Search in AI" LANGUAGES CXX)
set (CMAKE_CXX_STANDARD 17)
enable_testing() 

Include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.3.2 # or a later release
)

FetchContent_MakeAvailable(Catch2)

# library files
# add_executable(inek src/main.cpp)

add_executable(tests test/main.cpp)

include_directories(AFTER SYSTEM src/)

target_sources(tests PRIVATE test/tree/tree.test.cpp)
target_sources(tests PRIVATE src/tree/tree.cpp)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

target_compile_options(tests PRIVATE -Isrc)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)

list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
include(CTest)
include(Catch)
catch_discover_tests(tests)
