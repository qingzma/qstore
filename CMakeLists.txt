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

include(CheckIncludeFile)
check_include_file("unistd.h" HAVE_UNISTD_H)

include(CheckLibraryExists)
check_library_exists(crc32c crc32c_value "" HAVE_CRC32C)
check_library_exists(snappy snappy_compress "" HAVE_SNAPPY)
check_library_exists(tcmalloc malloc "" HAVE_TCMALLOC)

include(CheckCXXSymbolExists)
check_cxx_symbol_exists(fdatasync "unistd.h" HAVE_FDATASYNC)
check_cxx_symbol_exists(F_FULLFSYNC "fcntl.h" HAVE_FULLFSYNC)
check_cxx_symbol_exists(O_CLOEXEC "fcntl.h" HAVE_O_CLOEXEC)

set(QSTORE_PUBLIC_INCLUDE_DIR "include/qstore")
set(QSTORE_PORT_CONFIG_DIR "include/port")

configure_file("port/port_config.h.in" "${PROJECT_BINARY_DIR}/${QSTORE_PORT_CONFIG_DIR}/port_config.h")
include_directories("${PROJECT_BINARY_DIR}/include" ".")

if(WIN32)
    message(FATAL_ERROR "windows is not supported.")
endif(WIN32)

add_definitions(-DQSTORE_PLATFORM_POSIX)

add_library(qbase "")
target_sources(qbase
    PRIVATE
    ${PROJECT_BINARY_DIR}/${QSTORE_PORT_CONFIG_DIR}/port_config.h
    util/status.cxx
    util/env_posix.cc
)
target_include_directories(qbase PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

if(WIN32 AND POSIX_IMPL)
    target_sources(qbase PRIVATE
        util/env_posix.cc
        util/posix_logger.h
    )
endif(WIN32 AND POSIX_IMPL)

add_executable(qstore "")
target_sources(qstore PRIVATE db/qstore.cxx util/status.cxx)
target_include_directories(qstore PUBLIC "include")
target_link_libraries(qstore qbase)

enable_testing()

add_executable(qstore_tests "")
target_sources(qstore_tests PRIVATE
    "util/status_test.cxx"

    "util/posix_logger_test.cc"
)
target_link_libraries(qstore_tests qbase GTest::gtest_main)
target_include_directories(qstore_tests PUBLIC "include")

include(GoogleTest)
gtest_discover_tests(qstore_tests)
