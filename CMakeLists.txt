cmake_minimum_required (VERSION 3.20)

project (mitake VERSION 0.0.1)

include_directories ("${PROJECT_SOURCE_DIR}/include/")

file (GLOB SRC_FILES "${PROJECT_SOURCE_DIR}/src/*.cpp")

add_executable (${CMAKE_PROJECT_NAME} ${SRC_FILES})

target_compile_features (${CMAKE_PROJECT_NAME} PRIVATE cxx_std_20)
