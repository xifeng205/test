/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-08-23 07:37
 * Last modified : 2020-08-23 07:37
 * Filename      : mat_.cpp
 * Description   :
 *********************************************************************/

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
class salt {
public:
  salt(char file_name[], char channels = 1, int salt_num = 0) {
    img_ = cv::imread(file_name, 1);
    channels_ = channels;
    salt_num_ = salt_num;
  }
  void salt_process();
  void set_salt_num(int n);
  void img_show();
  void salt_process_();

private:
  cv::Mat img_;
  cv::Mat_<uchar> img__;
  int salt_num_;
  char channels_;
};
void salt::salt_process() {
  int i, j;
  for (int n = 0; n < salt_num_; ++n) {
    i = rand() % img_.rows;
    j = rand() % img_.cols;
    if (img_.channels() == 1) {
      img_.at<uchar>(i, j) = 255;
    } else if (img_.channels() == 3) {
      img_.at<cv::Vec3b>(i, j)[0] = 255;
      img_.at<cv::Vec3b>(i, j)[1] = 255;
      img_.at<cv::Vec3b>(i, j)[2] = 255;
    }
  }
}
void salt_process_() {

}
void salt::img_show() { cv::imshow("slat image", img_); }
void salt::set_salt_num(int n) { salt_num_ = n; }
int main(int argc, char **argv) {
  char img[] = "../data/lena.jpg";
  salt salt(img);
  salt.set_salt_num(999);
  salt.salt_process();
  salt.img_show();
  cv::waitKey(0);

  return 0;
}
