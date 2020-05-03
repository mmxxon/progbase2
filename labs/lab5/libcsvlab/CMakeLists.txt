cmake_minimum_required(VERSION 3.16.4)

project (csvlab)
include_directories(.)

file(GLOB CPP_SOURCES "*.cpp")
add_library(${PROJECT_NAME} STATIC ${CPP_SOURCES})

