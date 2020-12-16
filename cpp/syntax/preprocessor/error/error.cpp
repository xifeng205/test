/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-07-19 07:08
 * Last modified : 2020-07-19 07:08
 * Filename      : error.cpp
 * Description   : 
*********************************************************************/
// 错误指令
//
// C
//
// C 语言
//
// 预处理器
//
//
// 显示给定的错误消息，并令程序为病式。
// 语法
// #error 错误消息
// 解释
//
// 实现在遇到 #error 指令后，显示诊断消息 错误消息 ，并令程序为病式（停止编译）。
//
// 错误消息 可由多个词组成，不必在引号中。
#if __STDC__ != 1
#error "Not a standerd compliant compile!! "
#endif

#include <iostream>
#include <stdlib.h>

using namespace std;
#define test 3
#if test  == 1
int main(int argc, char **argv)
{
    std::cout << __FILE__ << std::endl;
    return 0;
}
#elif test  == 2
int main(int argc, char **argv)
{
    std::cout << __STDC__ << std::endl;
    return 0;
}
#elif test  == 3
int main(int argc, char **argv)
{
    std::cout << __TIME__ << std::endl;
    return 0;
}
#elif test  == 4
int main(int argc, char **argv)
{
    return 0;
}
#else
int main(int argc, char **argv)
{
    std::cout << __LINE__ << std::endl;
    return 0;
}
#endif
