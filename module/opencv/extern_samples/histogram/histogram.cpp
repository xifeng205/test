/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-06-02 09:46
 * Last modified : 2020-06-02 09:46
 * Filename      : histogram.cpp
 * Description   :
 *********************************************************************/

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;

class Histogram1D {
private:
  int hist_size[1];
  float hranges[2];
  const float *ranges[1];
  int channels[1];

protected:
public:
  Histogram1D() {
    hist_size[0] = 256;
    hranges[0] = 0.0;
    hranges[1] = 255.0;
    ranges[0] = hranges;
    channels[0] = 0;
  }

  cv::MatND get_histogram(cv::Mat &image) {
    cv::MatND hist;
    cv::calcHist(&image, 1, channels, cv::Mat(), hist, 1, hist_size, ranges);
    return hist;
  }

  cv::Mat get_histogram_image(cv::Mat &image) {
    cv::MatND hist = get_histogram(image);

    double max_val = 0;
    double min_val = 0;
    cv::minMaxLoc(hist, &min_val, &max_val, 0, 0);
    cv::Mat hist_img(hist_size[0], hist_size[0], CV_8U, cv::Scalar(255));

    int hpt = static_cast<int>(.9 * hist_size[0]);

    for (int i = 0; i < hist_size[0]; ++i) {
      float bin_val = hist.at<float>(i);
      int instensity = static_cast<int>(bin_val * hpt / max_val);
      cv::line(hist_img, cv::Point(i, hist_size[0]),
               cv::Point(i, hist_size[0] - instensity), cv::Scalar::all(0));
    }
    return hist_img;
  }

  cv::Mat equalize(const cv::Mat &image) {
    cv::Mat result;
    cv::equalizeHist(image, result);
    return result;
  }
};

int main(int argc, char **argv) {
  cv::Mat image = cv::imread("../../../data/butterfly.jpg", 0);
  Histogram1D histogram1d;

  cv::MatND hist_ret = histogram1d.get_histogram(image);

  // for (int i=0; i<256; ++i) {
  // cout << "output:" << hist_ret.at<float>(i) <<endl;
  // }

  cv::imshow("gray image", image);
  cv::imshow("histgray image", histogram1d.get_histogram_image(image));
  cv::Mat equalize_out = histogram1d.equalize(image);
  cv::imshow("equlize image", equalize_out);
  cv::imshow("equhistgray image",
             histogram1d.get_histogram_image(equalize_out));
  // cv::Mat thresholded;
  // cv::threshold(image, thresholded, 40, 255, cv::THRESH_BINARY);
  // cv::imshow("threshold image", thresholded);

  // int dim[256];
  // cv::Mat lut(1, dim, CV_8U);

  // for (int i=0; i<256; ++i) {
  // image.at<uchar>(i) = 255 - i;
  // }
  // cv::imshow("threshold image", image);
  //
  cv::waitKey(0);

  return 0;
}
