/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-12-14 10:54
 * Last modified : 2020-12-14 10:54
 * Filename      : split_merge.cpp
 * Description   : 
*********************************************************************/

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <vector>

using namespace std;

int main(int argc, char **argv) {
  std::vector<cv::Mat> plane;
  cv::Mat img = cv::imread("../../data/lena.jpg");
  cv::split(img, plane);
  cv::Mat result;
  cv::Mat logo = cv::imread("../../data/box.png", 0);
  cv::Mat roi = plane[1](cv::Rect(0, 0, logo.cols, logo.rows));
		cv::addWeighted(roi, 1.0, logo, 1.0, 0.0, roi);

  cv::merge(plane, result);
  cv::imshow("merge img", result);
  cv::waitKey();
  return 0;
}
