
/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-06-06 10:12
 * Last modified : 2020-06-06 10:12
 * Filename      : harris.cpp
 * Description   : 
*********************************************************************/

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/features2d.hpp>

using namespace std;

int main(int argc, char **argv)
{
    cv::Mat image = cv::imread("../../../data/lena.jpg", 0);

    std::vector<cv::KeyPoint> key_points;
    cv::FastFeatureDetector fast(40);

    // fast.detect(image, key_points);
    // double threshold = 0.0001;
    // cv::threshold(corner, harrisCorners,
            threshold, 255, cv::THRESH_BINARY_INV); 

    cv::imshow("harris image", harrisCorners);

    cv::waitKey();
    return 0;
}
