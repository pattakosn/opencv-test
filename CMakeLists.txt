cmake_minimum_required(VERSION 3.23)
project(opencv-testakis VERSION 0.0.1 DESCRIPTION "experiment with opencv" LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

find_package(OpenCV CONFIG REQUIRED PATHS D:/ExternalLibraries/opencv4/opencv4-4.9.0-imkl)
#find_package(OpenCV REQUIRED core highgui imgproc PATHS D:/ExternalLibraries/opencv4/opencv4-4.9.0)#-imkl)

configure_file (
    "${PROJECT_SOURCE_DIR}/src/top_level_path.h.in"
    "${PROJECT_BINARY_DIR}/top_level_path.h"
)
macro(exe_from_single_source BIN_NAME)
    add_executable(${BIN_NAME}
        ${BIN_NAME}.cpp
        ${PROJECT_BINARY_DIR}/top_level_path.h
        #PROPERTIES
        #ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        #LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        #RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    )
    target_include_directories(${BIN_NAME} PRIVATE ${PROJECT_BINARY_DIR})
    target_link_libraries(${BIN_NAME} PRIVATE ${OpenCV_LIBS})
    #target_link_libraries(${BIN_NAME} PRIVATE opencv_core opencv_highgui opencv_imgproc)
    target_compile_options(${BIN_NAME} PRIVATE
        $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:
             -Wall -Wextra -pedantic>
        $<$<CXX_COMPILER_ID:MSVC>:
             /WX /W4>)
endmacro()

add_subdirectory(src)

##if(CMAKE_CXX_COMPILER_ID EQ MSVC)
##$<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>>:-DUSE_CLANG>"-Wall -Wextra -pedantic")
##else()
##    target_compile_options(main PRIVATE "-Wall -Wextra -pedantic")
##endif()
####target_compile_features(myTarget PUBLIC $<$<CXX_COMPILER_ID:GNU>:cxx_attributes> )
####target_include_directories(myLib INTERFACE
####        "$<$<COMPILE_FEATURES:cxx_variadic_templates>:${with_variadics}>"
####        "$<$<NOT:$<COMPILE_FEATURES:cxx_variadic_templates>>:${no_variadics}>")
