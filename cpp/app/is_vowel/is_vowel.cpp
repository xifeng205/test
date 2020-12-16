/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-08-01 14:22
 * Last modified : 2020-08-01 14:22
 * Filename      : is_vowel.cpp
 * Description   : 
*********************************************************************/

#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;
namespace tools_n {
    bool is_vowel(char chr) {
        vector<char> vowel = 
                {'a','o','e','u','i','A','O','E','U','I'};

        return std::any_of(vowel.begin(), vowel.end(),
                [chr](char ch) { return ch == chr; });
    }
}
int main(int argc, char **argv)
{
    std::cout << tools_n::is_vowel('C') << std::endl;
    std::cout << tools_n::is_vowel('c') << std::endl;
    std::cout << tools_n::is_vowel('a') << std::endl;
    std::cout << tools_n::is_vowel('A') << std::endl;
    return 0;
}
