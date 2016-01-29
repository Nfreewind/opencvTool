project(readPicture)
cmake_minimum_required(VERSION 3.0)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

if(MSVC)
else()
    set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g -std=c++11")
    set(CMAKE_CXX_FLAGS_RELEASE "-W -Wall -O3 -std=c++11")
endif()

if(MSVC)
    set(OPENCV_DIR "C:/opencv-2.4.9/build")
    set(OPENCV_DEBUG_VERSION "249d")
    set(OPENCV_VERSION "249")
endif()

if(MSVC)
    include_directories("${OPENCV_DIR}/include")
    link_directories("${OPENCV_DIR}/x86/vc12/lib")
else()
    find_package(OpenCV REQUIRED)
    include_directories(${OpenCV_INCLUDE_DIRS})
endif()

file(GLOB SRCS ./*.cpp)
add_executable(${PROJECT_NAME} ${SRCS})
if(MSVC)
    target_link_libraries(${PROJECT_NAME} opencv_core${OPENCV_DEBUG_VERSION}.lib opencv_highgui${OPENCV_DEBUG_VERSION}.lib opencv_imgproc${OPENCV_DEBUG_VERSION}.lib)
else()
    target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})
endif()

