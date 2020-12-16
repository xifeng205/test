/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-05-26 20:50
 * Last modified : 2020-05-26 20:50
 * Filename      : colo_reduce.cpp
 * Description   : 
*********************************************************************/

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>


using namespace std;

void color_reduce(cv::Mat &img, int div = 64)
{
    int nl = img.rows;
    cout << nl << endl;
    int nc = img.cols * img.channels();
    cout << nc << endl;

    for (int j=0; j<nl; ++j) {
        uchar *data = img.ptr<uchar>(j);
        for (int i = 0; i<nc; ++i) {
            data[i] = data[i]/div*div+div/2;  
        }
    }
}
void color_reduce1(cv::Mat &img, int div = 64)
{
    int nl = img.rows;
    int nc = img.cols * img.channels();

    for (int j=0; j<nl; ++j) {
        uchar *data = img.ptr<uchar>(j);
        for (int i = 0; i<nc; ++i) {
            data[i] = data[i] -data[i]%div +div/2;  
        }
    }
}
void color_reduce2(cv::Mat &img, int div = 64, int n = 6)
{
    int nl = img.rows;
    cout << nl << endl;
    int nc = img.cols * img.channels();
    cout << nc << endl;
    uchar mask = 0xFF << n;
    for (int j=0; j<nl; ++j) {
        uchar *data = img.ptr<uchar>(j);
    for (int i = 0; i<nc; ++i) {
        data[i] = data[i]&mask +div/2;  
        }
    }
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
        
void color_reduce3(cv::Mat &img, cv::Mat &result, int div)
{
    int nl = img.rows;
    int nc = img.cols * img.channels();

    result.create(img.rows, img.cols, img.type());
    
    for (int j=0; j<nl; ++j) {
        uchar *data_in = img.ptr<uchar>(j);
        uchar *data_out = result.ptr<uchar>(j);
        for (int i=0; i<nc; ++i) {
            data_out[i] = data_in[i]/div*div + div/2;  
        }
    }
}

int main(int argc, char **argv)
{
    cv::Mat image;
    image = cv::imread("../../../data/butterfly.jpg");
    get_miliisecond(0);
    color_reduce(image, 64);
    get_miliisecond(1);
    get_miliisecond(0);
    color_reduce3(image, image, 64);
    get_miliisecond(1);
    cv::namedWindow("color reduce");
    cv::imshow("color reduce", image);
    cv::waitKey(10000);

    return 0;
}
