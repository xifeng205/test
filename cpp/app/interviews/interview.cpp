/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-08-12 08:13
 * Last modified : 2020-08-12 08:13
 * Filename      : interview.cpp
 * Description   :
 *********************************************************************/

#include <cstring>
#include <iostream>
#include <iomanip>
#include <sys/time.h>

#define TEST
#if defined TEST0
using namespace std;
namespace test {
void get_memory(char **p, int n) { *p = (char *)malloc(sizeof(char) * n); }
} // namespace test

int main(int argc, char **argv) {
  char *str = nullptr;
  test::get_memory(&str, 100);
  strcpy(str, "hellow world");
  std::cout << str << std::endl;
  for (int i = 0; i < 10; ++i) {
    if (i == 6)
      std::cout << i << std::endl;
    else {
      std::cout << i + 1 << std::endl;
    }
  }
  return 0;
}
#elif defined TEST1
namespace test {
void test__() {
  char *str = (char *)malloc(100);
  free(str);
  if (str == nullptr) {
    strcpy(str, "hellow");
  } else
    strcpy(str, "heellow");
  std::cout << str << std::endl;
}
} // namespace test
int main(int argc, char **argv) {
  test::test__();
  return 0;
}
#elif defined TEST2

// (1) 以下函数输出结果是什么?
// ans: 无效的指针, 输出结果不确定

namespace test {
char *get_memory() {
  char str[] = "hellow";
  return str;
}
} // namespace test
int main(int argc, char **argv) {
  char *str = "hellow world";
  // char *str = test::get_memory();
  std::cout << str << std::endl;
  return 0;
}
#elif defined TEST3
//(2) 不调用库函数, 编写stract函数
namespace test {
void strcat(char *dst, const char *src) {
  char *dst_tmp = dst;
  const char *src_tmp = src;
  while (*dst_tmp++ != '\0');
  dst_tmp--;
  while (*src_tmp != '\0')
    *dst_tmp++ = *src_tmp++;
  *dst_tmp = '\0';
}
} // namespace test
int main(int argc, char **argv) {
  char src[10] = "hellow";
  char dst[100] = "world";

  test::strcat(dst, (const char *)src);
  std::cout << dst << std::endl;
  return 0;
}
#elif defined TEST4

int main(int argc, char **argv) {
  if (0 == '\0') std::cout << "0 =='\\0'" << std::endl;
  else std::cout << "0 != \0" << std::endl;
  return 0;
}
#elif defined TEST5

int main(int argc, char **argv) {
  int **a[3][4];
  std::cout << sizeof(a) << std::endl;
  std::cout << sizeof(int) << std::endl;
  return 0;
}
#elif defined TEST6

int main(int argc, char **argv) {
  int a[60][250][1000], i, j, k;
  
  for(k=0;k<=1000;k++)
    for(j=0;j<250;j++)
      for(i=0;i<60;i++)
        a[i][j][k]=0;
  std::cout << sizeof(a) << std::endl;
  std::cout << sizeof(int) << std::endl;
  return 0;
}
#elif defined TEST7
#define swap0(x, y) ((y) = (x) + (y), (x) = (y)  -(x), (y) = (y) - (x))
#define swap1(x, y)  decltype(x) t = y; y = x;x = t; 

int main(int argc, char **argv) {
  int x = 8, y = 9;
  std::cout << x << std::endl;
  std::cout << y << std::endl;
  swap0(x, y);
  std::cout << x << std::endl;
  std::cout << y << std::endl;
  std::cout << x << std::endl;
  std::cout << y << std::endl;
  swap1(x, y);
  std::cout << x << std::endl;
  std::cout << y << std::endl;

  return 0;
}
#elif defined TEST9
// namespace tools {
  // int do_dum(int a[], int N) {
    // for (int i = 0; i < N; ++i) {
    // } 
  // }
// }
// int main(int argc, char **argv) {

  // return 0;
