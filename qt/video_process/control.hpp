/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-06-01 11:23
 * Last modified : 2020-06-01 11:23
 * Filename      : designer.cpp
 * Description   :
 *********************************************************************/
#include "color_detect.hpp"
#include "object_trace.hpp"

class Guictrl {
public:
  static Guictrl *get_instance() {
    if (!singleton) {
      singleton = new Guictrl();
    }
    return singleton;
  }

  void destory() {
    if (singleton) {
      delete singleton;
      singleton = NULL;
    }
  }

  void set_color_distance_threshold(int distance) {
    cdetect->set_color_distance_threshold(distance);
  }

  int get_color_distance_threshold() const {
    // return cdetect->get_color_distance_threshold();
    return 1;
  }

  void set_target_color(unsigned char red, unsigned char green,
                        unsigned char blue) {
    cdetect->set_target_color(red, green, blue);
  }

  void get_target_color(unsigned char &red, unsigned char &green,
                        unsigned char &blue) {
    cv::Vec3b color = cdetect->get_target_color();
    red = color[2];
    green = color[1];
    blue = color[0];
  }

  bool set_input_image(std::string filename) {
    image = cv::imread(filename);
    if (!image.data)
      return false;
    else
      return true;
  }

  cv::Mat get_input_image() { return image; }

  void process() { result = cdetect->process(image); }

  const cv::Mat get_last_result() const { return result; }

  // video process
  void vp_set_input() { videoprocessor->set_input("/dev/video0"); }
  void vp_set_output() {
    videoprocessor->set_output("/home/cuiyunpeng/tools/opencv/ \
                   samples/cpp/extern_samples/video_processor/test.avi");
  }
  void vp_display_input() { videoprocessor->display_input("orgin frame"); }
  void vp_display_output() { videoprocessor->display_output("process frame"); }
  void vp_set_processor() {
    videoprocessor->set_frame_processor(featuretracker);
  }
  void vp_set_delay() {
    videoprocessor->set_delay(1000. / videoprocessor->get_frame_rate());
  }
  void vp_run() { videoprocessor->run(); }
  void vp_stop() { videoprocessor->stop_it(); }
  void vp_get_frame(cv::Mat &frame, cv::Mat &output) {
    videoprocessor->get_frame(frame, output);
  }
  ~Guictrl() {
    delete cdetect;
    delete videoprocessor;
    // delete featuretracker;
    // delete segmentor;
  }

protected:
private:
  static Guictrl *singleton;

  Color_detector *cdetect;
  Videoprocessor *videoprocessor;
  Featuretracker *featuretracker;
  BGFGsegmentor *segmentor;

  Guictrl() {
    cdetect = new Color_detector();
    videoprocessor = new Videoprocessor();
    featuretracker = new Featuretracker();
    segmentor = new BGFGsegmentor();
  }
  cv::Mat image;
  cv::Mat result;
};

Guictrl *Guictrl::singleton = NULL;
