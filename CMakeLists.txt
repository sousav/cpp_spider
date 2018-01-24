# stop if cmake version below 3.3
cmake_minimum_required(VERSION 3.3 FATAL_ERROR)

# location of additional cmake modules
set(CMAKE_MODULE_PATH
    ${CMAKE_MODULE_PATH}
    ${CMAKE_CURRENT_SOURCE_DIR}/CMake
)

set(PROJECT_GLOBAL_SOURCE_DIR ${PROJECT_SOURCE_DIR}/)
set(PROJECT_GLOBAL_BINARY_DIR ${PROJECT_BINARY_DIR}/bin/)


# guard against in-source builds and bad build-type strings
include(safeguards)

# add all the executable CMakeList
add_subdirectory(${PROJECT_SOURCE_DIR}/Client)
add_subdirectory(${PROJECT_SOURCE_DIR}/Server)