// }
#elif defined TEST10
namespace tools {
unsigned int bit_invert(unsigned int x, int p, int n) {
  unsigned t1 = x <<(32 -p - n) >> (32 - p);
  unsigned t2 = x <<(32 -p - n) >> (32 - p);
  unsigned t3 = x <<(32 -p - n) >> (32 - p);
  t3 ^= t3;
  t3 <<= p;
  x = t1 | t2 | t3;
  return x;
}
}
int main(int argc, char **argv) {

  //位与为0,则表示是2的若干次幂
  // 2)return  (x>>N==1);
  int  i = 1;
  std::cout << ((i & (i - 1)) ? false : true) << std::endl; 
  int x=1;
  int y = tools::bit_invert(x, 1, 1);
  std::cout << y << std::endl;

  return 0;
}
#elif defined TEST11
int main(int argc, char **argv) {
  int x = 1;
  std::cout << "x0: " << x << std::endl;
  int y = x >> 1;
  std::cout << "y: " << y << std::endl;
  std::cout << "x1: " << x << std::endl;
  return 0;
}
#elif defined TEST
namespace tools {
  unsigned int bit_invert(unsigned int x, int p, int n) {
    unsigned int l1 = p;
    unsigned int l2 = n;
    unsigned int l3 = sizeof(x)*8 - p - n;

    unsigned int t1 = x << (l2 + l3) >> (l2 + l3);
    unsigned int t2 = x >> (l1 + l2) << (l1 + l2);
    x = ~x; 
    unsigned int t3 = x << l3 >> (l3 + l1) << l1;

    return t1 | t2 | t3;
  }
//xor^ 的作用: (1) 
  unsigned int bit_invert1(unsigned int x, int p, int n) {
    unsigned int _t = 0;
    unsigned int _a = 1;
    for(int i = 0; i < n; ++i)//循环的目的主要是-t
    {
      _t |= _a;       //位或
      _a = _a << 1;
    }
    _t = _t << p;   //转换后_t变为1110000
    x ^= _t;       //异或,将原来的位取反
      return x;
  }

double get_times(char flag = 0) {
  static struct timeval tv_start;
  static struct timeval tv_end;
  long double times = 0;
  if (!flag) {
    gettimeofday(&tv_start, NULL);
  } else if (flag == 1) {
    gettimeofday(&tv_end, NULL);
    times = (tv_end.tv_usec - tv_start.tv_usec) +
      (tv_end.tv_sec - tv_end.tv_sec) * 10000 * 1000;
    std::cout << "Cost time: " << times << " us" << std::endl;
  } else if (flag == 2) {
    gettimeofday(&tv_end, NULL);
    times = (tv_end.tv_usec - tv_start.tv_usec) / 1000 +
      (tv_end.tv_sec - tv_end.tv_sec) * 1000;
    std::cout << "Cost time: " << times << "ms" << std::endl;
  } else if (flag == 3) {
    gettimeofday(&tv_end, NULL);
    times = (tv_end.tv_usec - tv_start.tv_usec) / 1000 / 1000 +
      (tv_end.tv_sec - tv_end.tv_sec);
    std::cout << "Cost time: " << times << " s" << std::endl;
  }
  return times;
}
}

int main(int argc, char **argv) {

  unsigned int x = 0x11;
  tools::get_times(0);
  unsigned int z = tools::bit_invert1(x, 2, 3);
  z = tools::bit_invert1(x, 2, 3);
  z = tools::bit_invert1(x, 2, 3);
  z = tools::bit_invert1(x, 2, 3);
  z = tools::bit_invert1(x, 2, 3);
  z = tools::bit_invert1(x, 2, 3);
  z = tools::bit_invert1(x, 2, 3);
  z = tools::bit_invert1(x, 2, 3);
  z = tools::bit_invert1(x, 2, 3);
  z = tools::bit_invert1(x, 2, 3);
  z = tools::bit_invert1(x, 2, 3);
  z = tools::bit_invert1(x, 2, 3);
  z = tools::bit_invert1(x, 2, 3);
  z = tools::bit_invert1(x, 2, 3);
  z = tools::bit_invert1(x, 2, 3);
  z = tools::bit_invert1(x, 2, 3);
  tools::get_times(1);

  tools::get_times(0);
  unsigned int y = tools::bit_invert(x, 2, 3);
  y = tools::bit_invert(x, 2, 3);
  y = tools::bit_invert(x, 2, 3);
  y = tools::bit_invert(x, 2, 3);
  y = tools::bit_invert(x, 2, 3);
  y = tools::bit_invert(x, 2, 3);
  y = tools::bit_invert(x, 2, 3);
  y = tools::bit_invert(x, 2, 3);
  y = tools::bit_invert(x, 2, 3);
  y = tools::bit_invert(x, 2, 3);
  y = tools::bit_invert(x, 2, 3);
  y = tools::bit_invert(x, 2, 3);
  y = tools::bit_invert(x, 2, 3);
  y = tools::bit_invert(x, 2, 3);
  y = tools::bit_invert(x, 2, 3);
  y = tools::bit_invert(x, 2, 3);
  y = tools::bit_invert(x, 2, 3);
  tools::get_times(1);
  std::cout << y << std::endl;
   std::cout << z << std::endl;
  return 0;
}



#endif
