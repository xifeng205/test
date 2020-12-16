/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-12-14 12:15
 * Last modified : 2020-12-14 12:15
 * Filename      : color_detecotr.cpp
 * Description   :
 *********************************************************************/

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace std;

// color detector
// strategy  mode
class ProcessMethod {
public:
  virtual void process(cv::Mat &img, cv::Mat &result) = 0;
};

class ColorDetector:public ProcessMethod {
public:
  ColorDetector();
  ProcessMethod *method;
  void set_method(ProcessMethod *method) {}

  void cv_process(cv::Mat &img, cv::Mat &result){
				method->process(img, result);
  };
};

// control mode
class ColorControl {
public:
  static ColorDetector *cd;

public:
  void set_detector_color(float r, float g, float b){

  };

  static ColorDetector *get_instance() {
    if (!cd) {
      cd = new ColorDetector();
    }
    return cd;
  }

  static void destory() {
    if (cd) {
      delete cd;
    }
  }

private:
  ColorControl() { cd = new ColorDetector(); }
};

int main(int argc, char **argv) { 

return 0; }
