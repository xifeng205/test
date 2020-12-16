/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-06-06 15:58
 * Last modified : 2020-06-06 15:58
 * Filename      : video_read.cpp
 * Description   :
 *********************************************************************/

#include <cstring>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <locale>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgproc/types_c.h>
#include <opencv2/video/tracking.hpp>
#include <opencv2/videoio/legacy/constants_c.h>
#include <opencv2/videoio/videoio.hpp>
#include <type_traits>

using namespace std;
class Frameprocessor {
public:
  virtual void process(cv::Mat &input, cv::Mat &outpuy) = 0;
};
class Videoprocessor {
private:
  Frameprocessor *frameprocess;
  cv::VideoCapture capture;
  void (*process)(cv::Mat &, cv::Mat &);
  bool call_it;
  std::string window_name_input;
  std::string window_name_output;
  std::vector<std::string> images;
  std::vector<std::string>::const_iterator it_img;
  int delay;
  long fnumber;
  long frame_to_stop;
  bool stop;
  bool is_video_write;
  cv::VideoWriter writer;
  std::string output_file;
  int current_index;
  int digits;
  std::string extension;

public:
  Videoprocessor()
      : call_it(true), delay(0), fnumber(0), stop(false), frame_to_stop(-1),
        is_video_write(false) {}
  void set_frame_processor(void (*frame_processing)(cv::Mat &, cv::Mat &)) {
    frameprocess = NULL;
    process = frame_processing;
    call_process();
  }
  void set_frame_processor(Frameprocessor *callback_process) {
    process = NULL;
    frameprocess = callback_process;
    call_process();
  }
  bool set_input(std::string file_name) {
    fnumber = 0;
    capture.release();
    images.clear();
    return capture.open(file_name);
  }
  void display_input(std::string wn) {
    window_name_input = wn;
    cv::namedWindow(window_name_input);
  }
  void display_output(std::string wn) {
    window_name_output = wn;
    cv::namedWindow(wn);
  }
  void dont_display() {
    cv::destroyWindow(window_name_input);
    cv::destroyWindow(window_name_output);
    window_name_input.clear();
    window_name_output.clear();
  }
  void run() {
    cv::Mat frame;
    cv::Mat output;
    if (!is_opened())
      return;
    stop = false;
    while (!is_stopped()) {
      if (!read_next_frame(frame))
        break;

      if (window_name_input.length() != 0) {
        if (frame.data)
          QImage img = QImage((const unsigned char *)(frame.data), frame.cols,
                              frame.rows, QImage::Format_RGB888);
        ui->label->setPixmap(QPixmap::fromImage(img));
        ui->label->resize(ui->label->pixmap()->size());
        // cv::imshow(window_name_input, frame);
      }

      if (call_it) {
        if (frameprocess)
          frameprocess->process(frame, output);
        else if (process)
          process(frame, output);
        fnumber++;
      } else
        output = frame;
      if (output_file.length() != 0 && is_video_write) {
        write_next_frame(output);
      }

      if (window_name_output.length() != 0) {
        QImage img = QImage((const unsigned char *)(output.data), output.cols,
                            output.rows, QImage::Format_RGB888);
        ui->label_2->setPixmap(QPixmap::fromImage(img));
        ui->label_2->resize(ui->label_2->pixmap()->size());

        // cv::imshow(window_name_output, output);
      }
      if (delay >= 0 && cv::waitKey(delay) >= 0)
        stop_it();
      if (frame_to_stop >= 0 && get_frame_number() == frame_to_stop)
        stop_it();
    }
  }
  void stop_it() { stop = true; }
  bool is_stopped() { return stop; }
  bool is_opened() { return capture.isOpened() || !images.empty(); }
  void set_delay(int d) { delay = d; }
  bool read_next_frame(cv::Mat &frame) {
    if (images.size() == 0) {
      return capture.read(frame);
    } else {
      if (it_img != images.end()) {
        frame = cv::imread(*it_img);
        it_img++;
        return frame.data != 0;
      } else {
        return false;
      }
    }
  }
  void call_process() { call_it = true; }
  void dont_call_process() { call_it = false; }
  long get_frame_number() {
    long frame_number = static_cast<long>(capture.get(CV_CAP_PROP_POS_FRAMES));
    return frame_number;
  }
  long get_frame_rate() { return capture.get(CV_CAP_PROP_FPS); }
  cv::Size get_frame_size() {
    cv::Size sz(capture.get(CV_CAP_PROP_FRAME_WIDTH),
                capture.get(CV_CAP_PROP_FRAME_HEIGHT));
    return sz;
  }
  void stop_at_frame_no(long frame) { frame_to_stop = frame; }
  bool set_input(const std::vector<std::string> &imgs) {
    fnumber = 0;
    capture.release();
    images = imgs;
    it_img = images.begin();
    return true;
  }
  bool set_output(const std::string &file_name, int codec = 0,
                  double frame_rate = 0.0, bool is_color = true) {
    output_file = file_name;
    extension.clear();
    if (frame_rate == 0.0)
      frame_rate = get_frame_rate();
    char c[4];
    if (codec == 0) {
      codec = get_codec(c);
    }
    return writer.open(output_file, codec, frame_rate, get_frame_size(),
                       is_color);
  }
  bool set_output(const std::string &file_name, const std::string &ext,
                  int num_of_digits = 3, int start_index = 0) {
    if (num_of_digits < 0)
      return false;

    output_file = file_name;
    extension = ext;
    digits = num_of_digits;
    current_index = start_index;

    return true;
  }
  void write_next_frame(cv::Mat &frame) {
    if (extension.length()) {
      std::stringstream ss;
      ss << output_file << std::setfill('0') << std::setw(digits)
         << current_index++ << extension;
      cv::imwrite(ss.str(), frame);
    } else {
      writer.write(frame);
    }
  }
  int get_codec(char codec[4]) {
    if (images.size() != 0)
      return -1;
    union {
      int value;
      char code[4];
    } returned;
    returned.value = static_cast<int>(capture.get(CV_CAP_PROP_FOURCC));
    codec[0] = returned.code[0];
    codec[1] = returned.code[1];
    codec[2] = returned.code[2];
    codec[3] = returned.code[3];
    return returned.value;
  }
  void video_write(bool write) { is_video_write = write; }
};

