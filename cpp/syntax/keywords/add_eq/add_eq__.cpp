/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-08-08 15:53
 * Last modified : 2020-08-08 15:53
 * Filename      : add_eq__.cpp
 * Description   : 
*********************************************************************/

#include <iostream>
#include <bitset>
using namespace std;

int main(int argc, char **argv) {
 std::bitset<4>mask{"0011"};
 std::bitset<4> val{"0100"};
 val and_eq mask;
 std::cout << val << std::endl;
 return 0;
}
