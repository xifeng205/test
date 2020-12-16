/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-07-18 11:31
 * Last modified : 2020-07-18 11:31
 * Filename      : unique_ptr.cpp
 * Description   : 
*********************************************************************/

#include <iostream>
#include <memory>

using namespace std;

int main(int argc, char **argv)
{
    std::unique_ptr<int> p1;
    std::unique_ptr<int> p2(nullptr);
    std::unique_ptr<int> p3(new int);
    std::unique_ptr<int> p4(new int(10));
    std::unique_ptr<int> p5(std::move(p4));
    
    std::cout << *p5 << std::endl;
    int *p = p5.release();
    if (p5) std::cout << "no nullprt" << std::endl;
    else std::cout << "nullptr" << std::endl;

    p1.reset(p);
    if (p1) std::cout << "no nullprt" << std::endl;
    else std::cout << "nullptr" << std::endl;
    std::cout << *p1 << std::endl;

    return 0;
}
