#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "top_level_path.h"

using namespace cv;

int main()
{
    const Mat image_ref = imread(top_level_path_str + "/lena.png");
    if(image_ref.empty())
        return EXIT_FAILURE;
        

    // identity filter kernel
    Mat kernel1 = (Mat_<double>(3,3) << 0, 0, 0, 0, 1, 0, 0, 0, 0);
    Mat identity; 
    filter2D(image_ref, identity, -1 , kernel1, Point(-1, -1), 0, 4);
    imshow("Original", image_ref);
    imshow("Identity", identity);
    waitKey();
    //imwrite("identity.jpg", identity);
    destroyAllWindows();
 
    // Blurred using kernel
    Mat kernel2 = Mat::ones(5,5, CV_64F);
    kernel2 = kernel2 / 25; // Normalization
    Mat img;
    filter2D(image_ref, img, -1 , kernel2, Point(-1, -1), 0, 4);
    imshow("Original", image_ref);
    imshow("Kernel blur", img);
    //imwrite("blur_kernel.jpg", img);
    waitKey();
    destroyAllWindows();

    // Blurred using OpenCV C++ blur() function
    Mat img_blur;
    blur(image_ref, img_blur, Size(5,5));
    imshow("Original", image_ref);
    imshow("Blurred", img_blur);
    //imwrite("blur.jpg", img_blur);
    waitKey();
    destroyAllWindows();

    // Performing Gaussian Blur
    Mat gaussian_blur;
    GaussianBlur(image_ref, gaussian_blur, Size(5,5), 0, 0);
    imshow("Original", image_ref);
    imshow("Gaussian Blurred", gaussian_blur);
    //imwrite("gaussian_blur.jpg", gaussian_blur);
    waitKey();
    destroyAllWindows();

    // Apply Median Blur
    Mat median_blurred;
    medianBlur(image_ref, median_blurred, (5,5));
    imshow("Original", image_ref);
    imshow("Median Blurred", median_blurred);
    //imwrite("median_blur.jpg", median_blurred);
    waitKey();
    destroyAllWindows();

    // Apply sharpening using kernel
    Mat sharp_img;
    Mat kernel3 = (Mat_<double>(3,3) << 0, -1,  0, 
                                       -1,  5, -1, 
                                        0, -1, 0);
    filter2D(image_ref, sharp_img, -1 , kernel3, Point(-1, -1), 0, BORDER_DEFAULT);
    imshow("Original", image_ref);
    imshow("Sharpenned", sharp_img);
    //imwrite("sharp_image.jpg", sharp_img);
    waitKey();
    destroyAllWindows();

    // Apply bilateral filtering
    Mat bilateral_filter;
    bilateralFilter(image_ref, bilateral_filter, 9, 75, 75);
    imshow("Original", image_ref);
    imshow("Bilateral filtering", bilateral_filter);
    //imwrite("bilateral_filtering.jpg", bilateral_filter);
    waitKey(0);
    destroyAllWindows();

    return EXIT_SUCCESS;
}
