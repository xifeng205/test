
/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-07-19 07:08
 * Last modified : 2020-07-19 07:08
 * Filename      : error.cpp
 * Description   : 
*********************************************************************/
#if __STDC__ != 1
#error "Not a standerd compliant compile!! "
#endif

#include <iostream>
#include <stdlib.h>

using namespace std;


// 1:marco name  2:line 3:# &##  4 
#define test 1

#if test  == 1
int main(int argc, char **argv)
{
    std::cout << __FILE__ << std::endl;
    std::cout << __STDC__ << std::endl;
    std::cout << __TIME__ << std::endl;
    std::cout << __func__ << std::endl;
    std::cout << __LINE__ << std::endl;
    // std::cout << __STDC_VERSION__ << std::endl;
    return 0;
}
#elif test  == 2

#include <cassert>
#define FNAME "test.cpp"

int main(int argc, char **argv)
{
#line 777 FNAME
    assert(2+2 == 5);
    return 0;
}
#elif test  == 3
#include <iostream>

// Make function factory and use it
#define FUNCTION(name, a) int fun_##name() { return a;}

FUNCTION(abcd, 12)
FUNCTION(fff, 2)
FUNCTION(qqq, 23)

#undef FUNCTION
#define FUNCTION 34
#define OUTPUT(a) std::cout << "output: " #a << '\n'

// Using a macro in the definition of a later macro
#define WORD "Hello "
#define OUTER(...) WORD #__VA_ARGS__

int main()
{
    std::cout << "abcd: " << fun_abcd() << '\n';
    std::cout << "fff: " << fun_fff() << '\n';
    std::cout << "qqq: " << fun_qqq() << '\n';

    std::cout << FUNCTION << '\n';
    OUTPUT(million);               //note the lack of quotes

    std::cout << OUTER(World) << '\n';
    std::cout << OUTER(WORD World) << '\n';
}

#elif test  == 4
int main(int argc, char **argv)
{
    return 0;
}
#else
int main(int argc, char **argv)
{
    return 0;
}
#endif
