#include <string>
#include <opencv2/core.hpp>
//#include <opencv2/highgui.hpp>
//#include <opencv2/imgproc.hpp>
#include "top_level_path.h"
#include <iostream>

using namespace cv;
using std::string;

int main()
{
    const Mat image_ref = imread(top_level_path_str + "/threshold.jpg", IMREAD_GRAYSCALE);
    if (image_ref.empty())
        return EXIT_FAILURE;
    //namedWindow(window_name, WINDOW_AUTOSIZE);
    //imshow(window_name, image_ref);
    //waitKey();

 
    Mat image_annotated = image_ref.clone();
    Point pointA(200,80);
    Point pointB(450,80);
    line(image_annotated, pointA, pointB, Scalar(255, 255, 0), 3, 8, 0);
    
    Point circle_center(image_annotated.cols/3, 2*image_annotated.rows/3);
    std::cout << "\t" << circle_center << "\n";
    std::cout << "\t" << image_annotated.cols << " rows: "  << image_annotated.rows << "\n";
    std::cout << "\t" << image_annotated.cols/2 << " rows: "  << image_annotated.rows/2 << "\n";
    int radius = 100;
    circle(image_annotated, circle_center, radius, Scalar(0, 0, 255), /*-1*/3, 8, 0);

    Point start_point(300,115);
    Point end_point(475,225);
    rectangle(image_annotated, start_point, end_point, Scalar(0,0,255), 3, 8, 0);

    Point ellipse_center(415,390);
    Point axis1(100, 50);
    Point axis2(125, 50);
    //Horizontal
    ellipse(image_annotated, ellipse_center, axis1, 0, 0, 360, Scalar(255, 0, 0), 3, 8, 0);
    // Vertical
    ellipse(image_annotated, ellipse_center, axis2, 90, 0, 360, Scalar(0, 0, 255), 3, 8, 0);

    putText(image_annotated, "mono malakies", Point(50,350), /*FONT_HERSHEY_COMPLEX*/ FONT_ITALIC, 1.5, Scalar(250,225,100));

    imshow("Annotated Image", image_annotated);
    waitKey();

    destroyAllWindows();
    return EXIT_SUCCESS;
}
