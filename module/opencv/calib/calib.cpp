/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-11-28 23:19
 * Last modified : 2020-11-28 23:19
 * Filename      : calib.cpp
 * Description   : 
*********************************************************************/

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;

//估算图像间的投影关系
//★ 相机标定
//★ 计算一对图像间的基础矩阵(Fundmental Matrix)
//★ 使用随即采样一致算法(RANSAC) 进行图像匹配
//★ 计算两幅图像间的单应矩阵(Homography)

//投影几何是描述成像过程的工具
//相机针孔模型: h = ϝ*H/d

// 相机标定
int main(int argc, char **argv) {

  return 0;
}
