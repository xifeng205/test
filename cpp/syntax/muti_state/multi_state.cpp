/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-05-15 13:31
 * Last modified : 2020-05-15 13:31
 * Filename      : multi_state.cpp
 * Description   : 
*********************************************************************/

#include <iostream>

using namespace std;

class Shape {
    public:
        Shape(int w, int h)
        {
            width = w;
            heigth = h;
        }
        virtual double get_area() = 0;
        // {
        //    cout << "Shape: The area is:" << endl; 
        //    return width * heigth; 
        // }

    protected:
        double width;
        double heigth;
    private:
};

class Rectangle: public Shape {
    public:
        Rectangle(double w, double h):Shape(w, h){};
        double get_area()
        {
            cout <<"Rectangle: The area is:"  << endl;            
            return width * heigth;
        }

    protected:

    private:
};

int main(int argc, char **argv)
{
    Rectangle ret(10, 29);
    double area = ret.get_area();
    cout << area << endl; 
    return 0;
}
