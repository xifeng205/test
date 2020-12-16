/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-06-10 16:29
 * Last modified : 2020-06-10 16:29
 * Filename      : application.cpp
 * Description   : OpenCV Application Tracing support demo
*********************************************************************/

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/video/video.hpp>
#include <opencv2/core/utils/trace.hpp>

using namespace std;
using namespace cv;

static void process_frame(const cv::UMat &frame) {
    // CV_TRACE_FUNCTION();        
    cv::UMat gray, processed;
  cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
    cv::Canny(gray, processed, 32, 64, 3);
    cv::imshow("process frame", processed);

}

int main(int argc, char **argv) {
    // CV_TRACE_FUNCTION();

    cv::CommandLineParser parser(argc, argv, 
            "{help h ? |     | help message}"
            "{n        | 100 | number of frames to process}"
            "{@video   | 0   | video filename or cameraID}"
            );
    if (parser.has("help")) {
        parser.printMessage();
        return 0;
    }
    cv::VideoCapture capture;

    string video = parser.get<string>("@video");
    if (video.size() == 1 && isdigit(video[0])) {
        capture.open(parser.get<int>("@video"));        
    } else {
        capture.open(cv::samples::findFileOrKeep(video));
    }
    int nframes = 0;
    if (capture.isOpened()) {
        nframes = (int)capture.get(cv::CAP_PROP_FRAME_COUNT);
        cout << "Video" << video << 
            ":width:" << capture.get(cv::CAP_PROP_FRAME_WIDTH)<<
            ",heigth:" << capture.get(cv::CAP_PROP_FRAME_COUNT)<<
            ",frame" << nframes << endl;
    } else {
        cout << "Could not intialize video capturing...\n" <<endl;
        return -1;
    } 
    int N = parser.get<int>("n"); 
    if (nframes > 0 && N > nframes) {
        N = nframes;        
    }
    cout << "Start processing..." << endl
        << "Press ESC key to terminate" << endl;

    cv::UMat frame;
    for (int i=0; N > 0 ? (i < N) : true; ++i) {
        // CV_TRACE_FUNCTION("FRAME");       
        // {
            // CV_TRACE_REGION("read");
            capture.read(frame);
            if (frame.empty()){
                cout << "Can't capture frame:" << i << endl;
                break;
            }
        // }
        // CV_TRACE_REGIN_NEXT("process");
        process_frame(frame);
        // CV_TRACE_REGION_NEXT("delay");
        if (cv::waitKey(1) == 27) break;
    }

    return 0;
}

