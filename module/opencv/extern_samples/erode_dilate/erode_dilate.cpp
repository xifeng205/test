/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-06-04 08:00
 * Last modified : 2020-06-04 08:00
 * Filename      : erode_dilate.cpp
 * Description   : 
*********************************************************************/

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;

int main(int argc, char **argv)
{
    cv::Mat image = cv::imread("../../../data/butterfly.jpg", 0);
    cv::imshow("orign image", image);
    cv::Mat eroded;
    cv::erode(image, eroded,cv::Mat());
    cv::imshow("erode image", eroded);

    cv::Mat dilated;
    cv::dilate(image, dilated, cv::Mat());
    cv::imshow("dilate image", dilated);
    
    cv::Mat dilate;
    cv::Mat element(7, 7, CV_8U, cv::Scalar(1));
    cv::dilate(image, dilate, element);
    cv::imshow("7x7 dilate image", dilate);

    cv::waitKey(0);
    return 0;
}
