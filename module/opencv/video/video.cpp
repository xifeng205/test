/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-09-04 07:53
 * Last modified : 2020-09-04 07:53
 * Filename      : video.cpp
 * Description   :
 *********************************************************************/

#include <iomanip>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgproc/types_c.h>
#include <opencv2/video/video.hpp>
#include <opencv2/videoio/legacy/constants_c.h>
#include <sstream>

using namespace std;
#define test
#if defined test1

int main(int argc, char **argv) {
  cv::VideoCapture cpv(3);
  if (!cpv.isOpened())
    return 1;
  double rate = cpv.get(CV_CAP_PROP_FPS);
  bool stop(false);
  cv::Mat frame;
  cv::namedWindow("vido");
  int delay = 1000 / rate;
  while (!stop) {
    if (!cpv.read(frame))
      break;
    cv::imshow("vido", frame);
    if (cv::waitKey(delay) >= 0)
      stop = true;
  }
  cpv.release();

  return 0;
}
#elif defined test
class FrameProcess {
public:
  virtual void process(cv::Mat &input_img, cv::Mat &output_img) = 0;
};
class FrameProcessor : public FrameProcess {
public:
  void process(cv::Mat &input_img, cv::Mat &output_img) {
    if (input_img.channels() == 3)
      cv::cvtColor(input_img, output_img, CV_BGR2GRAY);
    cv::Canny(output_img, output_img, 100, 200);
    cv::threshold(output_img, output_img, 18, 255, cv::THRESH_BINARY);
  }
};
class VideoProcessor {
private:
  cv::VideoCapture capture;
  std::vector<std::string> images;
  std::vector<std::string>::const_iterator it;
  void (*process)(cv::Mat &img, cv::Mat &outImg);
  FrameProcess *framprocessor;
  bool callIt;
  std::string windowNameInput;
  std::string windowNameOutput;
  int delay;
  long fnumber;
  long frameToStop;
  bool stop;

  cv::VideoWriter writer;
  //输出文件名称
  std::string outFilename;
  //输出图像的当前索引
  int currentIndex;
  //输出图像中的数字位数
  int digits;
  //输出图像的扩展位
  std::string extension;

public:
  VideoProcessor()
      : callIt(true), delay(0), fnumber(0), stop(false), frameToStop(-1) {}

  void setFrameProcess(void (*frameProcessCallBack)(cv::Mat &img,
                                                    cv::Mat &outImg)) {
    process = frameProcessCallBack;
  }
  void setFrameProcess(FrameProcess *processor) {
    process = 0;
    framprocessor = processor;
    call_process();
  }
  bool set_intput(std::string filename) {
    fnumber = 0;
    capture.release();
    return capture.open(filename);
  }

  void displayInput(std::string wn) {
    windowNameInput = wn;
    cv::namedWindow(windowNameInput);
  }
  void displayOutput(std::string wn) {
    windowNameOutput = wn;
    cv::namedWindow(windowNameInput);
  }
  //不再显示处理后的帧

