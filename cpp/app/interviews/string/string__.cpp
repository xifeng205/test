/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-08-21 10:17
 * Last modified : 2020-08-21 10:17
 * Filename      : string__.cpp
 * Description   : 
*********************************************************************/

#include <iostream>
#include <cstring>
using namespace std;

class String {
  public:
    String(const char *str = NULL);
    String(const String &other);
    ~String(void);
    // String & operator =(const String &other);
    void operator =(const String &other);
    void pt(void) {
      std::cout << m_data << std::endl;  
    }
  private:
    char *m_data;
};
//默认构造函数
//
//普通构造函数
String::String(const char *str) {
  if (str == nullptr) {
    m_data = new char(0);
    return;
  }
  size_t str_len = strlen(str)+1;
  m_data = new char[str_len];
  memcpy(m_data, str, str_len);
}
//拷贝构造函数
String::String(const String &other) {
  size_t str_len = strlen(other.m_data)+1;
  m_data = new char[str_len];
  memcpy(m_data, other.m_data, str_len);
}
String::~String(void) {
  delete  [] m_data;
}
void String::operator=(const String &other) {
  if (&other == this) return;

  delete []m_data;
  size_t str_len = strlen(other.m_data)+1;
  m_data = new char[str_len];
  memcpy(m_data, other.m_data, str_len);
  return ;
}
//
// String &String::operator=(const String &other) {
//   if (&other == this) return *this;
//
//   delete []m_data;
//   size_t str_len = strlen(other.m_data)+1;
//   m_data = new char[str_len];
//   memcpy(m_data, other.m_data, str_len);
//   return *this;
// }
//
int main(int argc, char **argv) {
  String str1, str2, str3;
  str1 = "hllow world.";
  str2 = str1;
  str2.pt();
  return 0;
}
