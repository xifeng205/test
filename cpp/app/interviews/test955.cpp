/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-08-19 20:02
 * Last modified : 2020-08-19 20:02
 * Filename      : test955.cpp
 * Description   :
 *********************************************************************/

#include <array>
#include <iostream>

using namespace std;
namespace test {
void bubble_sort(int x[], int n) {
  int i, j;
  int temp;
  for (i = 0; i < n; i++)
    for (j = 0; j < n -1 - i; j++) {
      if (x[j] > x[j + 1]) {
        temp = x[j];
        x[j] = x[j + 1];
        x[j + 1] = temp;
      }
    }
}
} // namespace test
int main(int argc, char **argv) {
  int arr[10] = {1, 3, 2, 4, 5, 6, 7, 8};
  test::bubble_sort(arr, 9);
  for (int i = 0; i < 9; ++i)
  std::cout << arr[i] << std::endl;
  return 0;
}
