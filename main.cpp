#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
using namespace cv;
#include "top_level_path.h"

int main()
{
    std::string image_path = top_level_path_str + "/lena.png";
    Mat img = imread(image_path, IMREAD_COLOR);

    imshow("Display window", img);
    int k = waitKey(0); // Wait for a keystroke in the window
    return 0;
}
