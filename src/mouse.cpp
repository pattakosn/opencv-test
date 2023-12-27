#include <string>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "top_level_path.h"

using namespace cv;
using std::string;
Mat image_cur;
string window_name = "Lena";
const int max_scale_up = 100;
int scale_factor = 1;

// function which will be called on mouse input
void drawRectangle(int action, int x, int y, int /*flags*/, void * userdata)
{
    Mat* image = (Mat*) userdata;
    static Point top_left_corner, bottom_right_corner;

    // Mark the top left corner when left mouse button is pressed
    if (action == EVENT_LBUTTONDOWN)
        top_left_corner = Point(x, y);
    // When left mouse button is released, mark bottom right corner
    else if (action == EVENT_LBUTTONUP)
    {
        bottom_right_corner = Point(x, y);
        // Draw rectangle
        rectangle(*image, top_left_corner, bottom_right_corner, Scalar(0, 255, 0), 2, 8);
        // Display image
        imshow(window_name, *image);
    }
}

void scaleImage(int, void*)
{
    // Get the Scale factor from the trackbar
    double scaleFactorDouble = 1 + scale_factor / (double)max_scale_up;
     
    // Set the factor to 1 if becomes 0
    if (scaleFactorDouble == 0)
        scaleFactorDouble = 1;
     
    Mat scaledImage;
    resize(image_cur, scaledImage, Size(), scaleFactorDouble, scaleFactorDouble, INTER_LINEAR);
    imshow(window_name, scaledImage);
}

//FIXME the scaleImage and the scroll callback functions are not related, work on different images. result is weird image instead of combined images
int main()
{
    string trackbar_value = "Scale";
    const Mat image_ref = imread(top_level_path_str + "/lena.png");
    image_cur = image_ref.clone();

    namedWindow(window_name, WINDOW_AUTOSIZE);
    // highgui function called when mouse events occur
    setMouseCallback(window_name, drawRectangle, &image_cur);

    // Create Trackbars and associate a callback function
    createTrackbar(trackbar_value, window_name, &scale_factor, max_scale_up, scaleImage);

    int k = 0;
    while (k != 'q') {
        imshow(window_name, image_cur);
        scaleImage(25,0);

        k = waitKey(0);
        // If c is pressed, clear the window, using the original image
        if (k == 'c')
            image_ref.copyTo(image_cur);
    }
    destroyAllWindows();
    return EXIT_SUCCESS;
}
