/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-08-27 10:27
 * Last modified : 2020-08-27 10:27
 * Filename      : morphology.cpp
 * Description   :
 *********************************************************************/
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
#define test
#if defined test1

int main(int argc, char **argv) {
  cv::Mat img = cv::imread("../data/lena.jpg", 0);
  cv::imshow("orig img", img);
  cv::Mat erode;
  cv::erode(img, erode, cv::Mat(), cv::Point(-1, -1), 8);
  cv::dilate(img, erode, cv::Mat(), cv::Point(-1, -1), 8);
  cv::imshow("erode img", erode);
  cv::waitKey(0);

  return 0;
}
#elif defined test1
int main(int argc, char **argv) {
  cv::Mat img = cv::imread("../data/ela_modified.jpg", 0);
  cv::threshold(img, img, 88, 255, cv::THRESH_BINARY);
  cv::imshow("orig img", img);
  cv::Mat result;
  cv::Mat element5(7, 7, CV_8U, cv::Scalar(1));
  cv::morphologyEx(img, result, cv::MORPH_CLOSE, element5);
  // cv::morphologyEx(result, result, cv::MORPH_OP, element5);
  cv::imshow("resut", result);
  cv::waitKey(0);
  return 0;
}
#elif defined tes3
class MorphFeature {
public:
  MorphFeature(int thresh_val = -1);
  cv::Mat get_eadge(cv::Mat &img);
  cv::Mat get_corner(cv::Mat &img);
  cv::Mat applay_threshold(cv::Mat &img);
  void set_threshold(int thresh_val);
  void draw_on_img(cv::Mat &img, cv::Mat &corner);

private:
  int threshold;
  cv::Mat cross;
  cv::Mat diamond;
  cv::Mat square;
  cv::Mat x;
};

MorphFeature::MorphFeature(int thresh_val)
    : threshold(thresh_val), cross(5, 5, CV_8U, cv::Scalar(0)),
      diamond(5, 5, CV_8U, cv::Scalar(1)), square(5, 5, CV_8U, cv::Scalar(1)),
      x(5, 5, CV_8U, cv::Scalar(0)) {
  for (int i = 0; i < 5; ++i) {
    cross.at<uchar>(i, 2) = 1;
    cross.at<uchar>(2, i) = 1;
  }
  diamond.at<uchar>(0, 0) = 0;
  diamond.at<uchar>(0, 1) = 0;
  diamond.at<uchar>(0, 3) = 0;
  diamond.at<uchar>(0, 4) = 0;

  diamond.at<uchar>(1, 4) = 0;
  diamond.at<uchar>(3, 4) = 0;
  diamond.at<uchar>(4, 4) = 0;

  diamond.at<uchar>(4, 3) = 0;
  diamond.at<uchar>(4, 1) = 0;
  diamond.at<uchar>(4, 0) = 0;

  diamond.at<uchar>(3, 0) = 0;
  diamond.at<uchar>(1, 0) = 0;

  for (int i = 0; i < 5; ++i) {
    x.at<uchar>(i, i);
    x.at<uchar>(4 - i, i);
  }
}

cv::Mat MorphFeature::get_corner(cv::Mat &img) {
  cv::Mat result;
  cv::dilate(img, result, diamond);
  cv::erode(result, result, cross);

  cv::Mat result2;
  cv::dilate(img, result2, x);
  cv::erode(result2, result2, square);

  cv::absdiff(result2, result, result);
  applay_threshold(result);

  return result;
}

void MorphFeature::draw_on_img(cv::Mat &img, cv::Mat &corner) {
  cv::Mat_<uchar>::const_iterator it_beg = corner.begin<uchar>();
  cv::Mat_<uchar>::const_iterator it_end = corner.end<uchar>();
  for (int i = 0; it_beg != it_end; ++i, ++it_beg) {
    if (!*it_beg) {
      cv::circle(img, cv::Point(i % img.step, i / img.step), 5,
                 cv::Scalar(255, 0, 0));
    }
  }
}
cv::Mat MorphFeature::get_eadge(cv::Mat &img) {
  cv::morphologyEx(img, img, cv::MORPH_GRADIENT, cv::Mat());
  applay_threshold(img);
  return img;
}

void MorphFeature::set_threshold(int thresh_val) { threshold = thresh_val; }
cv::Mat MorphFeature::applay_threshold(cv::Mat &img) {
  cv::threshold(img, img, threshold, 255, cv::THRESH_BINARY);
  return img;
}

int main(int argc, char **argv) {

  cv::Mat img = cv::imread("../data/aero3.jpg", 0);
  std::cout << img.step << std::endl;
  MorphFeature mf;
  mf.set_threshold(8);
  cv::Mat corner = mf.get_corner(img);
  mf.draw_on_img(img, corner);
  cv::imshow("corner img", img);
  cv::waitKey(0);
  return 0;
}
#elif defined test
class WatershedSegmenter {
  private:
    cv::Mat marker;
  public:
  void set_marker(const cv::Mat &img) {
      img.convertTo(marker, CV_32S); 
  }
  cv::Mat process(cv::Mat &img)  {
    cv::watershed(img, marker);
    return marker;
  }
};

int main(int argc, char **argv) {
  cv::Mat img = cv::imread("../data/detect_blob.png", 1);

  // cv::Mat result;
  // cv::threshold(img, result, 88, 255, cv::THRESH_BINARY);
  WatershedSegmenter ws;
  ws.set_marker(img);
  ws.process(img);
  cv::imshow("corner img", img);
  cv::waitKey(0);
  return 0;
}
#endif
