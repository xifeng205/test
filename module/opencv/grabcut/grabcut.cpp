/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-08-28 13:52
 * Last modified : 2020-08-28 13:52
 * Filename      : grabcut.cpp
 * Description   : 
*********************************************************************/

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgproc/types_c.h>

using namespace std;

int main(int argc, char **argv) {
  cv::Mat img = cv::imread("../data/detect_blob.png", 1); 
  cv::imshow("df", img);
  cv::Rect rect(39, 43, 300, 300);
  cv::Mat result;
  cv::Mat bg;
  cv::Mat fg;
  cv::grabCut(img, result, rect, bg, fg, 5, cv::GC_INIT_WITH_RECT);
  cv::compare(result, cv::GC_PR_FGD, result, cv::CMP_EQ);
  cv::Mat foreground(img.size(), CV_8UC3, cv::Scalar(0, 0, 0));
  result &= 1;
  img.copyTo(foreground, result);

  cv::imshow("img", foreground);
  cv::waitKey(0);
 return 0;

}
