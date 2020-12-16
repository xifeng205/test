/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-08-23 13:58
 * Last modified : 2020-08-23 13:58
 * Filename      : sharpend.cpp
 * Description   :
 *********************************************************************/

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
namespace test {
// current_pix = 5 * current_pix -  up - down - left - right;
void img_sharpend(cv::Mat &img, cv::Mat &result) {
  int ncols = img.cols * img.channels();
  int rows = img.rows;
  result.create(img.size(), img.type());
  for (int i = 1; i < rows - 1; ++i) {
    const uchar *pre = img.ptr<const uchar>(i - 1);
    const uchar *cur = img.ptr<const uchar>(i);
    const uchar *next = img.ptr<const uchar>(i + 1);
    uchar *out = result.ptr<uchar>(i);
    for (int j = 1; j < ncols - 1; ++j) {
      out[j] = cv::saturate_cast<uchar>(cur[j] * 5 - cur[j - 1] - cur[j + 1] -
                                        pre[j] - next[j]);
    }
  }
  result.row(0).setTo((cv::Scalar(0)));
  result.row(rows - 1).setTo((cv::Scalar(0)));
  result.col(0).setTo((cv::Scalar(0)));
  result.col(result.cols - 1).setTo((cv::Scalar(0)));
}
} // namespace test
int main(int argc, char **argv) {
  cv::Mat img = cv::imread("../data/lena.jpg", 1);
  cv::Mat result;
  test::img_sharpend(img, result);
  cv::imshow("sharpen image", result);
  cv::waitKey(0);
  return 0;
}
