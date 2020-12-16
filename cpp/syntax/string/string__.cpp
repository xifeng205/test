/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-05-23 13:41
 * Last modified : 2020-05-23 13:41
 * Filename      : string.cpp
 * Description   :
 *********************************************************************/

#include <iostream>
#include <string>
using namespace std;
#define TEST1
#if defined TEST0
int main(int argc, char **argv) {
  string s2("12344");
  cout << s2 << endl;

  string s3(3, '5');
  cout << s3 << endl;

  string s4("hellow world", 3, 5);
  cout << s4 << endl;

  string s5("12345"), s6;
  cout << s5 << endl;
  s6.assign(s5);
  cout << s6 << endl;
  cout << s6.size() << endl;
  cout << s6.length() << endl;
  cout << s5.append(s4) << endl;

  string s7("12345");
  string s8("123456");
  int n = s7.compare(s8);
  cout << n << endl;

  n = s7.compare("123455");
  cout << n << endl;

  string s9 = s7.substr(3);
  cout << s9 << endl;

  string s10("hellow");
  cout << s10 << endl;
  string s11("world");
  cout << s11 << endl;
  s10.swap(s11);
  cout << s10 << endl;
  cout << s11 << endl;

  string s12("12345678");
  s12.replace(0, 9, "qwert", 2, 4);
  cout << s12 << endl;
  string s13("12345678");
  s13.replace(2, 3, 4, '0');
  cout << s13 << endl;
  string s14("12345678");
  n = s14.find('3');
  cout << n << endl;
  s14.replace(n, 1, "xxx");
  cout << s14 << endl;
  string s15("123456789");
  s15.erase(3);
  cout << s15 << endl;
  s15.erase(3, 4);
  cout << s15 << endl;
  string s16("1234567890");
  s16.insert(1, "dffd");
  cout << s16 << endl;
  string s17("123456");
  s17.insert(1, 3, 'd');
  cout << s17 << endl;

  return 0;
}
#elif defined TEST1
int main(int argc, char **argv) {
  string s;
  s = "hello world.";
  std::cout << s << std::endl;

  string s1 = "Test 2";
  cout << s1 << endl;

  s1.swap(s);
  std::cout << s1 << s << std::endl;
  string s2 = "123456789";
  s2.append(s1);
  cout << s2<< endl;

  string s17("123456");
  s17.insert(1, 3, 'd');
  cout << s17<< endl;
  string s13("12345678");
  s13.replace(2, 3, 4, '0');
  cout << s13 << endl;

  string s12("12345678");
  s12.replace(0, 9, "qwert", 2, 4);
  cout << s12 << endl;
  
  return 0;
}
#endif
