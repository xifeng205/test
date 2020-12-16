

/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-06-04 08:00
 * Last modified : 2020-06-04 08:00
 * Filename      : erode_dilate.cpp
 * Description   : 
*********************************************************************/

#include <atomic>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
class Morphofeatures {
    private:
        int threshold;
        cv::Mat cross;
        cv::Mat diamond;
        cv::Mat square;
        cv::Mat x;
    public:
        Morphofeatures(int t=0.05):threshold(t),   
        cross(5, 5,CV_8U, cv::Scalar(0)),
        diamond(5, 5, CV_8U, cv::Scalar(1)), 
        x(5, 5, CV_8U, cv::Scalar(0)), 
        square(5, 5, CV_8U, cv::Scalar(1)) {
            for (int i=0; i<5; ++i) {
                cross.at<uchar>(2, i) = 1;
                cross.at<uchar>(i, 2) = 1;
            }            
            diamond.at<uchar>(0, 0)  =0;
            diamond.at<uchar>(0, 1)  =0;
            diamond.at<uchar>(1, 0)  =0;
            diamond.at<uchar>(4, 4)  =0;
            diamond.at<uchar>(3, 4)  =0;
            diamond.at<uchar>(4, 3)  =0;
            diamond.at<uchar>(4, 0)  =0;
            diamond.at<uchar>(4, 1)  = 0;
            diamond.at<uchar>(3, 0)  = 0;
            diamond.at<uchar>(0, 4)  = 0;
            diamond.at<uchar>(0, 3)  = 0;
            diamond.at<uchar>(1, 4)  = 0;

            for (int i=0; i<5; ++i) {
                cross.at<uchar>(i, i) = 1; 
                cross.at<uchar>(4-i, i) = 1; 
            }

        };
        cv::Mat get_edges(cv::Mat &image) {
            cv::Mat result;
            cv::morphologyEx(image, result, cv::MORPH_GRADIENT, cv::Mat());
            apply_threshold(result);
            return result;
        }
        cv::Mat apply_threshold(cv::Mat &image) {
            if (threshold > 0)
                cv::threshold(image, image, threshold, 255, cv::THRESH_BINARY);
            return image;
        }
        void set_threshold(int t) {
            threshold = t;
        }
        cv::Mat get_corners(const cv::Mat &image) {
            cv::Mat result;
            cv::dilate(image, result, cross);
            cv::erode(result, result, diamond);

            cv::Mat result2;
            cv::dilate(result, result2, x);
            cv::erode(result2, result2, square);
            
            cv::absdiff(result2, result, result);
            apply_threshold(result);
            
            return result;
        }
        void draw_on_image(const cv::Mat &binary, cv::Mat &image) {
            cv::Mat_<uchar>::const_iterator it = 
                binary.begin<uchar>(); 
            cv::Mat_<uchar>::const_iterator it_end = 
                binary.end<uchar>();
            for (int i;it!=it_end; ++it, ++i) {
                if (!*it) {
                    cv::circle(image, cv::Point(i%image.step, i/image.step),
                            4, cv::Scalar(255, 0, 0));
                }
            }
        }
};

class Watershed {
    private:
        cv::Mat markers;
    public:
        void set_markers(cv::Mat &mark_image) {
            mark_image.convertTo(markers, CV_32S);
        }
        cv::Mat get_markers() {
            cv::Mat tmp;
            markers.convertTo(tmp, CV_8U, 255, 255);
            return tmp;
        }
        cv::Mat process(const cv::Mat &image) {
            cv::watershed(image, markers);
            return markers;
        }  
};
int main(int argc, char **argv)
{
    Watershed watershed;
    cv::Mat image = cv::imread("../../../data/lena.jpg", 0);
    cv::imshow("orign image", image);
    cv::threshold(image, image, 128, 255, cv::THRESH_BINARY);
    
    cv::Mat fg;
    cv::erode(image, fg, cv::Mat(), cv::Point(-1, -1), 6);
    
    cv::Mat bg;
    cv::dilate(image, bg, cv::Mat(), cv::Point(-1, -1), 6);
    cv::threshold(bg, bg, 1, 128,cv::THRESH_BINARY_INV);
   
    cv::Mat marker(bg.size(), CV_8U, cv::Scalar(0));
    marker = fg+bg;
      
    watershed.set_markers(marker);
    watershed.process(image);

    cv::Mat result = watershed.get_markers(); 
    // cv::imshow("fg image", fg);
    // cv::imshow("bg image", bg);
    // cv::imshow("marker image", result);

    
    cv::waitKey(0);
    return 0;
}
