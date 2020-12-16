/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-07-28 09:23
 * Last modified : 2020-07-28 09:23
 * Filename      : endia.cpp
 * Description   : 
*********************************************************************/

#include <iostream>

using namespace std;

int main(int argc, char **argv)
{
    union endia {
        short int a;
        char b[sizeof(short int)];
    };
    endia __endia;
    __endia.a = 0x1234;

    if (__endia.b[0]==0x12 &&  __endia.b[1]==0x34)
        printf("big endia");
    else if (__endia.b[0]==0x34 &&  __endia.b[1]==0x12)
        printf("big endia");

    return 0;
}
