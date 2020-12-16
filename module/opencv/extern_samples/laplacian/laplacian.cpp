/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-06-05 10:08
 * Last modified : 2020-06-05 10:08
 * Filename      : laplacian.cpp
 * Description   : 
*********************************************************************/

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;

class Laplacianzc {
    private:
        cv::Mat img;
        cv::Mat laplace;
        int aperture;
    public:
        Laplacianzc():aperture(3){}
        void set_aperture(int a) {
            aperture = a;
        }

        cv::Mat compute_laplacian(const cv::Mat &image) {
            cv::Laplacian(image, laplace, CV_32F, aperture);
            img = image.clone();
            return laplace;
        }

        cv::Mat get_laplacian_image(double scale = -1.0) {
            if (scale < 0) {
                double lapmin, lapmax;
                cv::minMaxLoc(laplace, &lapmin, &lapmax);
                scale = 127/std::max(-lapmin, lapmax);
            } 
            cv::Mat laplace_image;
            laplace.convertTo(laplace_image, CV_8U, scale, 128);
            return laplace_image;
        }
};

int main(int argc, char **argv)
{
    cv::Mat image = cv::imread("../../../data/lena.jpg");
    cv::imshow("origin image", image);

    Laplacianzc laplacianzc;
    laplacianzc.set_aperture(7);
    cv::Mat laplace0 = laplacianzc.compute_laplacian(image);
    
    cv::Mat laplace = laplacianzc.get_laplacian_image();
    cv::imshow("laplace image0" , laplace0);
    cv::imshow("laplace image" , laplace);
    
    cv::threshold(laplace, laplace, 120, 255, cv::THRESH_BINARY_INV);
    cv::imshow("laplace threshold image" , laplace);

    cv::waitKey();

    return 0;
}
