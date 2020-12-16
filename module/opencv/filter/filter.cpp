/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-08-28 15:19
 * Last modified : 2020-08-28 15:19
 * Filename      : filter.cpp
 * Description   : 
*********************************************************************/

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgproc/types_c.h>

//低通滤波器目的是降低图像的变化幅度, 一个简单的方案是将每个像素替换为相邻像素的平均值.
using namespace std;
#define test
// 平均值滤波
#if defined test0

int main(int argc, char **argv) {
  cv::Mat img = cv::imread("../data/lena.jpg", 1);
  cv::Mat result;
  cv::blur(img, result, cv::Size(5, 5));
  cv::imshow("blur img", result);
  cv::waitKey(0);
  return 0;
}
//gaussian 滤波, 加权滤波
#elif defined test1

int main(int argc, char **argv) {
  cv::Mat img = cv::imread("../data/lena.jpg", 1);
  cv::Mat result;
  cv::GaussianBlur(img, result, cv::Size(5, 5), 0.8);
  cv::imshow("blur img", result);
  cv::waitKey(0);
  
  return 0;
}
//使用pyrDown pyrUp 或者 resize() 进行图片缩放
#elif defined test2


int main(int argc, char **argv) {
  cv::Mat img = cv::imread("../data/lena.jpg", 1);
  cv::Mat result;
  cv::pyrDown(img, result);
  cv::imshow("pyrdown img", result);
  cv::pyrUp(result, img);
  cv::imshow("up img", img);
  cv::resize(img, result, cv::Size(img.cols/6, img.rows/6));
  cv::imshow("resize img", result);
  
  cv::waitKey(0);

  return 0;
}
#elif defined test3
//中值滤波器
int main(int argc, char **argv) {
  cv::Mat img = cv::imread("../data/lena.jpg", 1);
  cv::Mat result;
  cv::medianBlur(img, result, 5);
  cv::imshow("midianBlur img", result);
  cv::waitKey(0);

  return 0;
}
#elif defined test4
//使用方向滤波器检测边缘, 使用高通滤波器进行边缘滤波, 我们这里使用的滤波器称为
//sobel 滤波器, 它具有方向性, 根据使用核的不同, 它只改变图像的垂直或垂直频率, 
//opencv 拥有一个对图像的运算的sobel 运算的函数水平滤波使用方式如下:
//cv::sobel(image, sobelX, CV_8U, 1, 0, 3, 0.4, 128);
//垂直滤波函数的使用的方式如下:
//cv::sobel(image, sobelY, CV_8U, 1, 0, 3, 0.4, 128);
//sobel 算子是一种经典的边缘检测线性滤波器, 他基于一个简单的3x3核, 如果我们将
//图像视为二维函数, sobel 算子可以认为是图像在水平方向上的测量, 这种测量在数学中
//被称为梯度, 他被定义为函数在两个正交方向的一阶组成的二维向量.
int main(int argc, char **argv) {
  cv::Mat img = cv::imread("../data/lena.jpg", 1);
  cv::Mat result;
  cv::Sobel(img, result, CV_8U, 1, 0);
  cv::imshow("sobel img", result);
  cv::Mat result1;
  cv::Sobel(img, result1, CV_8U, 0, 1);
  cv::imshow("sobel img1", result1);
  cv::waitKey(0);
  return 0;
}
#elif defined test4
int main(int argc, char **argv) {
  cv::Mat img = cv::imread("../data/lena.jpg", 0);
  cv::Mat result;
  cv::Sobel(img, result, CV_16S, 1, 0);
  cv::Mat result1;
  cv::Sobel(img, result1, CV_16S, 0, 1);
  cv::Mat sobel;
  sobel = cv::abs(result1) + cv::abs(result);
  double sobel_min;
  double sobel_max;
  cv::minMaxLoc(sobel, &sobel_min, &sobel_max);
  cv::Mat sobel_img;
  sobel.convertTo(sobel_img, CV_8U, -255./sobel_max, 255);
  cv::imshow("sobel img1", sobel_img);
  cv::Mat threshold_img;
  cv::threshold(sobel_img, threshold_img, 240, 255, cv::THRESH_BINARY);
  cv::imshow("threhold img", threshold_img);
  cv::waitKey(0);
  return 0;

}
#elif defined test
//laplacian是另一种基于图像导数的高通线性滤波器, 他计算二届导数以计算以衡量图像的弯曲度.
//opencv 使用cv::laplacian()函数计算一幅图像的laplacian, 他与sobel函数很类似, 事实上他们
//使用同一个基础函数cv::getDriveKernels()来获取矩阵核, 唯一的差别是不存在指定导数阶数的
//参数.因为他们都是二阶导数.:
//二维函数的laplacian计算他的二阶导数之和.它使用最间单的形式. 可以使用最简单的矩阵和:
/*
    +---+---+--+
    | 0 | 1 |0 |
    +---+---+--+
    | 1 |-4 |1 |
    +---+---+--+
    | 0 | 1 |0 |
    +---+---+--+
*/
//由于这个函数对于噪点更为敏感, 由于laplacian度量函数的曲率, 它在平坦区域应为0  
class laplacianZC {
  public:
    laplacianZC(int aperture  = 3) { aperture_ = aperture; }
    void set_aperature(int aperature) {
      aperture_ = aperature; 
    }
    cv::Mat compute_laplacian(const cv::Mat &image) {
      cv::Laplacian(image, laplacian_img, CV_32F, aperture_); 
      img = image.clone();
      return laplacian_img;
    }
//返回8位图像存储的laplacian结果
//零点交叉与灰度值128,
//如果没有指定scale参数, 那么他的最大值将缩放至255.
//
    cv::Mat get_laplacian_img(double scale = -1.0) {
      if (scale < 0) {
        double lap_max, lap_min;  
        cv::minMaxLoc(laplacian_img, &lap_max, &lap_min, 0, 0);
        scale = 127 / std::max(lap_min, lap_max);
      }
      cv::Mat result;
      laplacian_img.convertTo(result, CV_8U, scale, 128);
       return result;
    }
    //得到零点交叉的二值图像
    //如果相邻像素的乘积小于threhold
    //那么零点交叉将被忽略不计
    cv::Mat get_zero_crossings(float threshold = 1.0) {
      cv::Mat_<float>::const_iterator it_beg = laplacian_img.begin<float>() + laplacian_img.step1(); 
      cv::Mat_<float>::const_iterator it_end = laplacian_img.end<float>();
      cv::Mat_<float>::const_iterator it_up = laplacian_img.end<float>();
      cv::Mat binary_img(laplacian_img.size(), CV_8U, cv::Scalar(255));
      cv::Mat_<uchar>::iterator it_out = binary_img.begin<uchar>() + binary_img.step1(); 
      threshold *= -1;

      for (; it_beg != it_end; ++it_beg, ++it_out, ++it_up) {
        if (*it_beg * *(it_beg - 1) < threshold) *it_out = 0;
        else if (*it_up * *it_beg < threshold) *it_out = 0;
      }
      return binary_img;
    }

  private:
    cv::Mat img;
    cv::Mat laplacian_img;
    int aperture_;
};
int main(int argc, char **argv) {
  cv::Mat img = cv::imread("../data/lena.jpg", 1);
  laplacianZC lc;
  lc.compute_laplacian(img);
  cv::Mat result = lc.get_laplacian_img();
  cv::Mat binary = lc.get_zero_crossings(180);
  cv::imshow("binary img", binary);
  cv::imshow("laplacian img", result);
  cv::waitKey(0);

  return 0;
}
#endif

