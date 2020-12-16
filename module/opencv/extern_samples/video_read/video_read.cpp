/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-06-06 15:58
 * Last modified : 2020-06-06 15:58
 * Filename      : video_read.cpp
 * Description   : 
*********************************************************************/

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/videoio/legacy/constants_c.h>
#include <sys/types.h>

using namespace std;

class Videoprocessor {
    private:
        cv::VideoCapture capture; 
        void (*process)(cv::Mat &, cv::Mat &);
        bool call_it;
        std::string window_name_input;
        std::string window_name_output;
        int delay;
        long fnumber;
        long frame_to_stop;
        bool stop;
    public:
        Videoprocessor():call_it(true), delay(0), fnumber(0), stop(false), 
        frame_to_stop(-1) {}
        void set_frame_processor(
                void (*frame_processing)(cv::Mat &, cv::Mat &)) {
            process = frame_processing;
        }

        bool set_input(std::string file_name) {
            fnumber = 0;
            capture.release();
            // images.clear();
            return capture.open(file_name);
        }
        void display_input(std::string wn) {
            window_name_input = wn;
            cv::namedWindow(window_name_input);
        }
        void display_out(std::string wn) {
            window_name_output = wn;
            cv::namedWindow(wn);
        }
        void dont_display() {
            cv::destroyWindow(window_name_input);
            cv::destroyWindow(window_name_output);
            window_name_input.clear();
            window_name_output.clear();
        }
        void process_frame(cv::Mat &img, cv::Mat &out) {
            canny(img, out); 
        }
        void canny(cv::Mat &img, cv::Mat &out)
        {
            // if (img.channels() == 3)
                // cv::cvtColor(img. out. CV_BGR2GRAY);
            cv::Canny(out, out, 100, 200);
            cv::threshold(out, out, 128, 255, cv::THRESH_BINARY_INV);
        }
        void run() {
            cv::Mat frame;
            cv::Mat output;
            if (!is_opened()) return;
            stop = false;
            while (!is_stopped()) {
               if (window_name_input.length() != 0) {
                    cv::imshow(window_name_input, frame);
               } 
               if (call_it) {
                    process(frame, output);
                    fnumber++;
               } else output = frame;
               if (window_name_output.length() != 0) 
                   cv::imshow(window_name_output, output);
               if (delay >= 0&& cv::waitKey(delay) >= 0) 
                   stop_it();
               if (frame_to_stop >= 0 &&
                       get_frame_number() == frame_to_stop)
                   stop_it();
            }
        }
        void stop_it() {
            stop = true;
        }
        bool is_stopped() {
            return stop;
        }
        bool is_opened() {
            return capture.isOpened();
        }
        void set_delay(int d) {
            delay = d;
        }
        bool read_next_frame(cv::Mat &frame) {
            return capture.read(frame);
        }
        void call_process() {
            call_it = true;
        }
        void dont_call_process() {
            call_it = false;
        }
        long get_frame_number() {
            long frame_number = static_cast<long>(
                    capture.get(CV_CAP_PROP_POS_FRAMES));
            return frame_number;
        }

};
int main(int argc, char **argv)
{
    // cv::VideoCapture capture("../../../data/tree.avi");
    // cv::VideoCapture capture("/dev/video0");
    // if (!capture.isOpened())
    //     return 1;
    //
    // double rate = capture.get(CV_CAP_PROP_FPS);
    // bool stop(false);
    //
    // cv::Mat frame;
    //
    // int delay = 1000/rate;
    // while (!stop) {
    //     if (!capture.read(frame)) break;
    //     cv::imshow("vidoe ", frame);
    //     if (cv::waitKey(delay) >=0) stop = true;
    //     
    // }
    //
    return 0;
}
