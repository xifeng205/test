/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-08-24 14:02
 * Last modified : 2020-08-24 14:02
 * Filename      : calHist.cpp
 * Description   :
 *********************************************************************/

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#define test
using namespace std;
class histgram1d {
public:
  histgram1d() {
    hist_size[0] = 256;
    channels[0] = 0;
    hranges[0] = 0.0;
    hranges[1] = 255.0;
    ranges[0] = hranges;
  }
  cv::MatND get_histgram(cv::Mat img);
  cv::Mat get_histgram_img(const cv::Mat &image);
  cv::Mat apply_lut(const cv::Mat &image);
  cv::Mat equalize(const cv::Mat &image);
  void init_lut();
  void set_mask(cv::Mat &mask);
  void set_ranges(char range[]);
  void set_channels(char channel[]);
  void init_invert_ltb(void);
  void init_strtch_ltb(cv::Mat &img, int min_val = 0);
  cv::Mat get_back_projct(cv::Mat &img, cv::MatND &hist);

private:
  int hist_size[1];
  int channels[2];
  float hranges[2];
  const float *ranges[1];
  cv::Mat lut;
};
cv::MatND histgram1d::get_histgram(cv::Mat img) {
  cv::MatND hist;
  cv::calcHist(&img, 1, channels, cv::Mat(), hist, 1, hist_size, ranges);
  return hist;
}

cv::Mat histgram1d::get_back_projct(cv::Mat &img, cv::MatND &hist) {
  cv::Mat result;     
  cv::normalize(hist, hist, 1.0);
  cv::calcBackProject(&img, 1, channels, hist, result, ranges, 255.0);
  return result;
}
cv::Mat histgram1d::equalize(const cv::Mat &image) {
  cv::Mat result;
  cv::equalizeHist(image, result); 
  return result;
}

cv::Mat histgram1d::get_histgram_img(const cv::Mat &img) {
  cv::MatND h = get_histgram(img);
  double max_val, min_val;
  cv::minMaxLoc(h, &min_val, &max_val, 0, 0);
  int hpt = static_cast<int>(hist_size[0] * 0.9);
  cv::Mat himg = cv::Mat(hist_size[0], hist_size[0], CV_8U, cv::Scalar(255));
  for (int i = 0; i < hist_size[0]; ++i) {
    float bin_val = h.at<float>(i);
    int intensity = static_cast<int>(bin_val * hpt / max_val);
    cv::line(himg, cv::Point(i, hist_size[0]),
             cv::Point(i, hist_size[0] - intensity), cv::Scalar::all(0));
  }
  return himg;
}
void histgram1d::init_invert_ltb(void) {
  int dim = 256;
  cv::Mat lut_(1, &dim, CV_8U);
  for (int i = 0; i < 256; ++i) {
    lut_.at<uchar>(i) = 256 - i;
  }
  lut = lut_;
}
// 1.
void histgram1d::init_strtch_ltb(cv::Mat &img, int min_val) {
  int dim = 256;
  cv::Mat lut_(1, &dim, CV_8U);
  cv::MatND h = get_histgram(img);
  int imin = 0, imax = 255;
  for (; imin < 256; ++imin) {
    std::cout << imin << std::endl;
    if (h.at<uchar>(imin) > min_val) break;    
  }

  for (; imax >= 0; --imax) {
    if (h.at<uchar>(imax) > min_val) break;    
  }
  for (int i = 0; i < dim; ++i) {
    if (i < imin)
      lut_.at<uchar>(i) = 0;
    else if (i > imax)
      lut_.at<uchar>(i) = 255;
    else
      lut_.at<uchar>(i) =
        static_cast<uchar>(255.0 * (i - imin) / (imax - imin) + 0.5);
  }
  lut = lut_;
}
cv::Mat histgram1d::apply_lut(const cv::Mat &image) {
  cv::Mat lut_img;
  cv::LUT(image, lut, lut_img);
  return lut_img;
}
// void histgram1d::init_lut (){
// }
#if defined test0
int main(int argc, char **argv) {
  cv::Mat img = cv::imread("../data/lena.jpg", 0);
  histgram1d histgram1d;
  cv::MatND hist = histgram1d.get_histgram(img);
  for (int i = 0; i < 256; ++i) {
    std::cout << hist.at<float>(i) << std::endl;
  }
  return 0;
}
#elif defined test1
int main(int argc, char **argv) {
  cv::Mat img = cv::imread("../data/lena.jpg", 0);
  histgram1d histgram1d;
  cv::Mat hist = histgram1d.get_histgram_img(img);
  cv::Mat threshold;
  cv::threshold(img, threshold, 88, 255, cv::THRESH_BINARY);
  cv::imshow("hist img", hist);
  cv::imshow("thresh img", threshold);
  cv::waitKey(0);

  return 0;
}
#elif defined test2
int main(int argc, char **argv) {
  cv::Mat img = cv::imread("../data/lena.jpg", 0);
  histgram1d histgram;
  histgram.init_invert_ltb();
  cv::Mat result = histgram.apply_lut(img);
  cv::imshow("lut image", result);
  cv::waitKey(0);

  return 0;
}
#elif defined test3
int main(int argc, char **argv) {
  cv::Mat img = cv::imread("../data/lena.jpg", 0);
  histgram1d histgram;
  histgram.init_strtch_ltb(img, 10);
  cv::Mat result = histgram.apply_lut(img);
  cv::imshow("lut image", result);
  cv::waitKey(0);

  return 0;
}
#elif defined test4
int main(int argc, char **argv) {
  cv::Mat img = cv::imread("../data/lena.jpg", 0);
  histgram1d histgram;
  cv::Mat result = histgram.equalize(img);
  cv::imshow("equalize image", result);
  cv::waitKey(0);
  return 0;
}
#elif defined test
int main(int argc, char **argv) {
  cv::Mat img = cv::imread("../data/lena.jpg", 0);
  histgram1d histgram;
  cv::Mat roi_img = img(cv::Rect(0, 0, 50, 50));
  cv::MatND hist = histgram.get_histgram(roi_img);
  cv::Mat result = histgram.get_back_projct(img, hist);
  cv::threshold(result, result, 18, 255, cv::THRESH_BINARY);

  cv::imshow("backproject image", result);
  cv::waitKey(0);
  return 0;
}
#endif
