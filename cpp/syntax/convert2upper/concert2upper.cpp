/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-07-15 20:22
 * Last modified : 2020-07-15 20:22
 * Filename      : concert2upper.cpp
 * Description   : 
*********************************************************************/

#include <iostream>

using namespace std;
class A {
    private:
        int a_a;
    public:
        A(int a) :a_a(a) {}
        void display() {std::cout << "A: " << a_a << std::endl;}
};
 
class B: public A {
    private:
        int b_b;
    protected:

    public:
        B(int a, int b): A(a), b_b(b) {}
        void display() {std::cout << "B: " << b_b << std::endl;}
};
class C {
    private:
        int c_c;
    public:
        C(int a) :c_c(a) {}
        virtual void display() {std::cout << "C: " << c_c << std::endl;}
};
 
class D: public C {
    private:
        int d_d;
    protected:

    public:
        D(int a, int b): C(a), d_d(b) {}
        void display() {std::cout << "D: " << d_d << std::endl;}
};

int main(int argc, char **argv)
{
    A a(10);
    a.display();
    
    B b(10, 20);
    b.display();

    A *c = new A(10);
    B *e = new B(3, 4);
    A *f = e;
    f->display();

    C *h = new C(10);
    D *g = new D(8, 7);
    C *j = g;
    j->display();

    return 0;
}
