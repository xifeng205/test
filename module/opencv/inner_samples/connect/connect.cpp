#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/imgcodecs.hpp>
#include <iostream>

int threshval = 100;
cv::Mat img;
static void on_trackbar(int, void*){
  cv::Mat bw = threshval < 128 ? (img < threshval) : (img > threshval);
  cv::Mat labelImage(img.size(), CV_32S);
  int nLabels = cv::connectedComponents(bw, labelImage, 8);
  std::vector<cv::Vec3b> colors(nLabels);
  colors[0] = cv::Vec3b(0, 0, 0);
  for (int label = 1; label < nLabels; ++label)
  {
    colors[label] = cv::Vec3b((rand()&255), (rand()&255), (rand()&255));
  }
  cv::Mat dst(img.size(), CV_8UC3);
  for (int r = 0; r < dst.rows; ++r) {
    for (int c = 0; c < dst.cols; ++c) {
      int label = labelImage.at<int>(r, c);     
      cv::Vec3b &pixel = dst.at<cv::Vec3b>(r, c);
      pixel = colors[label];
    }
  }
  cv::imshow("Connected Componets", dst);
}

int main(int argc, char **argv){
    // cv::CommandLineParser parser(argc, argv, 
        // "{@image|stuff.jpg image for converting to a grayscale}");

    // parser.about("\nThis program demonstrates connected components and use of the trackbar\n");
    // parser.printMessage();
    std::cout << "\nThe image is vonverted to frayscale and display , another image hs a trakbar\n"
      "that controls thresholding and thereby the extracted contours witch are drawn in color\n";
    // cv::String inputImage = parser.get<std::string>(0);

    img = cv::imread("../../../data/aero1.jpg", cv::IMREAD_GRAYSCALE);
    if (img.empty()) {
      // std::cout << "Could not read input image file: " <<  inputImage << std::endl;
      return EXIT_FAILURE;
    }
    cv::imshow("Image", img);
    cv::namedWindow("Connected Componets", cv::WINDOW_AUTOSIZE);
    cv::createTrackbar("Threshold", "Connected Componets",&threshval, 255, on_trackbar);
    on_trackbar(threshval, 0);
    cv::waitKey(0);

    return EXIT_SUCCESS;
}

