/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-08-20 22:52
 * Last modified : 2020-08-20 22:52
 * Filename      : filp.cpp
 * Description   : 
*********************************************************************/

#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>

using namespace std;

int main(int argc, char **argv) {
  cv::Mat image = cv::imread("../data/lena.jpg");
  cv::Mat result;
  cv::flip(image, result, 0);
  cv::imshow("flip image", result);
  cv::waitKey(0);
 return 0;
}
