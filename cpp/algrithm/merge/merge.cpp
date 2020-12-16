/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-07-10 13:58
 * Last modified : 2020-07-10 13:58
 * Filename      : merge.cpp
 * Description   : 
*********************************************************************/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(int argc, char **argv)
{
    int myarray0[]{1, 2, 3, 4, 5};
    int myarray1[]{6, 7, 8, 9, 10};
    std::vector<int> myvector(10);
    std::merge(myarray0, myarray0+5, myarray1, myarray1+5, myvector.begin());
    for (auto i: myvector)
        cout <<i ;
    cout << endl;

    return 0;
}
