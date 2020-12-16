/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-09-06 12:32
 * Last modified : 2020-09-06 12:32
 * Filename      : cout_mat.cpp
 * Description   : This file a part of opencv project
 * It is subjecy license terms in the LICENSE file found in the top
 * level director, of this distribution and at http://opencv.org/licese.html
 *********************************************************************/

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/video/video.hpp>
#include <opencv2/videoio/videoio.hpp>

using namespace std;

int main(int argc, char **argv) {
  const cv::String keys = "{c camera    | 0 | use video stream from camera"
                          "(device index starting from 0) }"
                          "{fn file_name |   | use video file as input }"
                          "{m method | mog2 | method: background subtraction "
                          "algorithm ('knn', 'mog2')}"
                          "{h help |  | show help message}";
  cv::CommandLineParser parser(argc, argv, keys);
  parser.about("This sample demonstrtes b ackground segmentation.");
  if (parser.has("help")) {
    parser.printMessage();
    return 0;
  }
  int camera = parser.get<int>("camera");
  cv::String file = parser.get<cv::String>("file_name");
  cv::String method = parser.get<cv::String>("method");
  if (!parser.check()) {
    parser.printErrors();
    return 1;
  }
  cv::VideoCapture cap;
  if (file.empty())
    cap.open(camera);
  else {
    file = cv::samples::findFileOrKeep(file);
    cap.open(file.c_str());
  }
  if (!cap.isOpened()) {
    std::cout << "Can not open video stream: '"
              << (file.empty() ? "<camera>" : file) << "'" << std::endl;
    return 2;
  }
  cv::Ptr<cv::BackgroundSubtractor> model;
  if (method == "knn")
    model = cv::createBackgroundSubtractorKNN();
  else if (method == "mog2")
    model = cv::createBackgroundSubtractorMOG2();
  if (!model) {
    std::cout << "Can not create backgrounf model using provided method: '"
              << method << "'" << std::endl;
    return 3;
  }

  std::cout << "Press <space> to toggle background model update" << std::endl;
  std::cout << "Press 's' to toggel foreground mask smoothing " << std::endl;
  std::cout << "Press ESC or 'q' to exit" << std::endl;
  bool doUpdateModel = true;
  bool doSmoothMask = false;
  cv::Mat inputFrame, frame, foregroundMask, foreground, background;
  for (;;) {
    // prepare input frame
    cap >> inputFrame;
    if (inputFrame.empty()) {
      std::cout << "Finished reading: empty frame" << std::endl;
      break;
    }
    const cv::Size scaledSize(640, 640 * inputFrame.rows / inputFrame.cols);
    cv::resize(inputFrame, frame, scaledSize, 0, 0, cv::INTER_LINEAR);
    // pass the frame to backgroundMask model
    model->apply(frame, foregroundMask, doUpdateModel ? -1 : 0);
    cv::imshow("imgage", frame);
    // show foreground image and mask (with optional smoothing)
    if (doSmoothMask) {
      cv::GaussianBlur(foregroundMask, foregroundMask, cv::Size(11, 11), 3.5,
                       3.5);
      cv::threshold(foregroundMask, foregroundMask, 10, 255, cv::THRESH_BINARY);
    }
    if (foreground.empty())
      foreground.create(scaledSize, frame.type());
    foreground = cv::Scalar::all(0);
    frame.copyTo(foreground, foregroundMask);
    cv::imshow("foreground mask", foregroundMask);
    cv::imshow("foreground image", foreground);
    // show background imgae
    model->getBackgroundImage(background);
    if (!background.empty()) {
      cv::imshow("mean background image", background);
      //
    }
    //interact with user
    const char key = (char)cv::waitKey(30);
    if (key == 27 || key == 'q') {
      std::cout << "Exit requested" << std::endl;
      break;
    } else if (key == ' ') {
      doUpdateModel = !doUpdateModel;
      std::cout << "Toggle background update: " << (doUpdateModel ? "ON" : "OFF")
        << std::endl;
    } else if (key == 's') {
      doSmoothMask = !doSmoothMask;
      std::cout << "Toggle foreground mask smoothing: "
        << (doSmoothMask ? "ON" : "OFF") << std::endl;
    }
  }

  return 0;
}
