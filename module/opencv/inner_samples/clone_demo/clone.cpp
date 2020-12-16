/*
 *  cloneing_demo.cpp
 *  Author:
 *  Siddharth Kherada <siddharthherada27[at]gail[sot]com>
 *  This tutorial dmonstates how to use Opencv seamless cloning 
 *  modele without GUI
 *  1. Normal Cloning 
 *  2. Mixed Cloning
 *  3. Monochrome Transfer
 *  4. Color Change
 *  5. Illumination change
 *  6. Texture Flattening
 *
 *  This program takes as input a source and a destintion image (for 1-3 methods)
 *  and outputs the cloned iamge.
 *
 *  Download test imgaes from opencv_extra repository.
 */
#include <opencv2/photo/photo.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <iostream>
int main(int argc, char **argv) {
  std::cout << std::endl;
  std::cout << "Note: specify OPENCV_SAMPLES_DATA_PATH_HINT=<opencv_extra>/testdata/cv" << 
    std::endl << std::endl;;
  std::cout << "Cloning Modeule" << std::endl;
  std::cout << "-----------------" << std::endl;
  std::cout << "Options: " << std::endl;
  std::cout << std::endl;
  std::cout << "1) Normal Cloning " << std::endl;
  std::cout << "2) Mixed Cloning " << std::endl;
  std::cout << "3) Monochrome Traansfer " << std::endl;
  std::cout << "4) Local Color Change " << std::endl;
  std::cout << "5) L0cal Color Change " << std::endl;
  std::cout << "6) Texture Flattening " << std::endl;
  std::cout << std::endl;
  std::cout << "Press number 1-6 to choose from above techinques; ";
  int num = 1;
  std::cin >> num;
  std::cout << std::endl;
  if (num == 1) {
    // std::string folder = "../../../data/";
    // std::string original_path1 = cv::samples::findFile(folder + "mask.png");
    // std::string original_path2 = cv::samples::findFile(folder + "mask.png");
    // std::string original_path3 = cv::samples::findFile(folder + "mask.png");

    cv::Mat source = cv::imread("../../../data/box.png", cv::IMREAD_COLOR);
    cv::Mat destination = cv::imread("../../../data/box.png", cv::IMREAD_COLOR);
    cv::Mat mask = cv::imread("../../../data/box.png", cv::IMREAD_COLOR);
    if (source.empty()){
      // std::cout << "Cound not load source image " << original_path1 << std::endl;
      exit(0);
    }
    if (destination.empty()){
      // std::cout << "Cound not load destination image " << original_path2 << std::endl;
      exit(0);
    };
    if (mask.empty()) {
      // std::cout << "Cound not load mask image " << original_path3 << std::endl; 
      exit(0);
    }
    cv::Mat result;
    cv::Point p;
    p.x = 400;
    p.y = 100;
    cv::seamlessClone(source, destination, mask, p, result, 1);
    cv::imshow("seamless image", result);
  }
  return 0; 
}

