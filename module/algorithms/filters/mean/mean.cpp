/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-12-16 18:15
 * Last modified : 2020-12-16 18:15
 * Filename      : mean.cpp
 * Description   :
 *********************************************************************/

#include <iostream>

using namespace std;

template <typename T, typename L> T mean(T data[], L len) {
  T sum = 0;
  for (int i = 0; i < len; ++i) {
    sum += data[i];
  }
  return sum / len;
}

int main(int argc, char **argv) {
  double data[4] = {1.3, 3.0, 4, 5};
  auto ave = mean(data, 4);
  std::cout << ave << std::endl;
  return 0; }
