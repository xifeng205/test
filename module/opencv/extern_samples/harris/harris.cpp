/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-06-06 10:12
 * Last modified : 2020-06-06 10:12
 * Filename      : harris.cpp
 * Description   : 
*********************************************************************/

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
class Harrisdectector {
    private:
        cv::Mat corner_strength;
        cv::Mat cornerth;
        cv::Mat local_max;
        int neighbourhood;
        int aperture;
        double k;
        double max_strength;
        double threshold;
        int non_max_size;
        cv::Mat kernel;
    public:
        Harrisdectector():neighbourhood(3), aperture(3),
        k(0.01), max_strength(0.0), threshold(0.01), 
        non_max_size(3) {
            
        }
        void detect(const cv::Mat &image) {
            cv::cornerHarris(image, corner_strength,
            neighbourhood, aperture, k);

            double min_strength;
            cv::minMaxLoc(corner_strength, &min_strength, 
                    &max_strength);
            cv::Mat dilated;
            cv::dilate(corner_strength, dilated, cv::Mat());
            cv::compare(corner_strength, dilated, 
                    local_max, cv::CMP_EQ);
        } 

};

int main(int argc, char **argv)
{
    cv::Mat image = cv::imread("../../../data/lena.jpg", 0);

    cv::Mat corner;
    cv::cornerHarris(image, corner, 3, 3, 0.01);

    cv::Mat harrisCorners;
    double threshold = 0.0001;
    cv::threshold(corner, harrisCorners,
            threshold, 255, cv::THRESH_BINARY_INV); 

    cv::imshow("harris image", harrisCorners);

    cv::waitKey();
    return 0;
}
