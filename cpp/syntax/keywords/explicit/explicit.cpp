/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-07-01 17:43
 * Last modified : 2020-07-01 17:43
 * Filename      : explicit.cpp
 * Description   : 
*********************************************************************/

#include <iostream>

using namespace std;

class Explicit {
    private:

    protected:

    public:
         int a;
         explicit Explicit(int e) {a = e;}

};
int main(int argc, char **argv)
{
    Explicit a(10);
    return 0;
}
