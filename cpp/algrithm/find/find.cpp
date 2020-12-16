/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-07-10 14:55
 * Last modified : 2020-07-10 14:55
 * Filename      : find.cpp
 * Description   : 
*********************************************************************/

#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

int main(int argc, char **argv)
{
    char str[] = "hellow world";
    char *find_p = find(str, str+strlen(str), 'w');
    if (find_p != str+strlen(str))
        cout << find_p << endl;
    else cout << "Not find!" << endl;

    std::vector<int> myvector{1,3,4, 5, 5, 6, 3, 6, 9};
    std::vector<int>::iterator it = find(myvector.begin(), myvector.end(), 9);
    if (it != myvector.end()) std::cout << *it << endl;


    return 0;
}
