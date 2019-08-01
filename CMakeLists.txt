cmake_minimum_required(VERSION 3.8.2)

if(NOT BUILD_VERSION)
    set(BUILD_VERSION 0.1.0)
endif()

project(librg_cpp VERSION ${BUILD_VERSION})

# Build options
option(BUILD_TESTS "Build the library tests" ON)
option(BUILD_EXAMPLES "Build the library examples" ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Add dependencies
set(LIBRG_STATIC ON)
set(LIBRG_VENDOR_FOLDER thirdparty)
set(LIBRG_POSTFIX _librg)

add_subdirectory(thirdparty/librg)

add_subdirectory(src)

if(BUILD_TESTS)
    enable_testing()

    add_subdirectory(tests)
endif()

if(BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()