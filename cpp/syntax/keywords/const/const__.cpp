/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-08-11 13:22
 * Last modified : 2020-08-11 13:22
 * Filename      : const__.cpp
 * Description   :
 *********************************************************************/

#include <iostream>

using namespace std;

class const_c {
private:
  const int age = 10;

public:
  void show() const { std::cout << age << std::endl; }
  void pp() { std::cout << age << std::endl; }
};

int main(int argc, char **argv) {
  const const_c const_o;
  const_o.show();
  return 0;
}
