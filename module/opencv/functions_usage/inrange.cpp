/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-09-07 18:02
 * Last modified : 2020-09-07 18:02
 * Filename      : inrange.cpp
 * Description   : 
*********************************************************************/

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
#define test
#if defined test1

int main(int argc, char **argv) {
  cv::VideoCapture cap;
  cap.open(0);
  if (!cap.isOpened()) {
    std::cout << "Video init error" << std::endl;
    return -1;
  }
  cv::Mat frame;
  cv::Mat img;
  cv::Mat result;
  cv::namedWindow("input img");
  for (;;) {
    cap >> frame;
    frame.copyTo(img);
    cv::imshow("input img", img);
    if (frame.empty()) break;
    cv::inRange(img, cv::Scalar(0, 30, 40), cv::Scalar(199, 255, 90), result);
    cv::imshow("inRange img", result);
    const char key = (char)cv::waitKey(30);
    if (key == 'q') break;

  }
  return 0;
}
#elif defined test

int main(int argc, char **argv) {
  cv::Mat img(10, 20, CV_8U, cv::Scalar::all(0));
  cv::imshow("orig img", img);
  cv::bitwise_not(img, img);
  cv::imshow("not img", img);
  char c = (char)cv::waitKey(0);
  if (c == 17) return 0;
  if (c == 'q') return 0;
  return 0;
}
#endif

