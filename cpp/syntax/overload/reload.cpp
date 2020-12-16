/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-05-15 11:30
 * Last modified : 2020-05-15 11:30
 * Filename      : reload.cpp
 * Description   : 
*********************************************************************/

#include <iostream>

using namespace std;

class Print {
    public:
        int a;

        void print(int p);
        void print(double p);
        void print(char *p);

        Print operator+(Print pt)
        {
            Print ptmp;
            ptmp.a = this->a + pt.a;
            return ptmp;
        }
};

void Print::print(int p)
{
    cout << p << endl;
}

void Print::print(double p)
{
    cout << p << endl;
}

void Print::print(char *p)
{
    cout << p << endl;
}

int main(int argc, char **argv)
{
    Print pt;
    Print pt1;
    pt.print(18);
    pt.print(19.9);
    char str[]= "hellow worls";
    pt.print(str);

    pt.a = 1;
    pt1.a = 2;

    Print pt2 = pt + pt1;
    pt.print(pt2.a);

    return 0;
}

