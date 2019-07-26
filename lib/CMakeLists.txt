cmake_minimum_required(VERSION 2.8)
include(ExternalProject)

project(tutorial)

find_package(PythonLibs ${PY_VERSION} REQUIRED)
set(Python_ADDITIONAL_VERSIONS 3.6)
find_package(Boost 1.64.0 REQUIRED COMPONENTS system python-py36)

include_directories(${Boost_INCLUDE_DIR} ${PYTHON_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIR})

add_library(hello SHARED)

set (public_headers
    "\"${CMAKE_CURRENT_SOURCE_DIR}/hello.hpp\""
)

target_sources(hello
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/hello.hpp
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/hello.cpp
)



message(STATUS "Generating py++ generator file")
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/pylib_generator.py.in ${PROJECT_BINARY_DIR}/pylib_generator.py @ONLY)

message(STATUS "${public_headers}")

add_custom_target(generate_python_interfaces)
add_custom_command(
    TARGET
        generate_python_interfaces
    COMMAND
        ${PROJECT_BINARY_DIR}/pylib_generator.py
)


add_library(pylib_auto SHARED)

add_dependencies(pylib_auto generate_python_interfaces)

target_sources(pylib_auto
    PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/hello.hpp"
)
target_sources(pylib_auto
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/hello.hpp
    PRIVATE
        ${PROJECT_BINARY_DIR}/pylib_auto.cpp
)

set_source_files_properties(${PROJECT_BINARY_DIR}/pylib_auto.cpp
    PROPERTIES GENERATED true)

target_link_libraries(pylib_auto hello ${Boost_LIBRARIES} ${PYTHON_LIBRARIES})

set_target_properties(pylib_auto PROPERTIES PREFIX "")