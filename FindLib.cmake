 add_library(Libraries::OpenCV INTERFACE IMPORTED)
 
 get_filename_component(OpenCV_DIR "${THIRD_PARTIES_PATH}/opencv/" ABSOLUTE)
 
 set_target_properties(Libraries::OpenCV PROPERTIES INTERFACE_INCLUDE_DIRECTORIES "${OpenCV_DIR}/include")
 
 target_link_directories(Libraries::OpenCV INTERFACE "${OpenCV_DIR}/lib/${CONFIG_DIR}/")
 
 target_link_libraries(Libraries::OpenCV INTERFACE
                       opencv_calib3d2413          opencv_ml2413
                       opencv_contrib2413          opencv_nonfree2413
                       opencv_core2413             opencv_objdetect2413
                       opencv_features2d2413       opencv_ocl2413
                       opencv_flann2413            opencv_photo2413
                       opencv_gpu2413              opencv_stitching2413
                       opencv_haartraining_engine  opencv_superres2413
                       opencv_highgui2413          opencv_ts2413
                       opencv_imgproc2413          opencv_video2413
                       opencv_legacy2413           opencv_videostab2413
 )
