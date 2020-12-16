/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-06-15 13:23
 * Last modified : 2020-06-15 13:23
 * Filename      : pair.cpp
 * Description   : 
*********************************************************************/

#include <iostream>
#include <memory>

using namespace std;

typedef pair<string, string> Author;
typedef pair<string, int> Atrbute;
typedef pair<double, int> pp;

std::pair<std::string, int> get_name() {
    return std::make_pair("cuiyunpeng", 18);
}
int main(int argc, char **argv)
{
    Author name("Name", "Joy");    
    Atrbute atrbute("sex", 18);
    
    cout << name.first << ":" << name.second << endl;
    cout << atrbute.first << ":" << atrbute.second << endl;

    Atrbute p = atrbute;
    cout << p.first << ":" << p.second << endl;
    
    pp p1 = make_pair(1, 2);
    cout << p1.first << ":" << p1.second << endl;

    std::string names;
    int ages;
    std::tie(names, ages) = get_name();
    cout << names << ":" << ages << endl;
    
    return 0;
}
