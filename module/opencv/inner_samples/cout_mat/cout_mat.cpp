/*
 * cvout_sample just demonstrates the derial out capabilities of cv::Mat 
 * That is, cv::Mat M(...); cout << M; Now works.
 */

#include <opencv2/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
using namespace std;
using namespace cv;
static void help(char **argv){
  cout 
    << "\n---------------------------------------------------------------\n"
    << "This program shows the erial out capabilitid of cv::Mat\n"
    << "That is, cv::Mat M(...); cv::cout << M; Now works.\n"
    << "Output can be foramatted to Opencv, matlab, python, numpy, csv, and\n"
    << "C styles Usage:\n"
    << argv[0]
    << "\n---------------------------------------------------------------\n\n"
    << endl;
}
int main(int argc, char **argv) {
  CommandLineParser parser(argc, argv, "{help h||}");
  if (parser.has("help")) {
      help(argv); 
      return 0;
  }

  cv::Mat I = cv::Mat::eye(4, 4, CV_64F);
  // cv::imshow("img", I);
  //
  I.at<double>(1, 1) = CV_PI;
  // cout << I.at<double>(1, 1) << std::endl;

  // cout << "I = \n" << I << ";" << endl << endl;
  cv::Mat r  = cv::Mat(10, 3, CV_8UC3);
  cv::randu(r, cv::Scalar::all(0), cv::Scalar::all(255));
  // cout << "r (default) = \n" << r <<";" << endl << endl; 
  // cout << "r(matlab) = \n" << cv::format(r, Formatter::FMT_MATLAB); 
  // cout << "r(python) = \n" << cv::format(r, Formatter::FMT_PYTHON); 
  // cout << "r(numpy) = \n" << cv::format(r, Formatter::FMT_NUMPY); 
  // cout << "r(csv) = \n" << cv::format(r, Formatter::FMT_CSV); 
  // cout << "r(c) = \n" << cv::format(r, Formatter::FMT_C); 
  // cv::Point2f p(5, 1);
  // cout << "p = \n" << p << ";" << endl;
  // cv::Point3f p3(1, 6, 6);
  // cout << "p = \n" << p3 << endl;
  std::vector<float> v;
  v.push_back(1);
  v.push_back(2);
  v.push_back(3);
  cout << "shortvec = " << Mat(v) << endl;
  vector<Point2f> points(20);
  for(size_t i = 0; i < points.size(); ++i) {
    points[i] = Point2f((float)(i*5), (float)(i % 7));
  }
  cout << "Points = " << points << ";" << endl;
  // cv::imshow("img", r);
  cv::waitKey(0);
  return 0; 
}
