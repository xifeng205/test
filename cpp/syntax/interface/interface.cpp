/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-07-31 18:17
 * Last modified : 2020-07-31 18:17
 * Filename      : interface.cpp
 * Description   : 
*********************************************************************/

#include <iostream>

using namespace std;

class line_c {
    public:
        double height;
        double width;
        virtual double get_area() = 0; 
};

class rect_c:public line_c  {

    public:
        double get_area() {
            return width * height;
        }

};
int main(int argc, char **argv)
{
    rect_c rect;
    return 0;
}
