/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-08-20 20:25
 * Last modified : 2020-08-20 20:25
 * Filename      : io.cpp
 * Description   : 
*********************************************************************/

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;

int main(int argc, char **argv) {
  cv::Mat image = cv::imread("../data/lena.jpg");
  cv::namedWindow("orig image");
  cv::imshow("orig image", image);
  cv::Mat result;
  cv::flip(image, result, 1);
  cv::imshow("filp image", result);
  cv::flip(image, result, 0);
  cv::imshow("filp1 image", result);
  cv::waitKey(0);
  return 0;
}
