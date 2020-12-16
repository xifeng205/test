/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-08-20 22:58
 * Last modified : 2020-08-20 22:58
 * Filename      : copyTo.cpp
 * Description   : 
*********************************************************************/

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;

int main(int argc, char **argv) {
  cv::Mat img = cv::imread("../data/left.jpg");
  cv::Mat result;
  img.copyTo(result);
  cv::imshow("result", result);
  cv::waitKey(0);
 return 0;
}
