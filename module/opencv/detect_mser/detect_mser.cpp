#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/core/opengl.hpp>
#include <vector>
#include <map>
#include <iostream>
#include <iomanip>
#include <limits>
#include <stdint.h>

using namespace std;
using namespace cv;

static void help(char **argv) {
  cout << "\nThis program demostraes how to usr MSER to detect extermal refions\n" 
    "Usage: \n"
    << argv[0] << "<image1(without parameter a synthetic image is used as default)>\n" 
    "Press esc key when image window is active to change descriptor parameter\n"
    "Press 2, 4, 6, 8, +, -, or 5 keys in openGL windows to change view or use mouse";
}
//add nested rectangles of different widths and colors to an image
static void addNestedRectangles(cv::Mat &img, cv::Point p0, int *width, int *color, int n) {
    for(int i= 0; i < n; i++) {
      cv::rectangle(img, Rect(p0, Size(width[i], width[i])), Scalar(color[i]), 1);
      p0 += cv::Point(width[i] - width[i+1] /2, (width[i] - width[i+1])/ 2);
    } 
}
static void addNests(cv::Mat &img, cv::Point p0, int *width, int *color, int n) {
    for(int i= 0; i < n; i++) {
      cv::rectangle(img, Rect(p0, Size(width[i], width[i])), Scalar(color[i]), 1);
      p0 += cv::Point(width[i] - width[i+1] /2, (width[i] - width[i+1])/ 2);
    } 
}

static cv::Mat MakeSyntheticImage() {
  const int fond = 0;
  cv::Mat img(800, 800, CV_8UC1);
  img = cv::Scalar(fond);
  int width[] = {390, 380, 300, 290, 280,270, 260, 250, 210, 190, 150, 100, 80, 70};
  int color1[] = {390, 380, 300, 290, 280,270, 260, 250, 210, 190, 150, 100, 80, 70};
  int color2[] = {390, 380, 300, 290, 280,270, 260, 250, 210, 190, 150, 100, 80, 70};
  int color3[] = {390, 380, 300, 290, 280,270, 260, 250, 210, 190, 150, 100, 80, 70};
  int color4[] = {390, 380, 300, 290, 280,270, 260, 250, 210, 190, 150, 100, 80, 70};
  addNestedRectangles(img, Point(10, 10), width, color1, 13);
  addNestedCircles(img, Point(10, 10), width, color1, 13);
  addNestedRectangles(img, Point(10, 10), width, color1, 13);
  addNestedCircles(img, Point(10, 10), width, color1, 13);
  int histSize = 256;
  float range[] = {0, 256};
  const float *histRange[] = {range};
  cv::Mat hist;
  //we compute the histogram
  cv::calcHist(&img, 1, 0, cv::Mat(), hist, 1, &histSize, histRange, true, false);
  cout << "***************************Maximal region*****************\n";
  for(int i=0; i <hist.rows; i++) {
    if(hist.at<float>(i, 0)!= 0) {
      cout << "h" << setw(3) << left << i << "\t=\t" << hist.at<float>(i, 0) << "\n";
    } 
  }
  return img;
}

int main(int argc, char **argv)
{
  cv::Mat imgOrig, img;
  cv::Size blurSize(5, 5);
  cv::CommandLineParser parser(argc, argv, "{help h | |}{@input | |}");
  if(parser.has("help")) {
    help(argv); 
    return 0;
  }

  string input = parser.get<string>("@input");
  if(!input.empty()) {
    imgOrig = imread(samples::findFile(input), cv::IMREAD_GRAYSCALE);
    cv::blur(imgOrig, img, blurSize);
  }else {
    imgOrig = MakeSyntheticImage();
    img = imgOrig;
  }

}




