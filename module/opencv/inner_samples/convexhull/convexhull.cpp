#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
using namespace cv;
using namespace std;

static void help(char **argv) {
    cout << "\nThis sample program demostrates the use of the convexHull() function\n"
      << "Call:\n"
      << argv[0] << std::endl;; 
}

int main(int argc, char **argv) {
  CommandLineParser parser(argc, argv, "{help h||}"); 
  if (parser.has("help")) {
    help(argv); 
    return 0;
  }
  cv::Mat img(500, 500, CV_8UC3);
  cv::RNG rng = cv::theRNG();
  for (;;) {
    int i, count = (unsigned)rng%100 + 1; 
    std::vector<cv::Point> points;
    for (i = 0; i < count; i++) {
      cv::Point pt; 
      pt.x = rng.uniform(img.cols/4, img.cols*3/4);
      pt.y = rng.uniform(img.rows/4, img.rows*3/4);
      points.push_back(pt);
    }
    std::vector<int> hull;
    cv::convexHull(cv::Mat(points), hull, true);
    img = cv::Scalar::all(0);
    for (i = 0; i < count; i++) {
      cv::circle(img, points[i], 3, cv::Scalar(0, 0, 255), cv::FILLED, cv::LINE_AA);
    }
    int hullcount = (int)hull.size();
    cv::Point pt0 = points[hull[hullcount - 1]];
    for(i = 0; i< hullcount; i++) {
      cv::Point pt = points[hull[i]];
      cv::line(img, pt0, pt, cv::Scalar(0, 255, 0), 1, cv::LINE_AA);
      pt0 = pt;
    }

    cv::imshow("hull", img);
    char key = (char)waitKey();
    if (key == 27 || key == 'q' || key == 'Q')break;
  }
  return 0;
}
