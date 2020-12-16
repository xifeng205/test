/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-07-28 15:53
 * Last modified : 2020-07-28 15:53
 * Filename      : string.cpp
 * Description   : 
*********************************************************************/

#include <iostream>
#include <cstring>

using namespace std;

class String  {
    private:
        char *str_data;
    public:
        String(const char *str);
        String(const String &other_obj);
        String &operator=(const String &other_obj);
        ~String();
};
String::String(const char *str) {
    if (str == NULL) {
        str_data = new char(1);
        *str_data = 0;
    } else {
        int len = strlen(str);
        str_data = new char(len + 1);
        strcpy(str_data, str);
    } 
}

String::String(const String &other_obj) {
    int len = strlen(other_obj.str_data);
    str_data = new char(len + 1);
    strcpy(str_data, other_obj.str_data);
}

String &String::operator=(const String &other_obj) {
    if (&other_obj == this) return *this;
    int len = strlen(other_obj.str_data);
    str_data = new char(len + 1);
    strcpy(str_data, other_obj.str_data);
    return *this;
}

String::~String() {
    delete []str_data;    
}

int main(int argc, char **argv)
{

    return 0;
}
