/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-08-23 12:25
 * Last modified : 2020-08-23 12:25
 * Filename      : color_reduce.cpp
 * Description   :
 *********************************************************************/

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
namespace test {
void color_reduce(cv::Mat_<cv::Vec3b> &img, int div) {
  int ncols = img.cols;
  int rows = img.rows;
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < ncols; ++j) {
      img(i, j)[0] = img(i, j)[0] / div * div + div / 2;
      img(i, j)[1] = img(i, j)[1] / div * div + div / 2;
      img(i, j)[2] = img(i, j)[2] / div * div + div / 2;
    }
  }
}
void color_reduce1(cv::Mat &img, int div) {
  int ncols = img.cols * img.channels();
  int rows = img.rows;
  for (int i = 0; i < rows; ++i) {
    uchar *data = img.ptr<uchar>(i);
    for (int j = 0; j < ncols; ++j) {
      *data = *data / div * div + div / 2;
      data++;
    }
  }
}
void color_reduce2(cv::Mat &img, int div) {
  cv::Mat_<cv::Vec3b>::iterator it_sta = img.begin<cv::Vec3b>();
  cv::Mat_<cv::Vec3b>::iterator it_end = img.end<cv::Vec3b>();
  for (; it_sta != it_end; ++it_sta) {
    (*it_sta)[0] = (*it_sta)[0] / div * div + div / 2;
    (*it_sta)[1] = (*it_sta)[1] / div * div + div / 2;
    (*it_sta)[2] = (*it_sta)[2] / div * div + div / 2;
  }
}
void color_reduce3(cv::Mat &img, int div) {
  uchar mask = 0xff << div;
  int rows = img.rows;
  for (int i = 0; i < rows; ++i) {
    uchar *data = img.ptr<uchar>(i);
    for (int j = 0; j < img.cols * img.channels(); ++j) {
      data[j] = data[j] & mask + div / 2;
    }
  }
}
} // namespace test
int main(int argc, char **argv) {
  cv::Mat img = cv::imread("../data/lena.jpg");
  cv::imshow("imag", img);
  test::color_reduce2(img, 128);
  cv::imshow("reduce imag", img);
  cv::waitKey(0);
  return 0;
}
