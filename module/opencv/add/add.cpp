/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-08-24 07:02
 * Last modified : 2020-08-24 07:02
 * Filename      : add.cpp
 * Description   : 
*********************************************************************/

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
namespace test {
}
int main(int argc, char **argv) {
  cv::Mat img = cv::imread("../data/lena.jpg", 1);
  cv::Mat img1 = cv::imread("../data/lena_tmpl.jpg", 1);
  cv::Mat result;
  // cv::addWeighted(img, 0.3, img1, 0.8, 0.0, result);
  // cv::add(img, img1, result);
  // cv::add(img, cv::Scalar(88), result);
  // cv::scaleAdd(img, 0.8, img1, result);
  result =  img *0.5+ img1*0.5;
  cv::imshow("add image", result);
  cv::waitKey(0);
 return 0;
}
