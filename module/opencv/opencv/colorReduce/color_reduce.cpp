/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-11-30 23:29
 * Last modified : 2020-11-30 23:29
 * Filename      : color_reduce.cpp
 * Description   :
 *********************************************************************/
//颜色缩减:
//为什么进行颜色缩减: 假如一幅3通道的图像, 每个通道的像素值是8位的,
//那么3channel 总共有256*256*256 约等于160000颜色要处理, 为了减少处理的
//颜色数量, 减少算法的复杂度,可以对颜色进行缩减是非常有必要的
//
//实现方式:
//可以RGB颜色空间划分为同等大小的网格, 每一维度缩减为原来的N倍, 那么
//总共的颜色空间就变为256/N * 256 / N * 256 / N了, 然后将图像每一个像素
//替换为像素对应网格中间所对应的位置.
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;

void colorReduce0(cv::Mat &img, const unsigned int div) {
  int ncols = img.cols * img.channels();
  int rows = img.rows;
  for (int i = 0; i < rows; ++i) {
    uchar *data = img.ptr<uchar>(i);
    for (int j = 0; j < ncols; ++j) {
      data[j] = data[j] / div * div;
    }
  }
}
void colorReduce1(cv::Mat &img, int div) {
  int ncols = img.cols * img.channels();
  int rows = img.rows;
  if (img.isContinuous()) {
    ncols = ncols * rows;
    rows = 1;
  }

  for (int i = 0; i < rows; ++i) {
    uchar *data = img.ptr<uchar>(i);
    for (int j = 0; j < ncols; ++j) {
      data[j] = data[j] / div * div + div / 2;
    }
  }
}

void colorReduce(cv::Mat &img, int div) {
  int ncols = img.cols * img.channels();
  int rows = img.rows;
  // cv::Mat_<cv::Vec3b>::iterator it_begin = img.begin<cv::Vec3b>();
  // cv::Mat_<cv::Vec3b>::iterator  it_end = img.end<cv::Vec3b>();
  cv::MatIterator_<cv::Vec3b> it_begin;
  cv::MatIterator_<cv::Vec3b> it_end;
  for (; it_begin != it_end; ++it_begin) {
    (*it_begin)[0] = (*it_begin)[0] / div * div + div / 2;
    (*it_begin)[1] = (*it_begin)[1] / div * div + div / 2;
    (*it_begin)[2] = (*it_begin)[2] / div * div + div / 2;
  }
}
int main(int argc, char **argv) {
  cv::Mat img = cv::imread("../../data/lena.jpg");
  int div = 32;
  double duration = static_cast<double>(cv::getTickCount());
  colorReduce(img, div);
  double interval = static_cast<double>(cv::getTickCount()) - duration;
  double time = interval / cv::getTickFrequency();
  std::cout << "cost time : " << time << std::endl;

  cv::namedWindow("colorReduce img");
  cv::imshow("colorReduce img", img);
  cv::waitKey();

  return 0;
}