class Featuretracker : public Frameprocessor {
private:
  cv::Mat gray;
  cv::Mat gray_prev;
  std::vector<cv::Point2f> points[2];
  std::vector<cv::Point2f> initial;
  std::vector<cv::Point2f> features;
  int max_count;
  double qlevel;
  double mini_dist;
  std::vector<uchar> status;
  std::vector<float> err;

public:
  Featuretracker() : max_count(500), qlevel(0.01), mini_dist(10.) {}

  void process(cv::Mat &frame, cv::Mat &output) {
    cv::cvtColor(frame, gray, CV_BGR2GRAY);
    frame.copyTo(output);
    if (add_new_point()) {
      detect_feature_points();
      points[0].insert(points[0].end(), features.begin(), features.end());
      initial.insert(initial.end(), features.begin(), features.end());
    }
    if (gray_prev.empty())
      gray.copyTo(gray_prev);
    cv::calcOpticalFlowPyrLK(gray_prev, gray, points[0], points[1], status,
                             err);
    int k = 0;
    for (int i = 0; i < points[1].size(); ++i) {
      if (accept_tracked_point(i)) {
        initial[k] = initial[i];
        points[1][k++] = points[1][i];
      }
    }

    points[1].resize(k);
    initial.resize(k);
    handle_tracked_points(frame, output);
    std::swap(points[1], points[0]);
    std::swap(gray_prev, gray);
  }
  bool add_new_point() { return points[0].size() <= 10; }
  void detect_feature_points() {
    cv::goodFeaturesToTrack(gray, features, max_count, qlevel, mini_dist);
  }
  bool accept_tracked_point(int i) {
    return status[i] && ((abs(points[0][i].x - points[1][i].x)) +
                             (abs(points[0][i].y - points[1][i].y)) >
                         2);
  }
  void handle_tracked_points(cv::Mat &frame, cv::Mat &output) {
    for (int i = 0; i < points[1].size(); ++i) {
      cv::line(output, initial[i], points[1][i], cv::Scalar(255, 255, 255));
      cv::circle(output, points[1][i], 3, cv::Scalar(255, 255, 255), -1);
    }
  }
};
void canny(cv::Mat &img, cv::Mat &out) {
  if (img.channels() == 3)
    cv::cvtColor(img, out, CV_BGR2GRAY);
  cv::Canny(out, out, 100, 200);
  cv::threshold(out, out, 128, 255, cv::THRESH_BINARY_INV);
}

class BGFGsegmentor : public Frameprocessor {
private:
  cv::Mat gray;
  cv::Mat background;
  cv::Mat back_image;
  cv::Mat foreground;
  double learning_rate;
  int threshold;

public:
  BGFGsegmentor() : threshold(10), learning_rate(0.01) {}

  void process(cv::Mat &frame, cv::Mat &output) {
    cv::cvtColor(frame, gray, CV_BGR2GRAY);
    if (background.empty())
      gray.convertTo(background, CV_32F);
    background.convertTo(back_image, CV_8U);
    cv::absdiff(back_image, gray, foreground);
    cv::threshold(foreground, output, threshold, 255, cv::THRESH_BINARY);
    cv::accumulateWeighted(gray, background, learning_rate, output);
  }
};
int main(int argc, char **argv) {
  Featuretracker featuretracker;
  Videoprocessor videoprocessor;
  BGFGsegmentor segmentor;
  videoprocessor.set_input("/dev/video0");
  videoprocessor.set_output("/home/cuiyunpeng/tools/opencv/samples/cpp/"
                            "extern_samples/video_processor/test.avi");

  videoprocessor.display_input("orgin frame");
  videoprocessor.display_output("output_frame");

  videoprocessor.set_delay(1000. / videoprocessor.get_frame_rate());
  // videoprocessor.set_frame_processor(&featuretracker);
  videoprocessor.set_frame_processor(&segmentor);

  videoprocessor.run();

  return 0;
}
