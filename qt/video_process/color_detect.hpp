#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>



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


