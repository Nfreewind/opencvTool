project(OpenCVTool)
cmake_minimum_required(VERSION 3.0)

option(BUILD_readPicture "Should we build takePicture?" ON)
option(BUILD_takePicture "Should we build takePicture?" ON)
option(BUILD_showUndistorted "Should we build showUndistorted?" ON)
option(BUILD_calibration "Should we build calibration?" ON)
option(BUILD_findChessboardCorners "Should we build findChessboardCorners?" ON)

if(BUILD_readPicture)
    add_subdirectory(readPicture)
endif()

if(BUILD_takePicture)
    add_subdirectory(takePicture)
endif()

if(BUILD_showUndistorted)
    add_subdirectory(calib3d/showUndistorted)
endif()

if(BUILD_calibration)
    add_subdirectory(calib3d/calibration)
endif()

if(BUILD_findChessboardCorners)
    add_subdirectory(calib3d/findChessboardCorners)
endif()
