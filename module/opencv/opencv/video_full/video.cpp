/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-12-14 16:18
 * Last modified : 2020-12-14 16:18
 * Filename      : video.cpp
 * Description   :
 *********************************************************************/

#include <iomanip>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/video/video.hpp>
#include <opencv2/videoio/legacy/constants_c.h>
#include <vector>

using namespace std;
void canny(cv::Mat &src, cv::Mat &dst) {
  if (src.channels() == 3) {
    cv::cvtColor(src, dst, cv::COLOR_BGR2GRAY);
  }
  cv::Canny(dst, dst, 80, 120);
  cv::threshold(dst, dst, 180, 255, cv::THRESH_BINARY);
}

class FrameProcessor {
public:
  virtual void process(cv::Mat &src, cv::Mat &dst) = 0;
};

class VideoProcessor {
private:
  cv::VideoWriter writer;
  std::string outputName;
  std::string extension;
  int digits;
  int currentIndex;

  cv::VideoCapture capture;
  bool stop;
  long delay;
  std::string winInputName;
  std::string winOutputName;
  void (*process)(cv::Mat &src, cv::Mat &dst);
  bool ifCallProcess;
  long frameToStop;
  std::vector<std::string> images;
  std::vector<std::string>::const_iterator img_iter;

public:
  VideoProcessor()
      : stop(false), ifCallProcess(false), frameToStop(-1), delay(0){};
  FrameProcessor *fp;
  // ~VideoProcessor();
  bool setInput(std::string fileName);
  bool setInput(std::vector<std::string> &img);
  void setWindowInputName(std::string inputname);
  void setWindowOutputName(std::string outputname);
  void dontDisplay();
  void setFrameProcess(void (*process)(cv::Mat &src, cv::Mat &dst));
  void setFrameProcess(FrameProcessor *processor);
  long getFrameRate();
  void setDelay(long d);
  void run();
  bool isCallProcess();
  bool isStopped();
  void stopIt();
  bool isOpened();
  void callProcess(bool cp);
  bool getNextFrame(cv::Mat &frame);

  long getFrameNum();
  void setFrameToStop(long n);
  // writer interface
  bool setOutput(std::string outputName, int codec, double frameRate,
                 bool isColor);
  bool setOutput(std::string outputName, std::string extension, int index,
                 int dt);
  void writeNextFrame(cv::Mat &frame);
  cv::Size getFrameSize();
  int getCodec(char codec[4]);
};

cv::Size VideoProcessor::getFrameSize() {
  cv::Size sz(capture.get(CV_CAP_PROP_FRAME_WIDTH),
              capture.get(CV_CAP_PROP_FRAME_HEIGHT));
  return sz;
}

int VideoProcessor::getCodec(char codec[4]) {
  if (images.size() != 0)
    return -1;
  union {
    char code[4];
    int value;
  } returned;
  returned.value = static_cast<int>(capture.get(cv::CAP_PROP_FOURCC));
  codec[0] = returned.code[0];
  codec[1] = returned.code[1];
  codec[2] = returned.code[2];
  codec[3] = returned.code[3];
  return returned.value;
}

bool VideoProcessor::setOutput(std::string output_name, int codec = 0,
                               double frameRate = 0.0, bool isColor = true) {
  outputName = output_name;
  extension.clear();
  char c[4];
  if (!codec)
    codec = getCodec(c);
  if (frameRate == 0.0)
    frameRate = getFrameRate();
  return writer.open(outputName, codec, frameRate, getFrameSize(), isColor);
}
bool VideoProcessor::setOutput(std::string output_name, std::string ext,
                               int numDitigs = 3, int startIndex = 0) {
  if (!numDitigs)
    return false;
  outputName = output_name;
  extension = ext;
  digits = numDitigs;
  currentIndex = startIndex;
  return true;
}

void VideoProcessor::writeNextFrame(cv::Mat &frame) {
  if (extension.length()) {
    std::stringstream ss;
    ss << outputName << std::setfill('0') << std::setw(digits) << currentIndex++
       << extension;
    cv::imwrite(ss.str(), frame);
  } else {
    writer.write(frame);
  }
}

