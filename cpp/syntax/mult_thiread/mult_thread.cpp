/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-05-17 12:54
 * Last modified : 2020-05-17 12:54
 * Filename      : mult_thread.cpp
 * Description   : 
*********************************************************************/

#include <iostream>
#include <vector>
using namespace std;

int main(int argc, char **argv)
{
    vector<int> vec;

    int i;

    cout << "vector:" << vec.size() << endl;
    for (i = 0; i<5; i++) {
        vec.push_back(i);
    }    
    cout << "extend vector:" << vec.size() << endl;
    for (i = 0; i < 5; i++) {
        cout << "extend vector:" << vec[i] << endl;
    }
    vector<int>::iterator v = vec.begin();
    while (v != vec.end()) {
        cout << "value of v = " << *v <<endl;
        v++;
    }
        
    return 0;
}
