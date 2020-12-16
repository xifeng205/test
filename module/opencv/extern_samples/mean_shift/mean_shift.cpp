/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-06-02 09:46
 * Last modified : 2020-06-02 09:46
 * Filename      : histogram.cpp
 * Description   : 
*********************************************************************/

#include <algorithm>
#include <iostream>
#include <iterator>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgproc/types_c.h>
#include <opencv2/video/tracking.hpp>

using namespace std;

class Contentfinder {
    private:
        float hranges[2];
        const float *ranges[3];
        int channels[3];
        float threshold;
        cv::MatND histogram;
    protected:
    public:
        Contentfinder():threshold(-1.0f) {
            ranges[0] = hranges;
            ranges[1] = hranges;
            ranges[2] = hranges;
        }

        void set_threshold(float t) {
            threshold = t;
        }
        float get_threshold() {
            return threshold;
        }
        void set_histogram(cv::MatND &h) {
            histogram = h;  
            cv::normalize(histogram, histogram, 1.0);
        } 

        cv::Mat content_find(cv::Mat &image, float min_val,
                float max_val, int *channels, int dim) {
            cv::Mat result;
            hranges[0] = min_val;
            hranges[1] = max_val;
            
            for (int i=0; i<dim; ++i) {
                this->channels[i] = channels[i];
            }
            cv::calcBackProject(&image,
                    1,
                    channels,
                    histogram,
                    result,
                    ranges,
                    255.0);
           if (threshold > 0.0) {
                cv::threshold(result, result, 255*threshold, 255,
                        cv::THRESH_BINARY);
           } 
            return result;
        }
        
        cv::Mat equalize(const cv::Mat &image) {
            cv::Mat result;
            cv::equalizeHist(image, result);
            return result;
        }
};

class Colorhistogram {
    private:
       int hist_size[3];
       float hranges[2];
       const float *ranges[3];
       int channels[3];
       
    protected:

    public:
       Colorhistogram() {
           hist_size[0] = hist_size[1] = hist_size[2]=256;
           hranges[0] = 0.0;
           hranges[1] = 255.0;
           ranges[0] = hranges;
           ranges[1] = hranges;
           ranges[2] = hranges;
           channels[0] = 0;
           channels[1] = 1;
           channels[2] = 2;
       }
       cv::MatND get_histogram(const cv::Mat &image) {
           cv::MatND hist;
           cv::calcHist(&image, 1, channels, cv::Mat(),
                   hist, 3, hist_size, ranges);
           return hist;
       }
       void color_reduce(cv::Mat &img, int div) {
           int nl = img.rows;
           int nc = img.cols * img.channels();

           for (int j=0; j<nl; ++j) {
               uchar *data = img.ptr<uchar>(j);
               for (int i = 0; i<nc; ++i) {
                   data[i] = data[i] -data[i]%div
                       +div/2;  
               }
           }
       }
       cv::MatND get_hue_histogram(cv::Mat &image, 
               int min_saturation) {
           cv::MatND hist;
           cv::Mat hsv;
           cv::cvtColor(image, hsv, CV_BGR2HSV);
           cv::Mat mask;
           if (min_saturation>0) {
               std::vector<cv::Mat> v;
               cv::split(hsv, v);
               cv::threshold(v[1], mask, min_saturation, 
                       255, cv::THRESH_BINARY);
           }
            hranges[0] = 0.0;
            hranges[1] = 180.0;
            channels[0] = 0;
            cv::calcHist(&hsv, 1, channels, mask, hist,   
                    1, hist_size, ranges);

            return hist;
       }
};

class Meanshift :public Colorhistogram {
    private:
        

    protected:

    public:
};
int main(int argc, char **argv)
{
    Colorhistogram hc;
    cv::Mat image = cv::imread("../../../data/home.jpg");

    hc.color_reduce(image, 4);
    cv::Mat img_roi = image(cv::Rect(0, 240, 45, 65));
    int min_sat = 64;
    cv::MatND hist = hc.get_hue_histogram(img_roi, min_sat);

    Contentfinder finder;
    finder.set_histogram(hist);

    cv::Mat image_trace = cv::imread("../../../data/home.jpg");
    hc.color_reduce(image_trace, 4);

    cv::imshow("image", image_trace);

    cv::Mat hsv_image_trace;
    cv::cvtColor(image_trace, hsv_image_trace, CV_BGR2HSV);

    std::vector<cv::Mat> v;
    cv::split(hsv_image_trace, v);

    cv::threshold(v[1], v[1], min_sat, 255, cv::THRESH_BINARY);

    finder.set_threshold(0.05f);

    int channels[1] = {0};
    cv::Mat result = finder.content_find(hsv_image_trace, 0.0, 180.0,
            channels, 1);
    cv::bitwise_and(result, v[1], result);

    cv::Rect rect(0, 240, 45, 65);
    cv::rectangle(result, rect, cv::Scalar(0, 0, 255));

    cv::TermCriteria criteria(cv::TermCriteria::MAX_ITER, 10, 0.01);
    cv::meanShift(result, rect, criteria);
    
    cv::imshow("trace image", result);

    cv::waitKey(0);
    return 0;
}
