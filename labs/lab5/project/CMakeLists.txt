cmake_minimum_required(VERSION 3.16.4)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
project(lab5)

include_directories(../libcsvlab)
link_directories(../libcsvlab/build)
file(GLOB CPP_SOURCES "*.cpp")

add_executable(${PROJECT_NAME}.out ${CPP_SOURCES})
target_link_libraries(${PROJECT_NAME} csvlab)
