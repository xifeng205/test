/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-08-20 11:37
 * Last modified : 2020-08-20 11:37
 * Filename      : test987.cpp
 * Description   : 
*********************************************************************/

#include <iostream>

using namespace std;
namespace test {
  template <typename T>
    void loop_move(T arr, int n) {
       
    }
}
int main(int argc, char **argv) {
  int arr[10] = {1, 2,3, 54, 8};
  test::loop_move(arr, 2);
  std::cout << arr << std::endl;
 return 0;
}
