cmake_minimum_required(VERSION 3.6.1)

project (csvlab)
include_directories(.)

file(GLOB CPP_SOURCES "*.cpp")

add_library(${PROJECT_NAME} STATIC ${CPP_SOURCES})

