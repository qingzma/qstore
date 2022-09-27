cmake_minimum_required(VERSION 3.14)

project(QStore)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(qstore src/qstore.cxx src/status.cxx)

add_executable(qstore_tests "")
target_sources(qstore_tests PRIVATE "tests/status_test.cxx" "src/status.cxx")
target_link_libraries(qstore_tests GTest::gtest_main)

target_include_directories(qstore PUBLIC "include")
target_include_directories(qstore_tests PUBLIC "include")

include(GoogleTest)
gtest_discover_tests(qstore_tests)