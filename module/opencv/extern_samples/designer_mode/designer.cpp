/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-06-01 11:23
 * Last modified : 2020-06-01 11:23
 * Filename      : designer.cpp
 * Description   : 
 *********************************************************************/

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

// #include "designer.hpp"

using namespace std;

class Color_detector {
    public:
        Color_detector():mini_dist(100) {
            target[0] = target[1] = target[2] = 0;
        }

        int get_distance(const cv::Vec3b &color) {
            return abs(
                    color[0] - target[0] +
                    color[1] - target[1] + 
                    color[2] - target[2]);
        }

        // int get_distance(const cv::Vec3b &color) {
        //     return static_cast<int>(cv::norm<int, 3>(cv::Vec3i(color[0]-target[0],
        //                     color[1]-target[1], color[2]-target[2])));
        // }

        cv::Mat process(cv::Mat &image) {
            result.create(image.rows, image.cols, CV_8U);

            cv::Mat_<cv::Vec3b>::const_iterator it = 
                image.begin<cv::Vec3b>();
            cv::Mat_<cv::Vec3b>::const_iterator it_end = 
                image.end<cv::Vec3b>();
            cv::Mat_<uchar>::iterator it_out = 
                result.begin<uchar>();

            for (; it != it_end; ++it, ++it_out) {
                if (get_distance(*it) < mini_dist) {
                    *it_out = 255;
                } else {
                    *it_out = 0;
                }
            } 
            return result;
        }

        void set_color_distance_threshold(int distance) {
            if (distance < 0) {
                distance= 0;    
            }
            mini_dist = distance;
        }

        void set_target_color(unsigned char red, unsigned char green,
                unsigned char blue) {
            target[2] = red;
            target[1] = green;
            target[0] = blue;
        }

        cv::Vec3b get_target_color() const {
            return target;
        }

    protected:

    private:
        int mini_dist;

        cv::Vec3b target;
        cv::Mat result;
};

class Color_detector_ctrl {
    public:
        static Color_detector_ctrl *get_instance() {
            if (!singleton) {
                singleton = new Color_detector_ctrl();
            }
            return singleton;
        }

        void destory() {
           if (singleton) {
                delete singleton; singleton = NULL;} 
        }
        
        void set_color_distance_threshold(int distance) {
            cdetect->set_color_distance_threshold(distance); 
        }

        int get_color_distance_threshold() const{
           // return cdetect->get_color_distance_threshold(); 
           return 1;
        } 
        
        void set_target_color(unsigned char red,
                unsigned char green, unsigned char blue) {
            cdetect->set_target_color(red, green, blue);
        }

        void get_target_color(unsigned char &red,   
                unsigned char &green, unsigned char &blue) {
            cv::Vec3b color = cdetect->get_target_color();
            red = color[2];
            green = color[1];
            blue = color[0];
        }

        bool set_input_image(std::string filename) {
            image = cv::imread(filename);
            if (!image.data) return false;
            else return true;
        }

        cv::Mat get_input_image() {
            return image;
        }

        void process() {
            result = cdetect->process(image);
        }

       const cv::Mat get_last_result() const {
            return result;
        } 

       ~Color_detector_ctrl() {
            delete cdetect;
       }
    protected:
        
    private:
        static Color_detector_ctrl *singleton;
        Color_detector *cdetect;
        
        Color_detector_ctrl() {
            cout <<"new color_cdetector;" << endl;
            cdetect = new Color_detector();
        }
        cv::Mat image;
        cv::Mat result;
};

Color_detector_ctrl *Color_detector_ctrl::singleton  = NULL;

int main(int argc, char **argv)
{
    Color_detector_ctrl::get_instance()->set_input_image("../../../data/butterfly.jpg");
    cv::imshow("image input",   
            Color_detector_ctrl::get_instance()->get_input_image());

    Color_detector_ctrl::get_instance()->set_target_color(130, 190, 230);
    Color_detector_ctrl::get_instance()->process();
    cv::imshow("image output", 
            Color_detector_ctrl::get_instance()->get_last_result());

    cv::waitKey(0);
    return 0;
}
