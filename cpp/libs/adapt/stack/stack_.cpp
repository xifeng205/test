/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-08-05 07:00
 * Last modified : 2020-08-05 07:00
 * Filename      : stack_.cpp
 * Description   : 
*********************************************************************/

#include <iostream>
#include <stack>
#include <deque>

using namespace std;
int main(int argc, char **argv)
{
    deque<int> deque__ {1, 2,  4 , 4};
    stack<int> mystack(deque__);
    while (!mystack.empty()) {
	    std::cout << mystack.top() << std::endl;
        mystack.pop();
    }
    return 0;
}
