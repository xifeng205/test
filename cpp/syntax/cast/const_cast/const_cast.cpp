/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-07-02 14:32
 * Last modified : 2020-07-02 14:32
 * Filename      : const_cast.cpp
 * Description   : 
*********************************************************************/

#include <iostream>

using namespace std;

/*
 * const_static 用法:  const_static<type_id>(expresstion)
 *
 * (1) const_static 主要用于修改类的const 和volotile 属性 
 * (2) 目标类型和元类型必须相同,可以加上const,也可以取出const属性
 *
 */

class const_b {
    private:

    protected:

    public:

};
int main(int argc, char **argv)
{
    const int a = 10;
    int b = a;

    const const_b *d = new const_b;
    const_b *e = const_cast<const_b*>(d);

    return 0;
}
