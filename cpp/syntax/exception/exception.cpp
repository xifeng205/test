/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-05-16 21:40
 * Last modified : 2020-05-16 21:40
 * Filename      : exception.cpp
 * Description   : 
*********************************************************************/

#include <iostream>
#include <exception>

using namespace std;

#define CUSTOM_EXCEPTION
double division(int a, int b)
{
    if (b == 0) {
        throw "Division by zero condition!";
    }
    return a/b;
}
#if defined ZERO_DIVISION
int main(int argc, char **argv)
{
    int x = 50; 
    int y = 0;
    double z = 0;
    
    try {
        z = division(x, y);
        cout << z << endl; 

    } catch(const char *msg) {
        cerr << msg << endl;
    }
    return 0;
}
#elif defined  CUSTOM_EXCEPTION
struct exception_s {
    const char *what() const throw() {
        return "C++ exception."
    }
}

int main(int argc, char **argv)
{
    int x = 50; 
    int y = 0;
    double z = 0;
    
    try {
        throw my_exception_s();
    } catch (exception_s &e){
        cerr << e.what() << endl;
    }
    return 0;
}
#else

#endif

