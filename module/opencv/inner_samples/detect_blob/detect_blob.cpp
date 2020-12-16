#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/features2d.hpp>
#include <map>
#include <iostream>

using namespace std;
using namespace cv;

static void help(char **argv) {
   
}

int main(int argc, char **argv) {
  cv::String fileName;
  cv::CommandLineParser parser(argc, argv, "{@input |detect_blob.png| }{h help || }");
  if (parser.has("help")) {
      help(argv); 
     return -1;
  }
  fileName= parser.get<string>("@input");
  cv::Mat img = cv::imread(samples::findFile(fileName), cv::IMREAD_COLOR);
  if (img.empty()) {
      cout << "Image " << fileName << " is empty or cnanot be found\n";
      return -1;
  }
  SimpleBlobDetector::Params pDefaultBLOB;
  //This is default parameters for DimpleBlobDetector
  pDefaultBLOB.thresholdStep = 10;
  pDefaultBLOB.minThreshold = 10;
  pDefaultBLOB.maxThreshold = 220;
  pDefaultBLOB.minRepeatability = 2;
  pDefaultBLOB.minDistBetweenBlobs = 10;
  pDefaultBLOB.filterByColor = 0;
  pDefaultBLOB.minArea = 25;
  pDefaultBLOB.maxArea= 5000;
  pDefaultBLOB.filterByCircularity = false;
  pDefaultBLOB.minCircularity = 0.9f;
  pDefaultBLOB.maxCircularity = (float)1e37;
  pDefaultBLOB.filterByInertia = false;
  pDefaultBLOB.minInertiaRatio = 0.1f;

}

