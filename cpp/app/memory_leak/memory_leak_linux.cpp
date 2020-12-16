/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-07-29 10:35
 * Last modified : 2020-07-29 10:35
 * Filename      : memory_leak_linux.cpp
 * Description   : 
*********************************************************************/

#include <iostream>
#include <memory>

#define test3
using namespace std;
#if defined test0
int main(){
	int *pint = new int;//动态申请内存
	*pint = 30;
	delete pint;//释放内存
	cout<<*pint<<endl;//使用野指针
	return 0;
}
#elif defined test1
int main(){
	int *pint = new int;//动态申请内存
	*pint = 30;
	delete pint;//释放内存
	delete pint;//释放内存
	cout<<*pint<<endl;//使用野指针
	return 0;
}
#elif defined test2
int main(){
	int *pint = new int;//动态申请内存
	*pint = 30;
	cout<<*pint<<endl;//使用野指针
	return 0;
}
#elif defined test3
int main(){
	int *pint = new int;//动态申请内存
	cout<<*pint<<endl;//使用野指针
    delete pint;
	return 0;
}
#endif
