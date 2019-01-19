cmake_minimum_required(VERSION 2.8)
project(lux)

set(LUX_SHARED_VERSION_MAJOR 0)
set(LUX_SHARED_VERSION_MINOR 0)
set(LUX_SHARED_VERSION_PATCH 0)

set(CMAKE_CXX_STANDARD 14)

configure_file("${PROJECT_SOURCE_DIR}/config.h.in"
               "${PROJECT_BINARY_DIR}/config.h")

include_directories(${PROJECT_SOURCE_DIR} ${PROJECT_BINARY_DIR})
include_directories(SYSTEM "deps")
file(GLOB_RECURSE m4_files RELATIVE "${PROJECT_SOURCE_DIR}" "*.m4")
foreach(m4_file IN LISTS m4_files)
    string(REPLACE ".m4" "" out_file ${m4_file})
    string(CONCAT out_file ${PROJECT_BINARY_DIR}/ ${out_file})
    string(CONCAT m4_file ${PROJECT_SOURCE_DIR}/ ${m4_file})
    get_filename_component(out_dir ${out_file} DIRECTORY)
    file(MAKE_DIRECTORY ${out_dir})
    add_custom_command(OUTPUT ${out_file}
                       COMMAND m4 ${m4_file} > ${out_file}
                       MAIN_DEPENDENCY ${m4_file}
                       VERBATIM)
    list(APPEND m4_out_files ${out_file})
endforeach(m4_file)

set(SOURCES
    noise.cpp
    hash.cpp
    random.cpp
    util/tick_clock.cpp
    net/enet.cpp
    net/serial.cpp
    deps/xxhash/xxhash.cpp
    deps/SimplexNoise/SimplexNoise.cpp)

add_subdirectory("deps/zlib")
add_subdirectory("deps/enet")

add_library(lux STATIC ${SOURCES} ${m4_out_files})

find_library(Z_LIB z)
find_library(ENET_LIB enet)
target_link_libraries(lux "${Z_LIB}")
target_link_libraries(lux "${ENET_LIB}")
