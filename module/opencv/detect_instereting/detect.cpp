/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-09-02 16:49
 * Last modified : 2020-09-02 16:49
 * Filename      : detect.cpp
 * Description   :
 *********************************************************************/

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgproc/types_c.h>
#include <opencv2/features2d/features2d.hpp>
#include <vector>

using namespace std;
//检测并匹配兴趣点
// 1. 检测harris角点
// 2. 检测fast特征
// 3. 检测尺度不变surf特征
// 4. 描述surf特征
//
//在计算机视觉中, 兴趣点(关键点, 特征点), 被用于大量检测物体识别, 图像
//匹配, 视觉跟踪, 三维重建等问题, 他依赖这个想法, 即不再观察整副图像,
//而是选择某些特殊的点, 然后对他们执行局部分析, 如果能检测到足够多的这
//种点, 同时他们的区分度很高, 并且可以精确定位稳定的特征, 那么这种方法就
//有效.
#define test
#if defined test1
//检测harris角点:
//在图像中进行兴趣点检测时, 角点可以做为一个有趣的方案, 他们在图像中可以
//轻易的定位, 同时他们在人造物体中随处可见. 角点的意义在于在于他们是可以
//精确定位的二维特征, 因为他们位于两条边的交点处, 轮廓难以在其他相同的物
//上精确定位. harris角点检测是一种经典的角点检测器.
//
//作用原理:
//为了定义图像中的角点, harris观察一个假定的特征点周围小窗口内方向性强度
//平均变化, 如果我们考虑方向向量(υ, ѵ), 他的平均强度变化为:
//       Ʀ ≈ ∑ ( I(х + υ, y + ѵ) - I(x, y) )²
//求和过称中覆盖了预定义的相邻像素点, 相邻像素的尺寸对应cv::harrisCorner()
//的第单个参数, 强度变化的平均值在多有可能的方向进行计算, 因为高强度变化会
//出现在多个方向, 通过这个定义, harris测试的过程如下, 我们首先获取平均强度
//变化最大的强度方向.接着检测位于他垂直方向的强度是否也很强烈, 同时满足条件
//的便是一个角点.
//用数学术语讲, 测试这个条件可以使用泰勒基数对先前公式进行近似.
//协方差矩阵的两个eigen给出的了最大平均强度变化以及垂直方向上的强度比阿变化
//如果这两个特征值比较底, 那么我们位于相同同质区域. 如果其中一个高, 一个底,
//那我们一定位于边上, 如果这两个特征值都比较高值那么我们肯定位于角点处,因此
//角点存在的条件是拥有超过阈值协方差矩阵的最小特征值, harris角点算法的原始
//定义, 使用使用特征分解理论的一些特性避免计算特征值, 这些特性包括:
//(1) 矩阵的特征值之积等于他的行列式;
//(2) 矩阵的特征值之和都与他的对角线之和, 即他的迹;
//然后我们通过下属式子验证特镇值是否足够高
//             Score = Det(c) - ktrace²(c);
//我们轻易的验证只有两个特征值都高时, 上述式子才能的高分,
//这正是cv::cornerHarris() 在每个像素点位置计算的得分, k的值指定为函数的第5个值,
//也许很难确定最优值, 然而 在实践经验中, 通常0.05 ~ 0,5之间能取得最优值,
//为了改进非极大值抑制,目的是移除 彼此相临的Harris角点, 因此, 为了最终被接受,
//Harris角点不只需要的分高于给定阈值 他还必须是局部极大值, 测试时使用简单的技巧,
//包阔在harris得分图像进行膨胀,
int main(int argc, char **argv) {
  cv::Mat img = cv::imread("../data/lena.jpg", 0);
  cv::Mat corner_strength;
  cv::cornerHarris(img, corner_strength, 3, 3, 0.01);
  cv::Mat harris;
  cv::threshold(corner_strength, harris, 0.0001, 255, cv::THRESH_BINARY);
  cv::imshow("hariss img", harris);
  cv::waitKey(0);

  return 0;
}
#elif defined test2
class HarrisDetect {
private:
  //表示角点强度的32位浮点图
  cv::Mat cornerStrengh;
  //表示阈值化后的32位浮点图
  cv::Mat cornerTh;
  cv::Mat localMax;
  //导数平滑的相邻相邻尺寸
  int neighbourhood;
  //梯度计算的孔径大小
  int aperture;
  // harris 参数
  double k;
  //阈值计算的最大强度
  double maxStrengh;
  //计算得到的阈值
  double threshold;
  //非极大值抑制的相邻像素尺寸
  int nonMaxSize;
  //非极大值抑制的核
  cv::Mat kernel;

public:
  HarrisDetect()
      : neighbourhood(3), aperture(3), k(0.01), maxStrengh(0.0),
        threshold(0.01), nonMaxSize(3) {
    setLocalMaxWindowSize(nonMaxSize);
  }

  void setLocalMaxWindowSize(int n) { nonMaxSize = n; };

  void detect(cv::Mat &img) {
    cv::cornerHarris(img, cornerStrengh, neighbourhood, aperture, k);
    double minStrengh;
    cv::minMaxLoc(cornerStrengh, &minStrengh, &maxStrengh);
    cv::Mat dialate;
    cv::dilate(cornerStrengh, dialate, cv::Mat());
    cv::compare(cornerStrengh, dialate, localMax, cv::CMP_EQ);
  }
  cv::Mat getCornersMap(double qualityLevel) {
    cv::Mat corner_map;
    threshold = qualityLevel * maxStrengh;
    cv::threshold(cornerStrengh, cornerTh, threshold, 255, cv::THRESH_BINARY);
    cornerTh.convertTo(corner_map, CV_8U);
    cv::bitwise_and(corner_map, localMax, corner_map);
    return corner_map;
  }
  void getCorners(std::vector<cv::Point> &pt, double qualityLevel) {
    cv::Mat corner_map = getCornersMap(qualityLevel);
    getCorners(pt, corner_map);
  }

