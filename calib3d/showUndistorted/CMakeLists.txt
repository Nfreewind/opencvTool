project(showUndistorted)
cmake_minimum_required(VERSION 3.0)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(BUILD_SHARED_LIBS ON)

if(MSVC)
else()
    set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g -std=c++11")
    set(CMAKE_CXX_FLAGS_RELEASE "-W -Wall -O3 -std=c++11")
endif()

find_package(OpenCV)
if(MSVC AND NOT OpenCV_FOUND)
    message(FATAL_ERROR "help: set OpenCV_DIR to c:/opencv-x.x.x/build")
endif()
include_directories(${OpenCV_INCLUDE_DIRS})

file(GLOB SRCS ./*.cpp)
add_executable(${PROJECT_NAME} ${SRCS})
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})
