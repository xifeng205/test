/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-09-05 22:37
 * Last modified : 2020-09-05 22:37
 * Filename      : fgbg.cpp
 * Description   : 
*********************************************************************/

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgproc/types_c.h>
#include <opencv2/video/video.hpp>

using namespace std;

int main(int argc, char **argv) {
  cv::VideoCapture vp("/dev/video0");
  if (!vp.isOpened()) return 0;
  cv::Mat frame;
  cv::Mat foreground;
  // cv::BackgroundSubtractor mog;
  while (1){

    
  }
  return 0;
}
