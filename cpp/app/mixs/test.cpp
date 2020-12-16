/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-07-28 09:58
 * Last modified : 2020-07-28 09:58
 * Filename      : test.cpp
 * Description   : 
*********************************************************************/

#include <iostream>

using namespace std;
int func() {
    int a = 10;
    int b = *&a;
    printf("%d", b);
    return b;
}

int main(int argc, char **argv)
{
    func();
    int a = 88;
    int *b = &a;
    int *&c = b;
    printf("%d", *c);

    return 0;
}
