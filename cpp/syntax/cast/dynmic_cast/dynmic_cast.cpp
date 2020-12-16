/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-07-02 12:40
 * Last modified : 2020-07-02 12:40
 * Filename      : dynmic_cast.cpp
 * Description   : 
*********************************************************************/

#include <exception>
#include <iostream>

using namespace std;

/*
   用法：dynmic_cast<tpye_id>(expression)

   (0)在运行时转换，检查转换的安全性，如果未执行转换，则转换失败
   expression表达式置为0；

   (1) 用于相关联基类与派生类的转换， 下行转换时要求基类必须 要有
   一个虚函数。tpye_id 和expression 必须是类的 指针， 类的引用或者
   void *, 如果typeid 是指针，则expression也是指针，如果type_id 是
   引用， 则expression 也是引用,

 */

class dynamic_b {
    private:
        int a;
    protected:

    public:
        dynamic_b(int a_=10) : a(a_) {
            cout << "basic class" << endl;
        }
        void pt()
        {
            cout << "basic class" << endl;
        }
        virtual void f(void){
        }
};

class dynamic_d :public dynamic_b {
    private:
        int d;
    protected:

    public:
        dynamic_d(int d_=10) :d(d_) {
            cout << "derive class"<< endl;
        }
        void pt1()
        {
            cout << "derive class"<< endl;
        }

};

class dynamic_o {
    private:

    protected:
    
    public:
        virtual void f(){}
};
int main(int argc, char **argv)
{
    dynamic_b *db = new dynamic_b; 
    cout << db << endl;
    dynamic_d *dd = dynamic_cast<dynamic_d*>(db);
    cout << dd << endl;
    try {
        dynamic_b *b0 = new dynamic_d(10);
        dynamic_b *b1 = new dynamic_b(20);
        dynamic_d *d0;

        d0 = dynamic_cast<dynamic_d*>(b0);
        if (d0) cout << "first conversion" << endl;
        d0 = dynamic_cast<dynamic_d*>(b1);
        if (d0) cout << "second converdion" << endl;

    }catch(exception &e) {
        cout << "excepion:" << e.what() << endl;
    }


    return 0;
}
