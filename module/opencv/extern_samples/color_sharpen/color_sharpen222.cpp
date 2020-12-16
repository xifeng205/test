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
#include <pthread.h>

#define NUM_THREAD 2

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

class Pthread {
    public:
        // int num_threads;
        // pthread_t tids[num_threads];
        // pthread_attr_t attr_init[num_threads];
        // void *(*thx_funcs[num_threads])(void *arg);

        void *status;

        Pthread(int n=1){};
        void pthread_fill_process(void *(*func_array[])(void *arg),
                void *(*thx_func)(void *arg), int index)
        {
            int i = index;
            func_array[i] = thx_func;
        }
        // void pthread_fill_data(void **data int index)
        // {
        //     int i = index;
        //     func_array[i] = thx_func;
        // }
        //
        void pthread_creats(pthread_t *tids, 
                void *(*thx_funcs[])(void *), void **data, int num_threads)
        {
            for (int i=0; i<num_threads; ++i) {
                // pthread_attr_init(&attr_init[i]);
                // pthread_attr_setdetachstate(&attr_init[i], PTHREAD_CREATE_JOINABLE);
            }
            for (int i=0; i<num_threads; ++i) {
                pthread_create(&tids[i], NULL,  thx_funcs[i], data[i]);   
            }
        }
        void pthread_joins(pthread_t *tids, int num_threads)
        {
            for (int i=0; i<num_threads; ++i) {
                int res = pthread_join(tids[i], &status);   
                if (res) {
                    cout << "pthread_join err!!"<< endl;
                    exit(-1);
                }
            }           
        }
        
    protected:

    private:
};
void *thx_func0(void *arg)
{   
    Sharpen sharp;
   int a = *(int  *)(arg);
   cout << a << endl;
    // cv::Mat img = cv::imread("../../../data/butterfly.jpg");
    // cv::Mat result;
    // sharp.get_miliisecond(0);
    // sharp.sharpen(img, result);
    // double duration = sharp.get_miliisecond(1);
    // cout << "cost: " << duration << endl;

    // cv::namedWindow("image origin");
    // cv::imshow("image origin", img);
//
    // cv::waitKey(100);
    return NULL;
}
void *thx_func1(void *arg)
{
   int a = *(int  *)(arg);
   cout << a << endl;
    //
    // Sharpen sharp;
    // cv::Mat img = cv::imread("../../../data/butterfly.jpg");
    // // cv::Mat img = *(cv::Mat *)arg;
    // cv::Mat result;
    // sharp.get_miliisecond(0);
    // sharp.sharpen(img, result);
    // double duration = sharp.get_miliisecond(1);
    // cout << "time cost: " << duration << endl;
    //
    // cv::namedWindow("image sharpen");
    // cv::imshow("image sharpen", result);
    //
    // cv::waitKey(1000);
    return NULL;
}

int main(int argc, char **argv)
{
    int *data[2];
    int c=1, d=3;
    data[0]=&c;
    data[1]=&d;

    Pthread pthread;
    pthread_t tids[NUM_THREAD];
    void *(*thx_funcs[NUM_THREAD])(void *arg);

    pthread.pthread_fill_process(thx_funcs, thx_func0, 0);
    pthread.pthread_fill_process(thx_funcs, thx_func1, 1);
    pthread.pthread_creats(tids, thx_funcs,(void **)data, NUM_THREAD);
    pthread.pthread_joins(tids, NUM_THREAD);
    return 0;
}
