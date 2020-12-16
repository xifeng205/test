/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-07-18 10:33
 * Last modified : 2020-07-18 10:33
 * Filename      : nullptr.cpp
 * Description   : 
 *********************************************************************/
#include <iostream>
using namespace std;
void isnull(void *c){
    cout << "void*c" << endl;
}
// void isnull(int n){
    // cout << "int n" << endl;
// }
int main() {
    isnull(0);
    isnull(nullptr);
    return 0;
}