  void dontDisplay(void) {
    cv::destroyWindow(windowNameInput);
    cv::destroyWindow(windowNameOutput);
    windowNameInput.clear();
    windowNameOutput.clear();
  }
  //获取并处理视频帧
  void stopIt() { stop = true; }
  //是否已经停止
  bool isStoped() { return stop; }
  //是否已经开始了捕获设备
  bool isOpened() { return capture.isOpened() || !images.empty(); }
  //设置帧间延迟, 0, 意味着每帧都等待用户按键, 负数意味这没有延迟
  void setDelay(int d) { delay = d; }
  //得到一帧,可能是视频或者摄像头
  // bool readNextFrame(cv::Mat &frame) {
  // return capture.read(frame);
  // }
  //得到一帧,可能是视频或者摄像头
  bool readNextFrame(cv::Mat &frame) {
    if (images.size() == 0) {
      return capture.read(frame);
    } else {
      if (it != images.end()) {
        frame = cv::imread(*it);
        ++it;
        return frame.data != 0;
      } else {
        return false;
      }
    }
  }
  //使用帧处理接口
  //在面向对象的上下文中, 更适合帧处理类而不是帧处理函数,
  //使用类给程序员根多的灵活性 需要调用回调函数
  void call_process() { callIt = true; }
  void dont_call_process() { callIt = false; }
  void stopAtFrameNo(long frame) { frameToStop = frame; }
  long getFrameNumber() {
    return static_cast<long>(capture.get(CV_CAP_PROP_POS_FRAMES));
  }
  long getFrameRate() {
    return static_cast<long>(capture.get(CV_CAP_PROP_FPS));
  }
  //设置输入的图像向量
  bool setInput(std::vector<std::string> &imgs) {
    fnumber = 0;
    //释放之前打开国的资源
    capture.release();
    //输入将是该图像的向量
    images = imgs;
    it = imgs.begin();
    return true;
  }
  //得到视频输入的编解码
  int getCodec(char codec[4]) {
    //未指定图像内容
    if (images.size() != 0)
      return -1;
    union { // 4 char 编码的数据结果
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
  cv::Size getFramSize() {
    return cv::Size(capture.get(CV_CAP_PROP_FRAME_WIDTH),
                    capture.get(CV_CAP_PROP_FRAME_HEIGHT));
  }
  //设置输出视频文件
  bool setOutput(const std::string &filename, int codec = 0,
                 double framrate = 0.0, bool is_color = true) {
    outFilename = filename;
    extension.clear();
    if (framrate == 0.0) {
      framrate = getFrameRate();
    }
    char c[4];
    //使用相同的编码格式
    if (codec == 0) {
      codec = getCodec(c);
    }
    return writer.open(outFilename, codec, framrate, getFramSize(), is_color);
  }
  bool setOutput(const std::string &filename, const std::string &ext,
                 int numberOfDights = 3, int startIndex = 0) {
    //数字位数必须是整数的
    if (numberOfDights < 0)
      return false;
    //文件名及其后缀
    outFilename = filename;
    extension = ext;
    //文件命名中的数字位数
    digits = numberOfDights;
    currentIndex = startIndex;
    return true;
  }
  void writeNextFrame(cv::Mat &frame) {
    //输出帧:可能是视频文件, 或者是图像文件
    if (extension.length()) {
      //我们输出到图像文件
      std::stringstream ss;
      //组成输出文件名称
      ss << outFilename << std::setfill('0') << std::setw(digits)
         << currentIndex++ << extension;
      cv::imwrite(ss.str(), frame);
    } else {
      writer.write(frame);
    }
  }

  void run(void) {
    cv::Mat frame;
    cv::Mat output;
    if (!isOpened())
      return;
    stop = false;
    while (!isStoped()) {
      //读取下一帧
      if (!readNextFrame(frame))
        break;
      if (windowNameInput.length() != 0)
        cv::imshow(windowNameInput, frame);
      if (callIt) {
        if (process)
          process(frame, output);
        else if (framprocessor) {
          framprocessor->process(frame, output);
          fnumber++;
        }
      } else {
        output = frame;
      }
      //输出图像序列
      if (outFilename.length() != 0)
        writeNextFrame(frame);
      //显示输出帧
      if (windowNameOutput.length() != 0) {
        cv::imshow(windowNameOutput, output);
      }
      //引入延迟
      if (delay > 0 && cv::waitKey(delay) >= 0)
        stopIt();
      //检查是否需要停止运行
      if (frameToStop >= 0 && getFrameNumber() == frameToStop)
        stopIt();
    }
  }
};
void canny(cv::Mat &input_img, cv::Mat &output_img) {
  if (input_img.channels() == 3) {
    cv::cvtColor(input_img, output_img, CV_BGR2GRAY);
  }
  cv::Canny(output_img, output_img, 100, 200);
  cv::threshold(output_img, output_img, 10, 255, cv::THRESH_BINARY);
}
//为了在不同的帧之间跟踪特帧点, 我们必须定位特帧在点在随后图像中的新位置, 
//如果我们我假定特征点的强度在新的相邻帧之间不发生变化, 那么我们要找到一个
class FeatureTracker: public FrameProcess {
   private:
    cv::Mat gray;
    cv::Mat gray_prev;
    //两幅图峡谷内跟踪的特征点
    std::vector<cv::Point2f> pt[2];
    std::vector<cv::Point2f> initial;
    //检测到的特征
    std::vector<cv::Point2f> features;
    //需要跟踪的最大特征数
    int max_count;
    //特征检测中的质量等级
    double qlevel;
    //亮点之间的最小距离
    double min_dist;
    //检测到的特征状态
    std::vector<uchar> status;
    //根中过程中的错误
    std::vector<float> err;

  public:
    FeatureTracker(): max_count(300), qlevel(0.01), min_dist(10.){};
    int addNewPoint(){
      return pt[0].size() <= 10;
    }
    void detectFeaturePoints(){
      cv::goodFeaturesToTrack(gray, features, max_count, qlevel, min_dist);
    }
    bool acceptTrackerPoints(int i){
      return status[i] &&
        (abs(pt[0][i].x - pt[1][i].x) + abs(pt[0][i].y - pt[1][i].y)) > 2;
    }    
    void handleTrackPoints(cv::Mat &frame, cv::Mat &output){
      for (int i = 0; i < pt[0].size(); ++i){
        //遍历所有的跟踪点
        //绘制直线与圆
        cv::line(output, initial[i], pt[1][i], cv::Scalar(255, 255, 255));
        cv::circle(output, pt[1][i], 3, cv::Scalar(255, 255, 255), -1);
      }
    } 
    void process(cv::Mat &input_img, cv::Mat &output_img) {
      //转化为灰色图像
      cv::cvtColor(input_img, gray, CV_BGR2GRAY);
      gray.copyTo(output_img);
      // 1. 如果需要添加新的特帧点
      if (addNewPoint()) {
          detectFeaturePoints();
          //添加检测到的特征到当前的特帧中
          pt[0].insert(pt[0].end(), features.begin(), features.end());
          initial.insert(initial.end(), features.begin(), features.end());
      }
      //对于序列中的第一副图像
      if (gray_prev.empty()) gray.copyTo(gray_prev);
      //  2 跟踪特征点
      cv::calcOpticalFlowPyrLK(gray_prev, gray, pt[0], pt[1], status, err); 
      //遍历所有跟踪的点进行筛选
      int k; 
      for (int i = 0; i < pt[1].size(); i++) {
        //是否需要保留该点
        if (acceptTrackerPoints(i)) {
          initial[k] = initial[i];
          pt[1][k++] =pt[1][i];
        }
      }
      //去除不成共的点
      pt[1].resize(k);
      //3 处理接受的跟踪点
      handleTrackPoints(input_img, output_img);
      //4 当前帧的点变为前一帧的点
      std::swap(pt[1], pt[0]);
      std::swap(gray_prev, gray);
    }
 };
class Featuretracker : public FrameProcess {
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

int main(int argc, char **argv) {
  VideoProcessor vp;
  vp.set_intput("/dev/video2");
  vp.displayInput("current img");
  vp.displayOutput("output img");
  vp.setDelay(1000 / vp.getFrameRate());
  Featuretracker ft;
    // FrameProcessor fp;
  vp.setFrameProcess(&ft);
  // vp.setOutput("test.avi");

  vp.run();

  return 0;
}
#endif
