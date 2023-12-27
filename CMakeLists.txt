cmake_minimum_required(VERSION 3.10)
project(opencv-testakis VERSION 0.0.1 DESCRIPTION "experiment with opencv" LANGUAGES CXX)

find_package(OpenCV CONFIG REQUIRED)

configure_file (
    "${PROJECT_SOURCE_DIR}/top_level_path.h.in"
    "${PROJECT_BINARY_DIR}/top_level_path.h"
)
add_executable(main main.cpp ${PROJECT_BINARY_DIR}/top_level_path.h)
target_link_libraries(main PRIVATE opencv_core opencv_highgui opencv_imgproc opencv_imgcodecs)
target_include_directories(main PRIVATE ${PROJECT_BINARY_DIR})
#include_directories(${OpenCV_INCLUDE_DIRS})
#target_link_libraries(main ${OpenCV_LIBS})
