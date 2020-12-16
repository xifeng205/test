/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-11-15 11:12
 * Last modified : 2020-11-15 11:12
 * Filename      : chart.cpp
 * Description   :
 *********************************************************************/

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
void draw_train_chart(char *window_name, float max_img_loss, int max_batches,
                      int number_of_lines, int img_size, int dont_show,
                      char *chart_path) {
  int img_offset = 60;
  int draw_size = img_size - img_offset;
  cv::Mat *img_ptr =
      new cv::Mat(img_size, img_size, CV_8UC3, CV_RGB(255, 255, 255));
  cv::Mat &img = *img_ptr;
  cv::Point pt1, pt2, pt_text;
  try {
    // load chart from file
    if (chart_path != NULL && chart_path[0] != '\0') {
      *img_ptr = cv::imread(chart_path);
    } else {
      // draw new chart
      char char_buff[100];
      int i;
      // vertical lines
      pt1.x = img_offset;
      pt2.x = img_size;
      pt_text.x = 30;
      for (i = 1; i <= number_of_lines; ++i) {
        pt1.y = pt2.y = (float)i * draw_size / number_of_lines;
        cv::line(img, pt1, pt2, CV_RGB(224, 224, 224), 1, 8, 0);
        if (i % 10 == 0) {
          sprintf(char_buff, "%2.1f",
                  max_img_loss * (number_of_lines - i) / number_of_lines);
          pt_text.y = pt1.y + 3;
          cv::putText(img, char_buff, pt_text, cv::FONT_HERSHEY_COMPLEX_SMALL,
                      0.7, CV_RGB(0, 0, 0), 1, cv::LINE_AA);
          cv::line(img, pt1, pt2, CV_RGB(128, 128, 128), 1, 8, 0);
        }
      }
      // horizontal lines
      pt1.y = 0;
      pt2.y = draw_size;
      pt_text.y = draw_size + 15;
      for (i = 0; i <= number_of_lines; ++i) {
        pt1.x = pt2.x = img_offset + (float)i * draw_size / number_of_lines;
        cv::line(img, pt1, pt2, CV_RGB(224, 224, 224), 1, 8, 0);
        if (i % 10 == 0) {
          sprintf(char_buff, "%d", max_batches * i / number_of_lines);
          pt_text.x = pt1.x - 20;
          cv::putText(img, char_buff, pt_text, cv::FONT_HERSHEY_COMPLEX_SMALL,
                      0.7, CV_RGB(0, 0, 0), 1, cv::LINE_AA);
          cv::line(img, pt1, pt2, CV_RGB(128, 128, 128), 1, 8, 0);
        }
      }
      // put text on chart
      cv::putText(img, "Loss", cv::Point(10, 60),
                  cv::FONT_HERSHEY_COMPLEX_SMALL, 0.7, CV_RGB(0, 0, 255), 1,
                  cv::LINE_AA);
      cv::putText(
          img, "Iteration number", cv::Point(draw_size / 2, img_size - 10),
          cv::FONT_HERSHEY_COMPLEX_SMALL, 0.7, CV_RGB(0, 0, 0), 1, cv::LINE_AA);
      char max_batches_buff[100];
      sprintf(max_batches_buff, "in cfg max_batches=%d", max_batches);
      cv::putText(
          img, max_batches_buff, cv::Point(draw_size - 195, img_size - 10),
          cv::FONT_HERSHEY_COMPLEX_SMALL, 0.7, CV_RGB(0, 0, 0), 1, cv::LINE_AA);
      cv::putText(img, "Press 's' to save : chart.png",
                  cv::Point(5, img_size - 10), cv::FONT_HERSHEY_COMPLEX_SMALL,
                  0.7, CV_RGB(0, 0, 0), 1, cv::LINE_AA);

      // whether show chart
      if (!dont_show) {
        printf(" If error occurs - run training with flag: -dont_show \n");
        cv::namedWindow(window_name, cv::WINDOW_NORMAL);
        cv::moveWindow(window_name, 0, 0);
        cv::resizeWindow(window_name, img_size, img_size);
        cv::imshow(window_name, img);
      }
    }
  } catch (...) {
    cerr << "OenCV exception: draw_train_chart() \n";
  }
}

int main(int argc, char **argv) {
  char winname[] = {"chart"};
  draw_train_chart(winname, 20, 100, 100, 1000, 0, 0);
  cv::waitKey(0);
  return 0;
}
