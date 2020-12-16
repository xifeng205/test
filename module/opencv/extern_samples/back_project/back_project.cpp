
/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-06-02 09:46
 * Last modified : 2020-06-02 09:46
 * Filename      : histogram.cpp
 * Description   :
 *********************************************************************/

#include <algorithm>
#include <iostream>
#include <iterator>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;

class Contentfinder {
private:
  float hranges[2];
  const float *ranges[3];
  int channels[3];
  float threshold;
  cv::MatND histogram;

protected:
public:
  Contentfinder() : threshold(-1.0f) {
    ranges[0] = hranges;
    ranges[1] = hranges;
    ranges[2] = hranges;
  }

  void set_threshold(float t) { threshold = t; }
  float get_threshold() { return threshold; }
  void set_histogram(cv::MatND &h) {
    histogram = h;
    cv::normalize(histogram, histogram, 1.0);
  }

  cv::Mat content_find(cv::Mat &image, float min_val, float max_val,
                       int *channels, int dim) {
    cv::Mat result;
    hranges[0] = min_val;
    hranges[1] = max_val;

    for (int i = 0; i < dim; ++i) {
      this->channels[i] = channels[i];
    }
    cv::calcBackProject(&image, 1, channels, histogram, result, ranges, 255.0);
    if (threshold > 0.0) {
      cv::threshold(result, result, 255 * threshold, 255, cv::THRESH_BINARY);
    }
    return result;
  }

  cv::Mat equalize(const cv::Mat &image) {
    cv::Mat result;
    cv::equalizeHist(image, result);
    return result;
  }
};

class Colorhistogram {
private:
  int hist_size[3];
  float hranges[2];
  const float *ranges[3];
  int channels[3];

protected:
public:
  Colorhistogram() {
    hist_size[0] = hist_size[1] = hist_size[2] = 256;
    hranges[0] = 0.0;
    hranges[1] = 255.0;
    ranges[0] = hranges;
    ranges[1] = hranges;
    ranges[2] = hranges;
    channels[0] = 0;
    channels[1] = 1;
    channels[2] = 2;
  }
  cv::MatND get_histogram(const cv::Mat &image) {
    cv::MatND hist;
    cv::calcHist(&image, 1, channels, cv::Mat(), hist, 3, hist_size, ranges);
    return hist;
  }
  void color_reduce(cv::Mat &img, int div) {
    int nl = img.rows;
    int nc = img.cols * img.channels();

    for (int j = 0; j < nl; ++j) {
      uchar *data = img.ptr<uchar>(j);
      for (int i = 0; i < nc; ++i) {
        data[i] = data[i] - data[i] % div + div / 2;
      }
    }
  }
};

int main(int argc, char **argv) {
  Colorhistogram hc;
  cv::Mat image = cv::imread("../../../data/home.jpg");

  hc.color_reduce(image, 32);
  cv::Mat img_roi = image(cv::Rect(0, 0, 165, 75));
  cv::MatND hist = hc.get_histogram(img_roi);

  Contentfinder finder;
  finder.set_histogram(hist);
  finder.set_threshold(0.05f);
  int channels[3];
  channels[0] = 0;
  channels[1] = 1;
  channels[2] = 2;

  cv::Mat result = finder.content_find(image, 0.0, 255.0, channels, 3);

  cv::imshow("image", result);
  cv::waitKey(0);

  return 0;
}
