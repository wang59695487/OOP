cmake_minimum_required(VERSION 3.15)
project(opencvdemo)

set(CMAKE_CXX_STANDARD 11)

#find_library(OpenCV)
find_package(OpenCV)
include_directories(${OpenCV_INCLUDE_DIRS})
set(CMAKE_CXX_STANDARD 11)


add_executable(opencvdemo main.cpp)
target_link_libraries(opencvdemo ${OpenCV_LIBS})