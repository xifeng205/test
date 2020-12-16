/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-05-24 11:21
 * Last modified : 2020-05-24 11:21
 * Filename      : salt.cpp
 * Description   : 
*********************************************************************/
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
        
using namespace std;
void salt_(cv::Mat &img, int n) 
{       
    cv::Mat_<cv::Vec3b>img_ = img;

    for (int k=0; k<n; ++k) {
        int i = rand() % img.cols;
        int j = rand() % img.rows;
        if (img_.channels() == 1) {
            img_(j, i) = 255;
        } else if (img.channels() == 3) {
            img_(j, i)[0] = 255;
            img_(j, i)[1] = 255;
            img_(j, i)[2] = 255;
        }
    }
}

void salt(cv::Mat &img, int n) 
{       
    for (int k=0; k<n; ++k) {
        int i = rand() % img.cols;
        int j = rand() % img.rows;
        if (img.channels() == 1) {
            img.at<uchar>(j, i) = 255;
        } else if (img.channels() == 3) {
            img.at<cv::Vec3b>(j, i)[0] = 255;
            img.at<cv::Vec3b>(j, i)[1] = 255;
            img.at<cv::Vec3b>(j, i)[2] = 255;
        }
    }
}
int main(int argc, char **argv)
{
    cv::Mat image1;
    image1 = cv::imread("./butterfly.jpg");
    salt(image1, 20000);
    salt_(image1, 20000);
    cv::namedWindow("hellow opencv");
    cv::imshow("hellow opencv", image1);
    cv::waitKey(10000);
    return 0;
}
