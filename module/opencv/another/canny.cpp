/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-11-23 13:43
 * Last modified : 2020-11-23 13:43
 * Filename      : canny.cpp
 * Description   : 
*********************************************************************/

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;

int main(int argc, char **argv) {
  cv::Mat img = cv::imread("../data/lena.jpg", 1);
  cv::imshow("orig img", img);
  cv::Mat contours;
  cv::Canny(img, contours, 100, 299);
  cv::imshow("canny img", contours);
  cv::waitKey(0);
  return 0;
}
