
/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-06-05 11:20
 * Last modified : 2020-06-05 11:20
 * Filename      : canny.cpp
 * Description   : 
*********************************************************************/

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#define PI CV_PI
using namespace std;

class Linefinder {
    private:
        cv::Mat img;
        std::vector<cv::Vec4i> lines;
        double delta_rho;
        double delta_theta;
        int min_vote;
        double min_length;
        double max_gap;
    public:
        Linefinder():delta_rho(1), delta_theta(PI/180),
        min_vote(10), min_length(0), max_gap(0){}    

        void set_acc_resolution(double rho, double theta) {
            delta_rho = rho;
            delta_theta = theta;
        }
        void set_min_vote(int vote) {
            min_vote = vote;
        }
        void set_min_length(double length) {
            min_length = length;
        }
        void set_max_gap(double gap) {
            max_gap = gap;
        }
        std::vector<cv::Vec4i> line_find(cv::Mat &binary_image) {
            lines.clear();
            cv::HoughLinesP(binary_image, lines, delta_rho,
                    delta_theta, min_vote, min_length, max_gap);
            return lines;
        }
        void draw_detector_lines(cv::Mat image, 
                cv::Scalar color = cv::Scalar(255, 255, 255)) {
            std::vector<cv::Vec4i>::const_iterator it2 = lines.begin();
            while (it2 != lines.end()) {
                cv::Point pt1((*it2)[0], (*it2)[1]);
                cv::Point pt2((*it2)[2], (*it2)[3]);
                cv::line(image, pt1, pt2, color);
                it2++;
            }
        }
};
int main(int argc, char **argv)
{
    cv::Mat image = cv::imread("../../../data/stuff.jpg", 0);

    cv::Mat contours;
    cv::Canny(image, contours, 125, 350);
    cv::imshow("contous image", contours);
    
    Linefinder linefinder;
    linefinder.set_max_gap(20);
    linefinder.set_min_length(100);
    linefinder.set_min_vote(80);

    linefinder.line_find(contours);
    linefinder.draw_detector_lines(image);
    
    cv::imshow("line image", image);

    cv::waitKey();
    return 0;
}
