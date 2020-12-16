/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-06-15 12:25
 * Last modified : 2020-06-15 12:25
 * Filename      : c_str.cpp
 * Description   : 
*********************************************************************/

#include <iostream>

using namespace std;

int main(int argc, char **argv)
{
    string str("123456");
    const char *c_str = str.c_str();
    printf("%s", c_str);
    return 0;
}