bool VideoProcessor::setInput(std::string fileName) {
  capture.release();
  return capture.open(fileName);
}
bool VideoProcessor::setInput(std::vector<std::string> &img) {
  capture.release();
  images = img;
  img_iter = img.begin();
  return true;
}

void VideoProcessor::setWindowInputName(std::string inputname) {
  winInputName = inputname;
  cv::namedWindow(winInputName);
}
void VideoProcessor::setWindowOutputName(std::string outputname) {
  winOutputName = outputname;
  cv::namedWindow(winOutputName);
}
void VideoProcessor::dontDisplay() {
  cv::destroyWindow(winInputName);
  cv::destroyWindow(winOutputName);
  winInputName.clear();
  winOutputName.clear();
}
void VideoProcessor::setFrameProcess(void (*callBackProcess)(cv::Mat &src,
                                                             cv::Mat &dst)) {
  process = callBackProcess;
  fp = nullptr;
  callProcess(true);
}
void VideoProcessor::setFrameProcess(FrameProcessor *processor) {
  process = nullptr;
  fp = processor;
  callProcess(true);
}
void VideoProcessor::setDelay(long d) { delay = d; }
bool VideoProcessor::isOpened() { return capture.isOpened(); }
bool VideoProcessor::getNextFrame(cv::Mat &frame) {
  if (images.size() == 0) {
    return capture.read(frame);
  } else {
    if (img_iter != images.end()) {
      frame = cv::imread(*img_iter);
      return frame.data != 0;
    }
    return false;
  }
}
void VideoProcessor::callProcess(bool cp) { ifCallProcess = cp; }
long VideoProcessor::getFrameNum() {
  return static_cast<long>(capture.get(cv::CAP_PROP_POS_FRAMES));
}

void VideoProcessor::setFrameToStop(long n) { frameToStop = n; }
bool VideoProcessor::isStopped() { return stop; }
void VideoProcessor::run() {
  cv::Mat frame;
  cv::Mat output;
  if (!isOpened()) {
    std::cout << "Video not opened" << std::endl;
    return;
  }
  while (!isStopped()) {
    if (!getNextFrame(frame))
      break;
    if (winInputName.length())
      cv::imshow(winInputName, frame);
    if (ifCallProcess) {
      if (process)
        process(frame, output);
      else
        fp->process(frame, output);
    } else {
      output = frame;
    }
    if (outputName.length())
      writeNextFrame(output);
    if (winOutputName.length())
      cv::imshow(winOutputName, output);
    if (cv::waitKey(1) > 0) {
      stopIt();
    }
    if (frameToStop > 0 && getFrameNum() == frameToStop)
      stopIt();
  }
}
long VideoProcessor::getFrameRate() {
  return static_cast<long>(capture.get(cv::CAP_PROP_FPS));
}
void VideoProcessor::stopIt() { stop = true; }
class canny_detector : public FrameProcessor {
public:
  void process(cv::Mat &src, cv::Mat &dst) {
    if (src.channels() == 3) {
      cv::cvtColor(src, dst, cv::COLOR_BGR2GRAY);
    }
    cv::Canny(dst, dst, 120, 200);
    cv::threshold(dst, dst, 180, 255, cv::THRESH_BINARY);
  }
};
class Featuretracker:public FrameProcessor {
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
        Featuretracker():max_count(500), qlevel(0.01), mini_dist(10.) {}

