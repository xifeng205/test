/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-08-10 18:22
 * Last modified : 2020-08-10 18:22
 * Filename      : convert.cpp
 * Description   : 
*********************************************************************/

#include <iostream>

using namespace std;

int main(int argc, char **argv) {
 double a = 3 / 2;
 double b = static_cast<double>(3) / 2;
 cout << a << endl;
 cout << b << endl;
 return 0;
}
