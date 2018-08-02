cmake_minimum_required(VERSION 2.8)
project(lux)

set(LUX_SHARED_VERSION_MAJOR 0)
set(LUX_SHARED_VERSION_MINOR 0)
set(LUX_SHARED_VERSION_PATCH 0)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ffast-math -Wall -Wextra")
set(CMAKE_CXX_STANDARD 17)

configure_file("${PROJECT_SOURCE_DIR}/config.h.in"
               "${PROJECT_BINARY_DIR}/include/lux/config.h")

include_directories(SYSTEM "include" "${PROJECT_BINARY_DIR}/include")
file(GLOB_RECURSE SOURCES "src/*.cpp")
add_library(lux STATIC ${SOURCES})