  void getCorners(std::vector<cv::Point> &pt, cv::Mat &corner_map) {
    for (int i = 0; i < corner_map.rows; ++i) {
      const uchar *p = corner_map.ptr<uchar>(i);
      for (int j = 0; j < corner_map.cols; ++j) {
        if (p[j]) {
          pt.push_back(cv::Point(j, i));
        }
      }
    }
  }
  void drawImage(cv::Mat &img, const std::vector<cv::Point> &pt,
                 cv::Scalar color = cv::Scalar(255, 255, 255), int radius = 3,
                 int thickness = 2) {
    std::vector<cv::Point>::const_iterator it = pt.begin();
    for (; it != pt.end(); ++it) {
      cv::circle(img, *it, radius, color, 2);
    }
  }
};
int main(int argc, char **argv) {
  cv::Mat img = cv::imread("../data/Blender_Suzanne1.jpg", 0);
  HarrisDetect hd;
  hd.detect(img);
  std::vector<cv::Point> pt;
  hd.getCorners(pt, 0.01);
  hd.drawImage(img, pt);
  cv::imshow("harris img", img);
  cv::waitKey(0);

  return 0;
}
#elif defined test3
// opencv 其他的角点检测器
//(1) 适合跟总的优质特征
//在浮点处理器的帮助下, 为了避免特征分解而而引入的数学上的简化而变得微不卒到
//因此harris可以通过计算而得到特征值, 这个修带不会显著影响检测的结果, 但是能
//避免使用任意的k参数,
//第二个修改用于解决特征点的聚类问题, 除了引入局部极大值外, 特征点倾向于在图像
//中不均匀分布, 集中在纹理丰富部分, 一种解决方案是利用特征点之间的最小距离, 我
//们从harris得分最高点开始, 仅接受离开有效特征点距离大于特定值的点, 这便是
// cv::GoodFeatureToTrack() 要实现的, 他检测到的点能用于视觉跟踪应用中优质特征
//集合,
//
int main(int argc, char **argv) {
  cv::Mat img = cv::imread("../data/Blender_Suzanne1.jpg", 0);
  std::vector<cv::Point> corners;
  cv::goodFeaturesToTrack(img, corners, 500, 0.01, 10);
  std::vector<cv::Point>::const_iterator it = corners.begin();
  for (; it != corners.end(); ++it) {
    cv::circle(img, *it, 3, cv::Scalar(255, 255, 255), 2);
  }
  cv::imshow("goodFeaturesToTrack img", img);

  cv::waitKey(0);
  return 0;
}
#elif defined test4
//特征检测器通用接
// opencv2 通用特征检测器引入了一种新的通用接口用于不同的检测器, 该接口用于在
//同一应用中简单测试不同的检测器
//抽象类cv::FeatureDetector提供了不同签名的签名的检测函数
//
int main(int argc, char **argv) {
  std::vector<cv::KeyPoint> kp;
  // cv::GoodFeaturesToTrack gfd;

  return 0;
}
#elif defined test5
//检测fast特征
// harris 提出了角点检测的正式定义, 他基于两个正交方向上的变化率, 尽管这是一个
//合理的定义, 他需要耗时的计算图像的导数, 尤其考虑到特征点值是其中的一部分
// fast 特征检测器, 能够依赖少量的像素比较来确定是否接受这一特征点
//作用原理:
//于harris相同的是FAST(Feature From Accelerated Segment Test)特征点需要定义
//什么是角点, 这次的定义是基于假定的特征点周围的图像强度, 通过检查候选像素
//周围的像素周围一圈来决定是否接受这一特征点
int main(int argc, char **argv) {
  std::vector<cv::KeyPoint> kp;
  cv::FastFeatureDetector fast(40);
  fast.detect(img, kp);
  cv:: Mat result;
  cv::drawKeypoints(img, kp, result, cv::Scalar(255, 255, 255),
                    cv::DrawMatchesFlags::DRAW_OVER_OUTIMG);
  cv::imshow("fast img", result);
  cv::waitKey(0);

  return 0;
}
#elif defined test
//检测尺度不变的SURF特征
//当尝试在不同的图像之间匹配特征时, 我们通常面临尺度变化的难题, 即需要分析的图像
//在拍摄时与目标图像的距离是不同的和因此, 目标物体在图像中有些不同的尺寸, 如果我
//们尝试使用固定尺寸的相邻尺寸来匹配不同图像中的相同特征, 那么由于尺度的变化, 
//他的强度模版并不会匹配.
//为了解决这个问题, 计算机视觉中, 引入了尺度不变的特征, 主要的思想是每个检测到
//的特征点都伴随这对应的尺寸因子, 经年来, 人们提出了多个尺度不变特征, 本则秘诀
//展示其中之一, 即SURF(Speeded Up Robust Features)特征------加速鲁棒特征.我们可以
//看到他们不仅有尺度不变的特征, 而且计算非常高效.
//SURF特征在opencv中的实现也使用了cv::FeatureDectector接口
//一幅图像的导数可以高通滤波器进行计算, 这些滤波器使用σ来决定滤波和的大小
int main(int argc, char **argv) { 
  std::vector<cv::KeyPoint> kp;
  cv::SurfFeatureDetector(25000.);
  return 0;
}
#endif
