cmake_minimum_required(VERSION 3.10)
project(opencv-testakis VERSION 0.0.1 DESCRIPTION "experiment with opencv" LANGUAGES CXX)

find_package(OpenCV CONFIG REQUIRED)
#find_package(OpenCV REQUIRED COMPONENTS core imgproc video)

add_executable(main main.cpp)
#target_link_libraries(main PRIVATE opencv)
#target_link_libraries(main PRIVATE opencv_ml opencv_dnn opencv_core opencv_flann)
include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(main ${OpenCV_LIBS})
