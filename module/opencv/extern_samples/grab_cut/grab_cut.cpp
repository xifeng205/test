/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-06-04 17:10
 * Last modified : 2020-06-04 17:10
 * Filename      : grab_cut.cpp
 * Description   : 
*********************************************************************/

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;

class Grabcut {
    private:
};

int main(int argc, char **argv)
{
    cv::Mat image = cv::imread("../../../data/ellipses.jpg");
    cv::imshow("origin image", image);
    cv::Rect rectangle(30, 21,280, 170);

    cv::Mat result;
    cv::Mat fg_model;
    cv::Mat bg_model;

    cv::grabCut(image, result, rectangle, bg_model, fg_model,
            5, cv::GC_INIT_WITH_RECT);
    cv::compare(result, cv::GC_PR_FGD, result, cv::CMP_EQ);
    cv::Mat foreground(image.size(), CV_8UC3,
            cv::Scalar(255, 255, 255));
    // image.copyTo(foreground, result);

    // cv::imshow("cut image1", result);

    // result = result&1;
    image.copyTo(foreground, result);
    cv::imshow("cut image", result);

    cv::waitKey();
    return 0;
}
