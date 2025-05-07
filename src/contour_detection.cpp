#include <vector>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "top_level_path.h"
#include <iostream>

using namespace cv;
using std::vector;

int main()
{
    const Mat image_ref = imread(top_level_path_str + "/lena.png");
    if(image_ref.empty())
        return EXIT_FAILURE;
    imshow("Original", image_ref);

    Mat img_gray;
    cvtColor(image_ref, img_gray, COLOR_BGR2GRAY);

    Mat thresh;
    std::cout << "\tlala\n";
    threshold(img_gray, thresh, 150, 255, THRESH_BINARY);
    imshow("Binary mage", thresh);
    waitKey(0);
    destroyAllWindows();

    // detect the contours on the binary image using CHAIN_APPROX_NONE
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    findContours(thresh, contours, hierarchy, RETR_TREE, CHAIN_APPROX_NONE);
    // draw contours on the original image
    Mat image_copy = image_ref.clone();
    drawContours(image_copy, contours, -1, Scalar(0, 255, 0), 2);
    imshow("None approximation", image_copy);
    waitKey(0);
    destroyAllWindows();

    return EXIT_SUCCESS;
}
