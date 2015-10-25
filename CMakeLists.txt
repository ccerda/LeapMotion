cmake_minimum_required(VERSION 2.8)

project(HACKINGEDUPROTOTYPE)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

include_directories("${PROJECT_SOURCE_DIR}")
include_directories(/home/chult/Dropbox/HackingEdu/LeapSDK/include)
link_directories(/home/chult/Dropbox/HackingEdu/LeapSDK/lib/x64)
add_library(Controls Controls.cpp)
# add_library(Leap SHARED ../LeapSDK/lib/x64/libLeap.so)
add_executable (main main.cpp)
target_link_libraries(main Leap Controls)
