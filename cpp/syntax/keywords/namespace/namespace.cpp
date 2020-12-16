/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-05-17 09:33
 * Last modified : 2020-05-17 09:33
 * Filename      : namespace.cpp
 * Description   : 
*********************************************************************/

#include <iostream>
using std::cout;
using std::endl;

namespace first_space {
    void  func()
    {
        cout << "Inside first_space" << endl;            
    }
}
namespace second_space {
    void func()
    {
        cout << "Inside second_space" << endl;         
    }
}
using namespace second_space;

int main(int argc, char **argv)
{
    func();
    return 0;
}
