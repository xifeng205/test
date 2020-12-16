/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-05-13 17:38
 * Last modified : 2020-05-13 17:38
 * Filename      : rand.cpp
 * Description   : 
*********************************************************************/

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;

int main(int argc, char **argv)
{

    srand((unsigned)time(NULL));
     int j ; 
     int d =10;
    while (d--)
    {
    j = rand();
    cout << j << endl;
    }
    return 0;
}
