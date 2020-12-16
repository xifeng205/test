/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-09-10 15:00
 * Last modified : 2020-09-10 15:00
 * Filename      : test.cpp
 * Description   : 
*********************************************************************/

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>


int main(int argc, char **argv) {
  int threshold = 100;
  cv::Mat img =  cv::imread("../../../data/detect_blob.png", 0);
  cv::Mat thresh = threshold < 128 ? (img < threshold) : (img > threshold);
  cv::imshow("img", thresh);
  cv::waitKey(0);

  return 0;
}
