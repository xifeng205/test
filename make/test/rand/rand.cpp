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

using namespace std;

int main(int argc, char **argv)
{
    srand((unsigned)time(NULL));
    int j = rand();
    cout << j << endl;

    return 0;
}
