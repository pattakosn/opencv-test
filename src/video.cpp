#include <iostream>
#include <opencv2/opencv.hpp>
#include "top_level_path.h"
 
using namespace cv;
using std::cout, std::endl;

int main()
{
    //VideoCapture vid_capture(top_level_path_str + "/360x240_1mb.mp4"); // "images%02d.jpg can also work
    VideoCapture vid_capture(0, CAP_DSHOW);

    if (!vid_capture.isOpened()) {
        cout << "Error opening video stream or file" << endl;
        return EXIT_FAILURE;
    }
    
    auto fps = vid_capture.get(CAP_PROP_FPS);
    cout << "Frames per second :" << fps;
 
    auto frame_count = vid_capture.get(CAP_PROP_FRAME_COUNT );
    cout << "  Frame count :" << frame_count;

    int frame_width = static_cast<int>(vid_capture.get(CAP_PROP_FRAME_WIDTH));
    int frame_height = static_cast<int>(vid_capture.get(CAP_PROP_FRAME_HEIGHT));
    Size frame_size(frame_width, frame_height);
    fps = 20;

    VideoWriter output("output.avi", VideoWriter::fourcc('M', 'J', 'P', 'G'), fps, frame_size);

    // Read the frames to the last frame
    while (vid_capture.isOpened()) {
        Mat frame;
 
        bool isSuccess = vid_capture.read(frame);
        if (isSuccess == false) {
            cout << "Video camera is disconnected" << endl;
            break;
        }
        
        imshow("Frame", frame);
        output.write(frame);
        //wait 20 ms between successive frames and break the loop if key q is pressed
        int key = waitKey(20);
        if (key == 'q') {
            cout << "q key is pressed by the user. Stopping the video" << endl;
            break;
        }
    }
    
    vid_capture.release();
    output.release();
    return EXIT_SUCCESS;
}