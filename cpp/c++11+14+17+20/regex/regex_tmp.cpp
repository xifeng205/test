/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-08-08 09:15
 * Last modified : 2020-08-08 09:15
 * Filename      : regex_tmp.cpp
 * Description   : 
*********************************************************************/

#include <iostream>
#include <regex>
#include <string>

using namespace std;

int main(int argc, char **argv) {
    std::string fnames[] = { "foo.txt", "zoo.txt", "test"};
    std::regex regex_pattern("([a-z]*)\\.txt");
    std::smatch match_result;
    for (const auto fname: fnames) {
        bool  result = std::regex_match(fname, match_result, regex_pattern);
        if (match_result.size() == 2) {
            std::cout << match_result[0] << std::endl;      
            std::cout << match_result[1] << std::endl;      
        }
    }
    return 0;
}
