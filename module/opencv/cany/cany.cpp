/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-09-01 14:33
 * Last modified : 2020-09-01 14:33
 * Filename      : cany.cpp
 * Description   :
 *********************************************************************/

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgproc/types_c.h>
#include <vector>
//提取直线轮廓直线及联通区域:
// 1. 使用cany算子检测轮廓
// 2. 使用霍夫变换检测直线
// 3. 用直线拟合一组点
// 4. 提取联通区域的轮廓
// 5. 计算联通区域的形状描述符
//为了对图像是实施基于内容的分析, 需要从像素中提取有意义的特征
//轮廓, 直线, 像素块都是定义像素内容的基本单元
using namespace std;
#define test
#if defined test1
//使用canny算子检测轮廓
//
//简单的二值边缘图像有两大缺点:
// 1. 检测的边缘过错, 这就意味着难以实现物体的精确定位.
// 2. 很难以找到这样一个边缘, 能够足够的检测到物体重要的边缘,
//    同时也不至于找到过多的次要边缘.
//    这种需要权衡的问题就是canny算子要解决的问题
//
// canny作用原理:
//  算子通常基于sobel算子,尽管也可以使用其他梯度算子,其核心思想是使用两个
//  不同的阈值确定那些点属于轮廓: 一个底值, 一个高值.
//  挑选的底值应该包或所有被认为是 属于明显图像的边缘轮廓.
//  第二个阈值的角色正是定义所有属于重要边缘的轮廓, 他应该排除所有 异常值. canny
//  算法组合这两幅边缘图以生成最优的轮廓图, 这种通过双阈值以得到二值图像的策略
//  被称为磁滞阈值化,
//
int main(int argc, char **argv) {

  cv::Mat img = cv::imread("../data/lena.jpg", 1);
  cv::Mat controus;
  cv::Canny(img, controus, 200, 300);
  cv::imshow("canny img", controus);
  cv::waitKey(0);
  return 0;
}
#elif defined test2
//使用霍夫变化检测直线
// hough transform is a tradition method for detect the line ,
// 后来被用于其他检测 简单结构. 在霍夫变换中直线用以下方式描述: ρ = xcosθ +
// ysinθ
//参数ρ是直线到原点的距离, θ则是与直线垂直的角度,
//而半角ρ的最大值为等于图像对角线
//
//                           |/
//                   \       |
//                    \     /|
//                     \   / |
//                  ----\-/--+--------
//                       X   |
//                      / \  |
//                     /   \ |
//
//
//实现方式:
// opencv2 提供两种霍夫变换的实现:
// 1. 基础版: HoughLines() , 他的输入是一组包含一组点的二值图像,
// 其中的一些排列后形 成直线, 通常是一幅图像的边缘图像, 比如来自canny算子,
// cv::HoughLines()的输出是一组 cv::Vec2f向量,
// 每个元素代表的是一组检测到的直线的浮点数(ρ, θ),
//霍夫变换仅仅是查找边缘点的一种排列方式,
//由于意外的排列或者多条线穿过同一组像素,
//
// 2. 很有可能得到错误的检测.为了克服这些空难, 同时检测到带端点的线段,
// 人们提出了改 进后的算法,即:概率霍夫变换.
// //
// #define t
// #if defined t1
// int main(int argc, char **arv) {
//   cv::Mat img = cv::imread("../data/home.jpg", 1);
//   cv::Mat canny_img;
//   cv::Canny(img, canny_img, 180, 350);
//   std::vector<cv::Vec2f> lines;
//   cv::HoughLines(canny_img, lines, 1, CV_PI / 180, 80);
//   std::vector<cv::Vec2f>::const_iterator it = lines.begin();
//   while (it != lines.end()) {
//     float rho = (*it)[0];
//     float theta = (*it)[1];
//     if (theta < CV_PI / 4 || theta > CV_PI * 3 / 4) {
//       cv::Point p1(rho / cos(theta), 0);
//       cv::Point p2((rho - img.rows * cos(theta)) / sin(theta), img.rows);
//       cv::line(img, p1, p2, cv::Scalar(255), 1);
//     } else {
//
//       cv::Point p1(0, rho / sin(theta));
//       cv::Point p2(img.cols, (rho - img.cols * sin(theta)) / cos(theta));
//       cv::line(img, p1, p2, cv::Scalar(255), 1);
//     }
//     ++it;
//   }
//   cv::imshow("hough img", img);
//   cv::waitKey(0);
//   return 0;
// }
// #elif defined t2
// //概率霍夫变换:houghLineP()
// //霍夫变换的目的是找到二值图像中经过足够多的点的所有直线, 他分析每个单独的像素点, 
// //并识别出所有经过他的直线, 当同一条直线穿过许多点, 便意味着这条直线的存在足够明显.
// //霍夫变换使用二维的累加器来统计特定的直线被识别了多少次,该累加器的尺寸由指定的(ρ, θ)
// //参数的步进尺寸来定义
// class LineFinder {
// public:
//   LineFinder()
//       : delta_rho(1), delt_theta(CV_PI / 180), min_vote(10), min_length(0),
//         max_gap(0.) {}
//   void set_acc_resolution(double drho, double dtheta) {
//     delta_rho = drho;
//     delt_theta = dtheta; 
//   }
//   void set_min_vote(int mval) {
//     min_vote= mval;
//   }
//   void set_line_length_and_gap(double len, double gap) {
//       min_length = len;
//       max_gap = gap;
//   }
//   std::vector<cv::Vec4i> find_lines(cv::Mat &binary) {
//       lines.clear(); 
//       cv::HoughLinesP(img, lines, delta_rho, delt_theta, min_vote, min_length, max_gap);
//       return lines;
//   }
//   void draw_detect_lines(cv::Mat &img, cv::Scalar color = cv::Scalar(255, 255, 255)) {
//     std::vector<cv::Vec4i>::const_iterator it = lines.begin(); 
//     while (it != lines.end()) {
//       cv::Point pt1((*it)[0], (*it)[1]); 
//       cv::Point pt2((*it)[2], (*it)[3]); 
//       cv::line(img, pt1, pt2, color, 1);
//       ++it;
//     }
//   }
//
// private:
//   cv::Mat img;
//   std::vector<cv::Vec4i> lines;
//   double delta_rho;
//   double delt_theta;
//   int min_vote;
//   double min_length;
//   double max_gap;
// };
// int main(int argc, char **argv) {
//   cv::Mat img = cv::imread("../data/aloeL.jpg", 1);
//   LineFinder lf;
//   lf.set_line_length_and_gap(100, 20);
//   lf.set_min_vote(80);
//   lf.find_lines(img);
//   lf.draw_detect_lines(img);
//   cv::imshow("lf img", img);
//   cv::waitKey(0);
//   return 0; 
// }
// #elif defined t3
// //霍夫变换也可以用于检测其他几何体, 事实上任何可以用参数方程表示的
// //几何体, 都可以尝试用霍夫变换检测. 
// //3 检测圆
// // (1) 使用二维的累加器找到圆的可能位置.原因在圆周上的点的梯度应该
// //     指向半径方向, 因此对于每个点只有沿着半径方向的项才会增加.
// // (2) 构建一维的值方图, 这个值方图的峰值对应这检测到的圆的半径
// //     实现了该策略的cv::HoughCircles() 整合了canny检测与霍夫变换 
// int main(int argc, char **argv) {
//   cv::Mat img = cv::imread("../data/stuff.jpg", 0);
//   cv::imshow("org img", img);
//   cv::GaussianBlur(img, img, cv::Size(5, 5), 1.5);
//   std::vector<cv::Vec3f> circles;
//   cv::HoughCircles(img, circles, CV_HOUGH_GRADIENT, 2, 50, 200, 50, 0, 200);
//   cv::Mat result(img.size(), CV_8U, cv::Scalar(0, 0, 0));
//   std::vector<cv::Vec3f>::const_iterator it = circles.begin();
//   
//   while (it != circles.end()) {
//     cv::circle(result, cv::Point((*it)[0],(*it)[1]), (*it)[2], cv::Scalar(255), 2);
//     ++it;
//   }
//   cv::imshow("hough circles img", result);
//   cv::waitKey(0);
//   return 0;
// }
// #elif defined t4
// //4 广义霍夫变换
// //
// int main(int argc, char **argv) {
//
//   return 0;
// }
// #endif
// #elif defined test4
// //4 用直线拟合一组点 
// int main(int argc, char **argv) {
//
//   return 0;
// }
#elif defined test
//5 提取联通区域
//图像中通常包含着物体的表现, 图像分析的一大目的便是识别并提取出这些物体, 
//在物体检测识别应用中, 第一步是生成包含生成特定物体的二值图像, 不论这个
//二值图像的获取如何, 我们通过简单的阈值化, 已经形态学开闭运算这幅图像,
//更明确的说法是我们将提取联通区域, 即由二值图像相连组成的图像.
//opencv 提供了一个简单的函数cv::findControus() 来提取联通区域. 
int main(int argc, char **argv) {
  cv::Mat img = cv::imread("../data/lena.jpg", 0);
  std::vector<std::vector<cv::Point()>> contours;
  cv::findContours(img, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
  cv::Mat result(img.size(), CV_8U, cv::Scalar(0));
  cv::drawContours(result, contours, -1,  cv::Scalar(255), 2);
  cv::imshow("contours img", result);
  cv::waitKey(0);

  return 0;
}
#endif
