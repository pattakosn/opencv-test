#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "top_level_path.h"

using namespace cv;

int main()
{
    const Mat image_ref = imread(top_level_path_str + "/tiger.jpg");
    if(image_ref.empty())
        return EXIT_FAILURE;

    imshow("original Image", image_ref);
    waitKey(0);

    Mat img_gray;
    cvtColor(image_ref, img_gray, COLOR_BGR2GRAY);
    Mat img_blur;
    GaussianBlur(img_gray, img_blur, Size(3,3), 0);
     
    // Sobel edge detection
    Mat sobelx, sobely, sobelxy;
    Sobel(img_blur, sobelx, CV_64F, 1, 0, 5);
    Sobel(img_blur, sobely, CV_64F, 0, 1, 5);
    Sobel(img_blur, sobelxy, CV_64F, 1, 1, 5);
    // Display Sobel edge detection images
    imshow("Sobel X", sobelx);
    waitKey(0);
    imshow("Sobel Y", sobely);
    waitKey(0);
    imshow("Sobel XY using Sobel() function", sobelxy);
    waitKey(0);
 
    // Canny edge detection
    Mat edges;
    Canny(img_blur, edges, 100, 200, 3, false);
    // Display canny edge detected image
    imshow("Canny edge detection", edges);
    waitKey(0);

    destroyAllWindows();
    return EXIT_SUCCESS;
}
