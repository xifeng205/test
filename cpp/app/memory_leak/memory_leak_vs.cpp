/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-07-27 14:51
 * Last modified : 2020-07-27 14:51
 * Filename      : memory_leak.cpp
 * Description   : 
 *********************************************************************/
#define CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
//在入口函数中包含 _CrtDumpMemoryLeaks();
//即可检测到内存泄露

//定义函数：
inline void EnableMemLeakCheck()
{
    _CrtSetDbgFlag(_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) | _CRTDBG_LEAK_CHECK_DF);
}
//该函数可以放在主函数的任意位置，都能正确的触发内存泄露输出


//以如下测试函数为例：
int main()
{
    EnableMemLeakCheck();
    char* pChars = new char[10];
    //_CrtDumpMemoryLeaks();
    return 0;
}


