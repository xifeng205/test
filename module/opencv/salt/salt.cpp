/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-08-22 17:40
 * Last modified : 2020-08-22 17:40
 * Filename      : salt.cpp
 * Description   :
 *********************************************************************/

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <random>

using namespace std;
namespace test {
void salt(cv::Mat &img, int n) {
  int i, j;
  for (int k = 0; k < n; ++k) {
      i = rand() % img.rows;
      j = rand() % img.cols;
    if (img.channels() == 1) {
   img.at<uchar>(i, j) = 255;
    } else if (img.channels() == 3) {
      img.at<cv::Vec3b>(i, j)[0] = 255;
      img.at<cv::Vec3b>(i, j)[1] = 255;
      img.at<cv::Vec3b>(i, j)[2] = 255;
    }
  }
}
} // namespace test
int main(int argc, char **argv) {
  cv::Mat img = cv::imread("../data/lena.jpg", 1);
  test::salt(img, 9900);
  cv::imshow("salt image", img);
  cv::waitKey(0);
  return 0;
}
