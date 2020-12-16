/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-07-02 11:02
 * Last modified : 2020-07-02 11:02
 * Filename      : static_cast.cpp
 * Description   : 
*********************************************************************/

#include <iostream>

using namespace std;
//static_cast usage
//static_cast <tpye_id> (expression)
//features
//Catst at compile time. type_id and expression
//Must be a pointer, alias, arithmetic types, or enumeration types
///用算符主要有如下几种用法：
//（1）
//用于类层次结构中，基类和派生类指针或别名之间的转换，对于类只能在有联系的类之间进行转换
// 将基类转换为派生类是不安全的,将派生类转换为基类是安全的
//（2)
//用于基本类型之间的数据转换
//（3）将空指针转换为目标类型的空指针
//（4）可以将任何类型的表达式转换为void型

class static_b {
    private:
        int a;
    protected:

    public:
        static_b(int b = 3):a(b){
            cout << a << endl;
        }
        void pt()
        {
            cout << "base class" << endl;
        }

};

class static_d :public static_b {
    private:
        int b;
    protected:

    public:
        static_d(int e =20) : b(e){
            cout << b << endl;
        }
        void pt2()
        {
            cout << "derive class" << endl;
        }

};
int main(int argc, char **argv)
{
    int a = 10;
    char b= 9;
    float c = 10.1;
    char *d;

    a = static_cast<int>(c);

    cout << a << endl;
    cout << c << endl;

    static_b *sb;
    static_d *sd;
    
    sb = static_cast<static_b*>(sd);
    sb->pt();
    
    sd = static_cast<static_d*>(sb);
    sd->pt2();
    return 0;

}
