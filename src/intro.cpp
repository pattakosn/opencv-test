#include <iostream>
#include <map>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/features2d.hpp> // feature blob detection
#include "top_level_path.h"

using namespace cv;
using std::string, std::vector, std::map, std::cout, std::cerr, std::endl;

int main()
{
    map<string, string> input_image_names {
        {"Lattice", top_level_path_str + "/lattice.jpg"},
        {"Lena", top_level_path_str +"/lena.png"}
    };

    // Read input images
    vector<Mat> images;
    for (const auto& [name, path] : input_image_names) {
        images.push_back(imread(path, IMREAD_COLOR)); //IMREAD_GRAYSCALE  IMREAD_UNCHANGED
        auto cur = images.back();
        if(cur.empty())
            cerr << "\tERROR reading: \"" << name << "\" from: \""  << path << "\"\n";
        else{
            imshow(name + " Window", cur);
            imshow("the one", cur);
        }
        cout << "image name: " << name << " size: " << cur.size() << "\n";
        cout << "Width : " << cur.size().width << endl;
        cout << "Height: " << cur.size().height << endl;
        cout << "Channels: :"<< cur.channels() << endl;
        // resize(image, Mat resized_up, Size(up_width, up_height), INTER_LINEAR);
        // resize(image, scaled_f_up, Size(), scale_up_x_factor, scale_up_y_factor, INTER_LINEAR);
    }


    // resize input images
    vector<Mat> images_resized;
    for (const auto& i: images) {
        static int count = 0;
        Mat resize_double;
        // INTER_AREA: better for shrinking, when zooming it uses INTER_NEAREST
        // INTER_CUBIC / INTER_LINEAR for resizing
        // INTER_NEAREST
        resize(i, resize_double, Size(), 0.5, 0.5, INTER_CUBIC);
        std::ostringstream wname;
        wname << "Window #" << count++ << " halfed";
        imshow( wname.str(), resize_double);
        images_resized.push_back(resize_double);
    }
    (void) waitKey(0);
    destroyAllWindows();


    // Check that images_resized are still in the vector
    imshow( "douleuei?", images_resized[1]);
    (void) waitKey(0);
    destroyAllWindows();


    // Crop image
    Mat cropped = images[1](Range(80,280), Range(150,330));
    cout << "Width : " << cropped.size().width << " . Height: " << cropped.size().height << " Channels: " << cropped.channels() << "\n";
    imshow("cropped Lena", cropped);
    (void) waitKey(0);


    // Rotate image
    const double angle = 45.;
    Point2f center((images[1].cols - 1.f) / 2.f, (images[1].rows - 1.f) / 2.f);
    Mat rotation_matix = getRotationMatrix2D(center, angle, 1.0);
    Mat rotated_image;
    // rotate the image using warpAffine
    warpAffine(images[1], rotated_image, rotation_matix, images[1].size());
    imshow("Rotated Lena", rotated_image);
    imshow("Lena", images[1]);
    waitKey(0);
    //imwrite("rotated_im.jpg", rotated_image);


    // BLOB detection example
    // Change image Colorspace
    Mat grey_lattice;
    cv::cvtColor(images[0], grey_lattice, COLOR_BGR2GRAY);
    imshow("Lattice Grey", grey_lattice);
    waitKey(0);

    // Setup SimpleBlobDetector with parameters.
    static_assert( (CV_MAJOR_VERSION > 2) && "blob detector parameter are declared differently, didnt bother with it");
    SimpleBlobDetector::Params blob_detection_params;
    blob_detection_params.minThreshold = 0.f;
    blob_detection_params.maxThreshold = 100000.f;//std::numeric_limits<float>::max();
    //blob_detection_params.filterByArea = true;
    //blob_detection_params.minArea = 1500;
    blob_detection_params.filterByCircularity = true;
    blob_detection_params.minCircularity = 0.1f;
    blob_detection_params.filterByConvexity = true;
    blob_detection_params.minConvexity = 0.87f;
    blob_detection_params.filterByInertia = true;
    blob_detection_params.minInertiaRatio = 0.1f;
    Ptr<SimpleBlobDetector> detector = SimpleBlobDetector::create(blob_detection_params);

    // Detect blobs.
    std::vector<KeyPoint> keypoints;
    detector->detect( grey_lattice, keypoints);
    
    // Draw detected blobs as red circles.
    // DrawMatchesFlags::DRAW_RICH_KEYPOINTS flag ensures the size of the circle corresponds to the size of blob
    Mat grey_lattice_with_keypoints;
    drawKeypoints( grey_lattice, keypoints, grey_lattice_with_keypoints, Scalar(0,0,255), DrawMatchesFlags::DRAW_RICH_KEYPOINTS );
    
    // Show blobs
    imshow("keypoints", grey_lattice_with_keypoints );
    waitKey(0);

    return EXIT_SUCCESS;
}
