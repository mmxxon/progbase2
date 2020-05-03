cmake_minimum_required(VERSION 3.6.1)

project(lab5)

include_directories(./../libcsvlab)
link_directories(./../libcsvlab/build)
file(GLOB CPP_SOURCES "*.cpp")


add_executable(${PROJECT_NAME} ${CPP_SOURCES})
target_link_libraries(${PROJECT_NAME} csvlab)
SET(CMAKE_CXX_FLAGS "-std=c++17")