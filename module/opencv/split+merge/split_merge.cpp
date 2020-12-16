/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-08-24 07:28
 * Last modified : 2020-08-24 07:28
 * Filename      : split_merge.cpp
 * Description   :
 *********************************************************************/

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;

int main(int argc, char **argv) {
  cv::Mat result;
  cv::Mat img = cv::imread("../data/lena.jpg", 1);
  cv::Mat img1 = cv::imread("../data/lena_tmpl.jpg", 0);
  std::vector<cv::Mat> planes;
  cv::split(img, planes);
  planes[0] += img1 ;
  cv::merge(planes, result);
  cv::imshow("merge img", result);
  cv::waitKey(0);

  return 0;
}
