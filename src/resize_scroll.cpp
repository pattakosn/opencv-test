#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "top_level_path.h"

using namespace cv;
using std::string;

int maxScaleUp = 100;
int scaleFactor = 1;
string windowName = "Resize Image";
string trackbarValue = "Scale";

void scaleImage(int, void *)
{
    Mat image = imread(top_level_path_str + "/lena.png");

    double scaleFactorDouble = 1 + scaleFactor / 100.0;

    if (scaleFactorDouble == 0)
      scaleFactorDouble = 1;

    Mat scaledImage;
    resize(image, scaledImage, Size(), scaleFactorDouble, scaleFactorDouble, INTER_LINEAR);
    imshow(windowName, scaledImage);
}

int main()
{
    Mat image = imread(top_level_path_str + "/lena.png");

    namedWindow(windowName, WINDOW_AUTOSIZE);

    // Create Trackbars and associate a callback function
    createTrackbar(trackbarValue, windowName, &scaleFactor, maxScaleUp, scaleImage);
    scaleImage(25, 0);

    imshow(windowName, image);
    waitKey(0);
    destroyAllWindows();
    return EXIT_SUCCESS;
}