/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-11-30 22:00
 * Last modified : 2020-11-30 22:00
 * Filename      : salt.cpp
 * Description   : 
*********************************************************************/

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;

void salt(cv::Mat &img, const int n){
  int cols = img.cols;
  int rows = img.rows;
  //随机设置n个噪点, 相当于n重循环
  for(int k = 0;k < n; ++k) {
    //随机生成像素点的位置
    int i = rand() % cols;
    int j = rand()%rows;
    //判断通道数
    if(img.channels() == 1) {
      img.at<uchar>(i, j) = 255;
    }else if(img.channels() == 3) {
      img.at<cv::Vec3b>(i, j)[0] = 255;
      img.at<cv::Vec3b>(i, j)[1] = 255;
      img.at<cv::Vec3b>(i, j)[2] = 255;
    }
  }
}

int main(int argc, char **argv) {
  cv::Mat img = cv::imread("../../data/lena.jpg");
  if(!img.data) {
    fprintf(stderr, "image read error");
    exit(-1);
  }
  int n = 1000;
  salt(img, n);
  cv::imshow("salt img", img);
  cv::waitKey(0);
}
