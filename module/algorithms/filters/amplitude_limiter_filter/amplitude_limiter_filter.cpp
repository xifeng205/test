/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-12-16 15:33
 * Last modified : 2020-12-16 15:33
 * Filename      : amplitude_limiter_filter.cpp
 * Description   : 
*********************************************************************/

#include <iostream>
#include <cstring>

using namespace std;
//1 限幅滤波法
//2 优缺点:
//(1) 优点: 能够克服偶然因素引起的脉冲干扰
//(2) 缺点: 无法抑制那种周期性的误差, 且平滑度比较差
//
template<typename T, typename N, typename L>
void amplimitude_limiter_filter(T value[], N n, L low_limit, L high_limit) {
 for(int i = 0; i< n; ++i) {
    if(value[i] < low_limit) 
      value[i] = low_limit; 
    else if(value[i] > high_limit)
      value[i] = high_limit;
 }
}

int main(int argc, char **argv) {
  int data[10]  = {0, 1, 2, 3, 4 ,5 ,6, 7, 8, 9};
  amplimitude_limiter_filter(data, 10, 3, 7);
  for(int i=0; i <10; i++)
  {
    std::cout << data[i];
  }
  std::cout << std::endl;
  return 0;
}
