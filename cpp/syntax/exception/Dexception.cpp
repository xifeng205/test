/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-05-16 23:24
 * Last modified : 2020-05-16 23:24
 * Filename      : selfexception.cpp
 * Description   : 
*********************************************************************/

#include <exception>
#include <iostream>

using namespace std;
 

class MyException: public exception {
    public:
        const char *what() const throw() {
            return "C++ Exception";
        }

    protected:

    private:
};

int main()
{
    try {
        throw MyException();
    } catch(MyException& e) {
        std::cout << "MyException caught" << std::endl;
        std::cout << e.what() << std::endl;
    } catch(std::exception& e) {
        //其他的错误
    }
    return 0;
}

