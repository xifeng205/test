/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-08-24 07:54
 * Last modified : 2020-08-24 07:54
 * Filename      : roi.cpp
 * Description   : 
*********************************************************************/

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>


using namespace std;

int main(int argc, char **argv) {
  cv::Mat img = cv::imread("../data/lena.jpg", 1);
  cv::Mat logo = cv::imread("../data/LinuxLogo.jpg", 1);
  cv::Mat mask = cv::imread("../data/LinuxLogo.jpg", 0);


  // cv::Mat roi_img = img(cv::Rect(58, 88, logo.cols, logo.rows));
  // cv::Mat roi_img = img(cv::Rect(58, 88, logo.cols, logo.rows));
  cv::Mat roi_img = img(cv::Range(0, logo.rows), cv::Range(0, logo.cols));
  logo.copyTo(roi_img, mask);

  // cv::Mat r = img.rowRange(0, 18);
  // cv::imshow("line", r);

  // cv::addWeighted(logo, 0.8, roi_img, 0.2, 0., roi_img);
  cv::imshow("img", img);
  cv::waitKey(0);
 return 0;
}
