#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/features2d.hpp>
#include "top_level_path.h"

using namespace cv;

int main()
{
    //const Mat image_ref = imread(top_level_path_str + "/blob_detection.jpg", IMREAD_GRAYSCALE);
    const Mat image_ref = imread(top_level_path_str + "/BlobTest.jpg", IMREAD_GRAYSCALE);
    if(image_ref.empty())
        return EXIT_FAILURE;

    imshow("original Image", image_ref);
    waitKey(0);

    // Setup SimpleBlobDetector parameters.
    SimpleBlobDetector::Params params;

    // Change thresholds
    params.minThreshold = 10;
    params.maxThreshold = 200;

    // Filter by Area.
    params.filterByArea = true;
    params.minArea = 1500;

    // Filter by Circularity
    params.filterByCircularity = true;
    params.minCircularity = 0.1f;

    // Filter by Convexity
    params.filterByConvexity = true;
    params.minConvexity = 0.87f;

    // Filter by Inertia
    params.filterByInertia = true;
    params.minInertiaRatio = 0.01f;
 
    // Detect blobs.
    std::vector<KeyPoint> keypoints;
    // Set up detector with params
    Ptr<SimpleBlobDetector> detector = SimpleBlobDetector::create(params);
    // Detect blobs
    detector->detect(image_ref, keypoints);
 
    // Draw detected blobs as red circles.
    // DrawMatchesFlags::DRAW_RICH_KEYPOINTS flag ensures the size of the circle corresponds to the size of blob
    Mat im_with_keypoints;
    drawKeypoints( image_ref, keypoints, im_with_keypoints, Scalar(0,0,255), DrawMatchesFlags::DRAW_RICH_KEYPOINTS );
 
    // Show blobs
    imshow("keypoints", im_with_keypoints );
    waitKey(0);

    destroyAllWindows();
    return EXIT_SUCCESS;
}
