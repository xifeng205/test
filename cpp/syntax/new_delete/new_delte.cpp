/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-05-29 15:05
 * Last modified : 2020-05-29 15:05
 * Filename      : new_delte.cpp
 * Description   : 
*********************************************************************/

#include <iostream>

using namespace std;
#define TEST
#if defined ARRY
class Box {
    public:
    Box() {
        cout << "hellow world" <<endl;
    }
    ~Box() {
        cout << "bye bye" <<endl;
    }
    protected:

    private:
};

int main(int argc, char **argv)
{
    Box *array = new Box[4];  
    delete [] array;

    int m = 10, n = 10, h = 10;
    int ***a = new int**[m];
    for (int i=0; i<m; ++i){
        a[i]  = new int *[n];
        for(int j = 0; j<n; ++j) {
            a[i][j] = new int[h];
        } 
    }

    for (int i=0; i<n; ++i) {
        for (int j=0; j<m; ++j) {
            for (int k=0; k<h; ++k) {
               a[i][j][k] = i+j+k; 
               
               cout << a[i][j][k] << "";
            }
            cout <<endl;
        }
    }

    for ( int i=0; i<m; ++i) {
        for (int j=0; j<m; ++j)
            delete [] a[i][j];
    }
    for (int i=0; i<m; ++i) delete [] a[i];
    delete [] a;

    return 0;
}
#elif defined TEST1
int main(int argc, char **argv)
{
    int *arr = new int[20]{1, 2};
    
    // for (int i=0; i < 20; ++i) arr[i] = i;
    for (int i=0; i < 20; ++i) std::cout << arr[i];
    std::cout << std::endl;
    return 0;
}
#elif defined TEST
int main(int argc, char **argv)
{
    int *var = new int(1);
    int *var1 = new int{1};
    std::cout << *var << std::endl;
    std::cout << *var1 << std::endl;
    return 0;
}
#endif
