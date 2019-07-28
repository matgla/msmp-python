cmake_minimum_required(VERSION 3.6)

project (MSMP_Python)

find_package(PythonLibs REQUIRED)
find_package(Boost REQUIRED COMPONENTS system python3)

include(cmake/GitModules.cmake)
include(cmake/FindHeaders.cmake)

add_subdirectory(lib)

message(STATUS "Generating py++ generator file")

set (compiler clang)
set (compiler_path ${CMAKE_C_COMPILER})

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/msmp_core_generator.py.in ${PROJECT_BINARY_DIR}/msmp_core_generator.py @ONLY)

# add_custom_target(generate_python_interfaces)
# add_custom_command(
#     TARGET
#         generate_python_interfaces
#     COMMAND
#         ../generate.sh ${PROJECT_BINARY_DIR}/msmp_core_generator.py
# )

add_library(msmp_core SHARED)
target_sources(msmp_core
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/msmp_wrapper.cpp
)

# add_dependencies(msmp_core generate_python_interfaces)

# set_source_files_properties(${PROJECT_BINARY_DIR}/msmp_core.cpp
#     PROPERTIES GENERATED true)

message(STATUS "PythonLibraries: ${PYTHON_LIBRARIES}")

target_include_directories(msmp_core
    PRIVATE
        ${PYTHON_INCLUDE_DIRS}
        ${Boost_INCLUDE_DIRS}
)

target_link_libraries(msmp_core msmp_api_tcp ${Boost_LIBRARIES} ${PYTHON_LIBRARIES})

set_target_properties(msmp_core PROPERTIES PREFIX "")
