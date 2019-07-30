cmake_minimum_required(VERSION 3.6)

project (MSMP_Python)

find_package(PythonLibs REQUIRED)
find_package(Boost REQUIRED COMPONENTS system python3)

include(cmake/GitModules.cmake)
include(cmake/FindHeaders.cmake)

add_subdirectory(lib)

add_library(msmp_core SHARED)
target_sources(msmp_core
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/msmp_wrapper.cpp
)

message(STATUS "PythonLibraries: ${PYTHON_LIBRARIES}")

target_include_directories(msmp_core
    PRIVATE
        ${PYTHON_INCLUDE_DIRS}
        ${Boost_INCLUDE_DIRS}
)

target_link_libraries(msmp_core msmp_api_tcp ${Boost_LIBRARIES} ${PYTHON_LIBRARIES})

target_compile_options(msmp_core PUBLIC
    $<$<COMPILE_LANGUAGE:CXX>:-std=c++2a -Wall -Werror -fPIC>
    $<$<CONFIG:DEBUG>:-Og -g>
    $<$<CONFIG:RELEASE>:-Os>
)

set_target_properties(msmp_core PROPERTIES PREFIX "")
