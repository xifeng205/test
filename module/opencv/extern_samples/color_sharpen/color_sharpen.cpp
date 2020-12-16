/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-05-27 17:53
 * Last modified : 2020-05-27 17:53
 * Filename      : color_sharpen.cpp
 * Description   : 
*********************************************************************/
#include <algorithm>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>


using namespace std;

class Sharpen {
    public:
        void sharpen(const cv::Mat &image, cv::Mat &result)
        {
            int nc = image.cols*image.channels();
            result.create(image.size(), image.type());
            for (int j=1; j<image.rows-1; ++j) {
                const uchar *previous = image.ptr<const uchar>(j-1);
                const uchar *current = image.ptr<const uchar>(j);
                const uchar *next = image.ptr<const uchar>(j+1);
                uchar *output = result.ptr<uchar>(j);
                for (int i=1; i<nc-1; ++i) {
                    *output++ = cv::saturate_cast<uchar>(
                            5*current[i]-current[i-1]-current[i+1]
                            -previous[i]-next[i]);
                }
            }
            result.row(0).setTo(cv::Scalar(0, 0, 0));
            result.row(result.rows-1).setTo(cv::Scalar(0, 0, 0));
            result.col(0).setTo(cv::Scalar(0));
            result.col(result.cols-1).setTo(cv::Scalar(0, 0, 0));

            result.row(1).setTo(cv::Scalar(0));
            result.row(result.rows-2).setTo(cv::Scalar(0, 0, 0));
            result.col(1).setTo(cv::Scalar(0));
            result.col(result.cols-2).setTo(cv::Scalar(0, 0, 0));

            result.row(result.rows-3).setTo(cv::Scalar(0, 0, 0));
            result.row(result.rows-3).setTo(cv::Scalar(0, 0, 0));
            result.col(2).setTo(cv::Scalar(0, 0, 0));
            result.col(result.cols-3).setTo(cv::Scalar(0, 0, 0));
        }
        void sharpen2d(const cv::Mat &img, cv::Mat &result)
        {
            cv::Mat kernel(3, 3, CV_32F, cv::Scalar(0));          
            kernel.at<float>(1, 1) = 5.0;
            kernel.at<float>(0, 1) = -1.0;
            kernel.at<float>(2, 1)  = 1.0;  
            kernel.at<float>(1, 0) = -1.0;
            kernel.at<float>(1, 2) = -1.0;
            // cv::filter2D(img, result, img.depth(), kernel);
        }
        double get_miliisecond(char flag) 
        {
            static double duration;
            double time = 0;
            if (!flag) {
                duration  = static_cast<double>(cv::getTickCount()); 
            } else if (flag == 1) {
                time = static_cast<double>(cv::getTickCount()) - duration;; 
                time /=cv::getTickFrequency();
            } 
            return time; 
        }
          protected:

    private:
};

    
int main(int argc, char **argv)
{
    double duration;
    Sharpen sharp;
    cv::Mat img = cv::imread("../../../data/butterfly.jpg");

    sharp.get_miliisecond(0);
    cv::namedWindow("image origin");
    cv::imshow("image origin", img);
    sharp.get_miliisecond(1);
    cout << "time cost: " << duration << endl;

    cv::Mat result;
    sharp.get_miliisecond(0);
    sharp.sharpen(img, result);
    duration = sharp.get_miliisecond(1);
    cout << "time cost: " << duration << endl;

    cv::namedWindow("image sharpen");
    cv::imshow("image sharpen", result);
    cv::waitKey(10000);
    return 0;
}
