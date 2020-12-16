/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-08-26 10:57
 * Last modified : 2020-08-26 10:57
 * Filename      : calcHist3d.cpp
 * Description   :
 *********************************************************************/

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/video/video.hpp>
#include <opencv2/imgproc/types_c.h>
#include <vector>
//1 coloarReduce
//2 calcHist
//3 normalize
//4 calcBackProject;
//5 threshold

using namespace std;
class histgram {
public:
  histgram();
  cv::MatND get_histgram(cv::Mat &img);
  cv::MatND get_histgram_img(cv::Mat &img);
  cv::MatND get_hue_histgram(cv::Mat &img, int min_saturation);

private:
  int hist_size[3];
  int channels[3];
  float hrange[2];
  const float *ranges[3];
};

histgram::histgram() {
  hist_size[0] = 256;
  hist_size[1] = 256;
  hist_size[2] = 256;
  channels[0] = 0;
  channels[1] = 1;
  channels[2] = 2;
  hrange[0] = 0.0;
  hrange[1] = 255.0;
  ranges[0] = hrange;
  ranges[1] = hrange;
  ranges[2] = hrange;
}

cv::MatND histgram::get_hue_histgram(cv::Mat &img, int min_saturation) {
  cv::MatND hist; 
  cv::cvtColor(img, img, CV_BGR2HSV);
  cv::Mat mask;

  std::vector<cv::Mat> split_img;
  if (min_saturation > 0) {
    cv::split(img, split_img);
    cv::threshold(split_img[1], mask, min_saturation, 255, cv::THRESH_BINARY);
  }
  hrange[0] = 0.0;
  hrange[1] = 180.0;
  cv::calcHist(&split_img[0], 1, &channels[0], mask, hist, 1, hist_size, ranges);
  return hist;
}

cv::MatND histgram::get_histgram(cv::Mat &img) {
  cv::MatND hist;
  cv::calcHist(&img, 1, channels, cv::Mat(), hist, 3, hist_size, ranges);
  return hist;
}
class ContentFinder {
  public:

    ContentFinder() : threshold(-0.01f) {
      ranges[0] = hrange;
      ranges[1] = hrange;
      ranges[2] = hrange;
    hrange[0] = 0.0;
    hrange[1] = 255.0; channels[0] = 0; 
    channels[1] = 1; channels[2] = 2; } 
    void set_threshold(float t) { threshold = t; }
  float get_threshold(void) { return threshold; }
  cv::Mat find(cv::Mat &img, cv::MatND hist);

private:
  float hrange[2];
  const float *ranges[3];
  int channels[3];
  float threshold;
  cv::Mat histgram;
};

cv::Mat ContentFinder::find(cv::Mat &img, cv::MatND hist) {
  cv::Mat result;
  cv::calcBackProject(&img, 1, channels, hist, result, ranges, 255.0);
  cv::threshold(result, result, threshold, 255.0, cv::THRESH_BINARY);
  return result;
}
class ColorReduce {
  public:
    cv::Mat color_reduce(cv::Mat &img, int div) {
      cv::Mat_<cv::Vec3b>::iterator it_beg = img.begin<cv::Vec3b>(); 
      cv::Mat_<cv::Vec3b>::iterator it_end = img.end<cv::Vec3b>(); 

      for (; it_beg != it_end; ++it_beg) {
        (*it_beg)[0] = (*it_beg)[0] / div * div + div / 2;
        (*it_beg)[1] = (*it_beg)[1] / div * div + div / 2;
        (*it_beg)[2] = (*it_beg)[2] / div * div + div / 2;
      }
      return img;
    }

  private:

};
int main(int argc, char **argv) {
  cv::Mat img = cv::imread("../data/lena.jpg", 1);

  ColorReduce cr;
  cr.color_reduce(img, 32);

  histgram hg;
  cv::Mat roi_img = img(cv::Rect(69, 117, 88, 88));
  cv::MatND hist = hg.get_hue_histgram(roi_img, 60);
  cv::normalize(hist, hist, 1.0);

  ContentFinder cf;
  cf.set_threshold(10);

  cv::Mat img1 = cv::imread("../data/left.jpg", 1);
  cr.color_reduce(img1, 32);
  cv::cvtColor(img1, img1, CV_BGR2HSV);
  cv::imshow("2", img1);
  std::vector<cv::Mat> split_img1;
  cv::split(img1, split_img1);
  cv::Mat result = cf.find(img1, hist);
  cv::imshow("3", result);
  cv::threshold(split_img1[1], split_img1[1], 60, 255, cv::THRESH_BINARY);
  cv::bitwise_and(result, split_img1[1], result);

  cv::Rect rect(69, 117, 88, 88);
  cv::rectangle(result, rect,cv::Scalar(255, 255, 255));
  cv::TermCriteria termcriteria(cv::TermCriteria::MAX_ITER, 10, 0.01);
  cv::meanShift(result, rect, termcriteria);

  cv::imshow("backproject img", result);
  cv::waitKey(0);

  return 0;
}
