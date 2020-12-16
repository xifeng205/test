/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-05-23 12:26
 * Last modified : 2020-05-23 12:26
 * Filename      : stack.cpp
 * Description   : 
*********************************************************************/

#include <iostream>
#include <stack>
using namespace std;

int main(int argc, char **argv)
{
        int n, k;
    stack <int> stk;
    cin >> n >> k;  //将n转换为k进制数
    if (n == 0) {
        cout << 0;
        return 0;
    }
    while (n) {
        stk.push(n%k);
        n /= k;
    }
    while (!stk.empty()) {
        cout << stk.top();
        stk.pop();
    }
    return 0;
}
