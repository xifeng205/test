#include <opencv2/core.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/videoio.hpp>
#include <vector>

#include <stdio.h>

using namespace std;
using namespace cv;

const std::string WindowName = "Faces Detection example";

class CascadeDetectorAdapter : public DetectionBasedTracker::IDetector {
public:
  CascadeDetectorAdapter(cv::Ptr<cv::CascadeClassifier> detector)
      : IDetector(), Detector(detector) {
    CV_Assert(detector);
  }
  void detect(const cv::Mat &Image,
              std::vector<cv::Rect> &objects) CV_OVERRIDE {
    Detector->detectMultiScale(Image, objects, scaleFactor, minNeighbours, 0,
                               minObjSize, maxObjSize);
  }
  virtual ~CascadeDetectorAdapter() CV_OVERRIDE {}

private:
  CascadeDetectorAdapter();
  cv::Ptr<cv::CascadeClassifier> Detector;
};

int main(int argc, char **argv) {
  namedWindow(WindowName);
  VideoCapture VideoStream(0);
  if (!VideoStream.isOpened()) {
    printf("Error: Cannot open video stream from camera \n");
    return 1;
  }
  std::string cascadeFrontalfilename =
      samples::findFile("/home/cuiyunpeng/tools/opencv/data/lbpcascades/"
                        "lbpcascade_frontalcatface.xml");

  cv::Ptr<cv::CascadeClassifier> cascade =
      cv::makePtr<cv::CascadeClassifier>(cascadeFrontalfilename);

  cv::Ptr<DetectionBasedTracker::IDetector> MainDetector =
      cv::makePtr<CascadeDetectorAdapter>(cascade);
  if (cascade->empty()) {
    printf("Error: Cannot load %s\n", cascadeFrontalfilename.c_str());
    return 2;
  }
  cascade = makePtr<cv::CascadeClassifier>(cascadeFrontalfilename);
  cv::Ptr<DetectionBasedTracker::IDetector> TrackingDetector =
      cv::makePtr<CascadeDetectorAdapter>(cascade);
  if (cascade.empty()) {
    printf("Error: Cannot load %s\n", cascadeFrontalfilename.c_str());
  }
  DetectionBasedTracker::Parameters params;
  DetectionBasedTracker Detector(MainDetector, TrackingDetector, params);
  if (Detector.run()) {
    printf("Error: Detector initialization failed\n");
    return 2;
  }
  cv::Mat ReferenceFrame;
  cv::Mat GrayFrame;
  std::vector<cv::Rect> Faces;
  do {
    VideoStream >> ReferenceFrame;
    cv::cvtColor(ReferenceFrame, GrayFrame, cv::COLOR_BGR2GRAY);
    Detector.process(GrayFrame);
    Detector.getObjects(Faces);
    for (size_t i = 0; i < Faces.size(); i++) {
      cv::rectangle(ReferenceFrame, Faces[i], cv::Scalar(0, 255, 0));
    }

    cv::imshow(WindowName, ReferenceFrame);
  } while (cv::waitKey(30) < 0);

  Detector.stop();
  return 0;
}
