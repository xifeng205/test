/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-11-15 14:25
 * Last modified : 2020-11-15 14:25
 * Filename      : distroy_window.cpp
 * Description   : 
*********************************************************************/

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace std;

int main(int argc, char **argv) {
  cv::Mat img(1000, 1000, CV_8UC3, CV_RGB(255, 255, 255));
  cv::imshow("test img", img);
  cv::destroyAllWindows();
  cv::waitKey(0);
  return 0;
}
