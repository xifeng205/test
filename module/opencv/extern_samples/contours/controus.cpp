/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-06-05 17:43
 * Lareturnr;st modified : 2020-06-05 17:43
 * Filename      : controus.cpp
 * Description   : 
*********************************************************************/

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgproc/types_c.h>


using namespace std;

int main(int argc, char **argv)
{
    cv::Mat image = cv::imread("../../../data/ellipses.jpg", 0);

    cv::threshold(image, image, 20, 255, cv::THRESH_BINARY);
    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(image, contours, CV_RETR_EXTERNAL,
            CV_CHAIN_APPROX_NONE);

    cv::Mat result(image.size(), CV_8U, cv::Scalar(255));
    cv::drawContours(result, contours, -1, cv::Scalar(0), 2);
    // cv::imshow("contours image", result);
    // cv::imshow("origin image", image);
    // int cmin = 10;
    // int cmax = 10000;
    // std::vector<std::vector<cv::Point>>:: 
        // const_iterator itc = contours.begin();
    // while (itc != contours.end()) {
        // if (itc->size() < cmin || itc->size() > cmax) {
            // itc = contours.erase(itc);
        // } else {
            // ++itc;
        // }
    // }
    // cv::drawContours(result, contours, -1, cv::Scalar(0), 2);
    double ret=cv::contourArea(contours, 0);
    
    cv::imshow("contours image", result);
    cv::waitKey(); 
    return 0;
}
