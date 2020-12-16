/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-05-14 10:11
 * Last modified : 2020-05-14 10:11
 * Filename      : class.cpp
 * Description   : 
*********************************************************************/

#include <iostream>

using namespace std;

class box {

    public: 
        box(double dim, double s1, int s2);
        // box(const box &obj);
        ~box();

        int length;
        double width;
        double height;
        double voloum;
        int st2;
        static int objcount;
        void set_length(int len);
        void set_width(double wid);
        void set_height(double hei);
        void set_ts2(int ts);
        double get_area()
        {
            return length * width;
        }
        double get_voloum();
        
        double get_dimension();
        
        friend void print_ts(box _box);
        int compare(box _box);
        // static int get_count()
        // {
            // return objcount;
        // }

    private:
        double dim;
        double st1;
};

box::box(double dimension, double s1, int s2):st1(s1), st2(s2)
{
    cout << "Creat a box object!" << endl;
    dim = dimension;
    cout << st1 << endl;
    cout << st2 <<endl;
    // objcount ++;
}

box::~box()
{
    cout << "Delete a box object!" << endl;
}

void box::set_ts2(int ts)
{
    st2 =ts;
}
int box::compare(box _box)
{
    return   this->st2 > _box.st2;
}

double box::get_dimension()
{
    return dim;
}

void box::set_height(double hei)
{
    height = hei;
}

void box::set_length(int len)
{
    length = len;
}

void box::set_width(double wid)
{
    width = wid;
}

double box::get_voloum()
{
    return length * width * height;
}

void print_ts(box _box)
{
    cout << "box.ts2:" << _box.st2 << endl;
}

// static box::objcount = 0;

int main(int argc, char **argv)
{
    box mybox(8.8, 2, 3);
    mybox.set_width(8);
    mybox.set_length(8.8);
    mybox.set_height(2.2);

    double area = mybox.get_area();
    cout << area << endl;
    double voloum = mybox.get_voloum();
    cout << voloum << endl;
    double dim = mybox.get_dimension();
    cout << "dim:" << dim << endl;
    print_ts(mybox);
    box mybox2 = mybox;
    mybox2.set_ts2(9);
    int ret = mybox.compare(mybox2);
    cout << "ret:" << ret << endl;
    mybox2.set_ts2(0);
    ret = mybox.compare(mybox2);
    cout << "ret:" << ret << endl;
    box *pbox = &mybox;
    cout << "pboxt->ts2:" << pbox->st2 << endl; 
    pbox->set_ts2(19);
    cout << "pboxt->ts2:" << pbox->st2 << endl; 
    return 0;
}