        void process(cv::Mat &frame, cv::Mat &output) {
            cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY); 
            frame.copyTo(output);
            if (add_new_point()) {
                detect_feature_points();
                points[0].insert(points[0].end(),
                        features.begin(), features.end());
                initial.insert(initial.end(),
                        features.begin(), features.end());
            } 
            if (gray_prev.empty()) gray.copyTo(gray_prev);
            cv::calcOpticalFlowPyrLK(gray_prev, gray, points[0], 
                    points[1], status, err);
            int k = 0;
            for (int i = 0; i<points[1].size(); ++i) {
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
        bool add_new_point() {
            return points[0].size() <= 10;
        }
        void detect_feature_points() {
            cv::goodFeaturesToTrack(gray, features, max_count, 
                    qlevel, mini_dist); 
        }
        bool accept_tracked_point(int i) {
           return status[i] && 
               ((abs(points[0][i].x - points[1][i].x))+ 
               (abs(points[0][i].y- points[1][i].y)) > 2);
        }
        void handle_tracked_points(cv::Mat &frame, cv::Mat &output) {
            for (int i=0; i<points[1].size(); ++i) {
                cv::line(output, initial[i], points[1][i], 
                        cv::Scalar(255, 255, 255));
                cv::circle(output, points[1][i], 3, 
                        cv::Scalar(255, 255, 255), -1);
            } 
        }
};


// class FeatureTracker : public FrameProcessor {
// private:
//   cv::Mat gray;
//   cv::Mat gray_prev;
//   std::vector<cv::Point2f> points[2];
//   std::vector<cv::Point2f> initial;
//   std::vector<cv::Point2f> features;
//   int max_count;
//   double qlevel;
//   double minDist;
//   std::vector<uchar> status;
//   std::vector<float> err;
//
// public:
//   FeatureTracker() : max_count(500), qlevel(0.01), minDist(10.) {}
//   void process(cv::Mat &src, cv::Mat &dst);
//   bool addNewPoints();
//   void detectFeaturePoints();
//   void handleTrackedPoints(cv::Mat &src, cv::Mat &dst);
//   bool acceptTrackedPoint(int i);
// };
// bool FeatureTracker::addNewPoints() { return points[0].size() < 10; }
// void FeatureTracker::detectFeaturePoints() {
//   cv::goodFeaturesToTrack(gray_prev, features, max_count, qlevel, minDist);
// }
// void FeatureTracker::handleTrackedPoints(cv::Mat &src, cv::Mat &dst) {
//   for (int i = 0; i < points[1].size(); ++i) {
//     cv::line(dst, points[0][i], points[1][i], cv::Scalar(255, 255, 255));
//     cv::circle(dst, points[1][i], 3,cv::Scalar(255, 255, 255), -1);
//   }
// }
// bool FeatureTracker::acceptTrackedPoint(int i) {
//   return status[i] && (fabs(points[1][i].x - points[0][i].x) +
//                        fabs(points[1][i].y - points[0][i].y));
// }
//
// void FeatureTracker::process(cv::Mat &src, cv::Mat &dst) {
//   cv::cvtColor(src, gray, CV_BGR2GRAY);
//   src.copyTo(dst);
//
//   // 1. 特征点检测
//   if (addNewPoints()) {
//     detectFeaturePoints();
//     points[0].insert(points[0].end(), features.begin(), features.end());
//     initial.insert(points[0].end(), features.begin(), features.end());
//   }
//   if (gray_prev.empty())
//     gray.copyTo(gray_prev);
//   // 2. 光流跟踪
//   // cv::calcOpticalFlowPyrLK(gray_prev, gray, points[0], points[1], status, err);
//   // 3. 特征点筛选
//   int k = 0;
//   for (int i = 0; i < points[1].size(); ++i) {
//     if (acceptTrackedPoint(i)) {
//       initial[k] = initial[i];
//       points[1][k++] = points[1][i];
//     }
//   }
//   points[1].resize(k);
//   initial.resize(k);
//   // 4. 特征点绘制
//
//   handleTrackedPoints(src, dst);
//   // 5. 特征点及背景前移
//   std::swap(points[1], points[0]);
//   std::swap(gray_prev, gray);
// }
// process video frame
int main(int argc, char **argv) {
  VideoProcessor vp;
  canny_detector cd;
  Featuretracker ft;
  vp.setWindowInputName("input video");
  vp.setWindowOutputName("output video");
  vp.setDelay(1000. / vp.getFrameRate());
  vp.setFrameToStop(-1);
  vp.setFrameProcess(&ft);
  vp.setInput("/dev/video0");
  // vp.setInput("test.avi");
  // vp.setOutput("test", ".jpg");
  vp.run();
  return 0;
}
