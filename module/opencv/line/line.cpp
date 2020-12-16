/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-12-14 14:23
 * Last modified : 2020-12-14 14:23
 * Filename      : line.cpp
 * Description   : 
*********************************************************************/

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
int main(int argc, char **argv) {

  cv::Mat img(400, 400, 0);
  cv::Point pt0(10, 30);
  cv::Point pt1(60, 80);
  cv::line(img, pt0, pt1, cv::Scalar(255));
  cv::imshow("black img", img);
  cv::waitKey();
  return 0;
}
