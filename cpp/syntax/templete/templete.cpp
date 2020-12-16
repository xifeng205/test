/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-05-17 10:45
 * Last modified : 2020-05-17 10:45
 * Filename      : templete.cpp
 * Description   : 
*********************************************************************/

#include <cstdio>
#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

#define T_CLASS

#if defined T_FUNCTION

template <typename T>
inline T add(T a, T b) {
    return a + b;
}
int main(int argc, char **argv) {
    int c = add(1, 3);
    double d = add(1.99, 3.999);
    cout << d << endl;
    return 0;
}

#elif defined T_CLASS

template <class T>
class stack_c {
    private:
        vector<T> m_stack;
    public:
       void pop();
       push(const T& element); 
};

template <class T>
void stack_c<T>::pop() {
    
}
template <class T>
void stack_c<T>::push(const T& element) {

}
int main(int argc, char **argv)
{
     
    return 0;
}
#endif
