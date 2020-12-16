/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-08-20 23:18
 * Last modified : 2020-08-20 23:18
 * Filename      : cvtColor.cpp
 * Description   : 
*********************************************************************/

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/types_c.h>

using namespace std;

int main(int argc, char **argv) {
  cv::Mat img = cv::imread("../data/left.jpg");
  cv::Mat result;
  cv::cvtColor(img, result, CV_RGB2BGR);
  cv::imshow("org image", img);
  cv::imshow("cvt image", result);
  cv::waitKey(0);
 return 0;
}
