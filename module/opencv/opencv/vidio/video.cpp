/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-12-14 14:52
 * Last modified : 2020-12-14 14:52
 * Filename      : video.cpp
 * Description   :
 *********************************************************************/

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/videoio/legacy/constants_c.h>
#include <opencv2/videoio/videoio.hpp>

using namespace std;

int main(int argc, char **argv) {
  int ret;
  bool stop = false;
  cv::VideoCapture vp(0string);
  if (!vp.isOpened()) {
    std::cout << "video open error." << std::endl;
    return -1;
  }
  float fps = 1000 / vp.get(CV_CAP_PROP_FPS);
  cv::Mat frame;
  while (!stop) {
    if (!vp.read(frame))
      break;
    cv::imshow("video", frame);
    if (cv::waitKey(fps) > 0) {
      stop = true;
    }
  }
  return 0;
}
