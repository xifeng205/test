/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-06-05 11:20
 * Last modified : 2020-06-05 11:20
 * Filename      : canny.cpp
 * Description   : 
*********************************************************************/

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;

int main(int argc, char **argv)
{
    cv::Mat image = cv::imread("../../../data/lena.jpg", 0);

    cv::Mat contours;
    cv::Canny(image, contours, 125, 350);
    cv::imshow("contous image", contours);

    cv::Mat contours_inv;
    cv::threshold(contours, contours_inv, 128, 255,
            cv::THRESH_BINARY_INV);
    cv::imshow("contous_inv image", contours_inv);

    cv::waitKey();
    return 0;
}
