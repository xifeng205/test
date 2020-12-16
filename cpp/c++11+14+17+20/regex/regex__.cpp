/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-07-18 22:27
 * Last modified : 2020-07-18 22:27
 * Filename      : regex.cpp
 * Description   :
 *********************************************************************/
//
// 对标准库的扩充: 正则表达式
// 二、正则表达式简介
//
// 正则表达式不是 C++ 语言的一部分，这里仅做简单的介绍。
//
// 正则表达式描述了一种字符串匹配的模式。一般使用正则表达式主要是实现下面三个需求：
//
//     检查一个串是否包含某种形式的子串；
//     将匹配的子串替换；
//     从某个串中取出符合条件的子串。
//
// 正则表达式是由普通字符（例如 a 到
// z）以及特殊字符组成的文字模式。模式描述在搜索文本时要匹配的一个或多个字符串。
// 正则表达式作为一个模板，将某个字符模式与所搜索的字符串进行匹配。
// （1）普通字符
//
// 普通字符包括没有显式指定为元字符的所有可打印和不可打印字符。这包括所有大写和小写字母
// 、所有数字、所有标点符号和一些其他符号。
// （2）特殊字符
//
// 特殊字符是正则表达式里有特殊含义的字符，也是正则表达式的核心匹配语法。参见下表：
// 特别字符 	描述
// $ 	匹配输入字符串的结尾位置。
// (,) 	标记一个子表达式的开始和结束位置。子表达式可以获取供以后使用。
// * 	匹配前面的子表达式零次或多次。
// + 	匹配前面的子表达式一次或多次。
// . 	匹配除换行符 \n 之外的任何单字符。
// [ 	标记一个中括号表达式的开始。
// ? 	匹配前面的子表达式零次或一次，或指明一个非贪婪限定符。
// \
// 将下一个字符标记为或特殊字符、或原义字符、或向后引用、或八进制转义符。例如，
// n 匹配字符 n。\n 匹配换行符。序列 \\ 匹配 '\' 字符，而 \( 则匹配 '(' 字符。
// ^
// 匹配输入字符串的开始位置，除非在方括号表达式中使用，此时它表示不接受该字符集合。
// { 	标记限定符表达式的开始。
// | 	指明两项之间的一个选择。
// （3）限定符
//
// 限定符用来指定正则表达式的一个给定的组件必须要出现多少次才能满足匹配。见下表：
// 字符 	描述
// * 	匹配前面的子表达式零次或多次。例如，foo* 能匹配 fo 以及 foooo。*
// 等价于{0,}。
// + 	匹配前面的子表达式一次或多次。例如，foo+ 能匹配 foo 以及
// foooo，但不能匹配 fo。+ 等价于 {1,}。 ?
// 匹配前面的子表达式零次或一次。例如，Your(s)? 可以匹配 Your 或 Yours 中的Your
// 。? 等价于 {0,1}。 {n} 	n 是一个非负整数。匹配确定的 n 次。例如，f{2}
// 不能匹配 for 中的 o，但是能匹配 foo 中的两个 o。 {n,} 	n
// 是一个非负整数。至少匹配 n 次。例如，f{2,} 不能匹配 for 中的 o，但能匹配
// foooooo 中的所有 o。o{1,} 等价于 o+。o{0,} 则等价于 o*。 {n,m} 	m 和 n
// 均为非负整数，其中 n 小于等于 m。最少匹配 n 次且最多匹配 m 次。例如，o{1,3}
// 将匹配 foooooo 中的前三个 o。o{0,1} 等价于
// o?。注意，在逗号和两个数之间不能有空格。
//
//
#include <iostream>
#include <regex>
#include <string>

using namespace std;

// 对字符串内容进行匹配的最常见手段就是使用正则表达式。可惜在传统 C++
// 中正则表达式一直没有得到语言层面的支持，没有纳入标准库，而 C++
// 作为一门高性能语言，在后台服务的开发中，对 URL
// 资源链接进行判断时，使用正则表达式也是工业界最为成熟的普遍做法。
//
// 一般的解决方案就是使用 boost 的正则表达式库。而 C++11
// 正式将正则表达式的的处理方法纳入标准库的行列，从语言级上提供了标准的支持，不再依赖第三方。
//
// C++11 提供的正则表达式库操作 std::string 对象，模式 std::regex (本质是
// std::basic_regex)进行初始化，通过 std::regex_match 进行匹配，从而产生
// std::smatch （本质是 std::match_results 对象）。
//
// 我们通过一个简单的例子来简单介绍这个库的使用。考虑下面的正则表达式
//
//     [a-z]+\.txt: 在这个正则表达式中, [a-z] 表示匹配一个小写字母, +
//     可以使前面的表达式匹配多次，因此 [a-z]+
//     能够匹配一个小写字母组成的字符串。在正则表达式中一个 .
//     表示匹配任意字符，而 \. 则表示匹配字符 .，最后的 txt 表示严格匹配 txt
//     则三个字母。因此这个正则表达式的所要匹配的内容就是由纯小写字母组成的文本文件。
//
// std::regex_match
// 用于匹配字符串和正则表达式，有很多不同的重载形式。最简单的一个形式就是传入std::string
// 以及一个 std::regex 进行匹配，当匹配成功时，会返回 true，否则返回
// false。例如：

#define TEST1
#if defined TEST0
int main(int argc, char **argv) {
    std::string file_names[] = {"foo.txt", "bar.txt", "test", "hellw"};
    std::regex txt_regex("([a-z]+)\\.txt");
    std::smatch smatchs;

    for (auto &file_name : file_names) {
        std::cout << file_name << " : "
            <<  std::regex_match(file_name, smatchs, txt_regex) << std::endl;
    }

    return 0;
}
#elif defined TEST1
// 另一种常用的形式就是依次传入 std::string/std::smatch/std::regex
// 三个参数，其中 std::smatch 的本质其实是 std::match_results，在标准库中，
// std::smatch 被定义为了
// std::match_results<std::string::const_iterator>，也就是一个子串迭代器类型的
// match_results。使用 std::smatch 可以方便的对匹配的结果进行获取，例如：

int main(int argc, char **argv) {
    std::string fnames[] = {"foo.txt", "bar.txt", "test", "hellw"};
    std::regex base_regex("([a-z]+)\\.txt");
    std::smatch base_match;
    for (const auto &fname : fnames) {
        if (std::regex_match(fname, base_match, base_regex)) {
            // sub_match 的第一个元素匹配整个字符串
            // sub_match 的第二个元素匹配了第一个括号表达式
            if (base_match.size() == 2) {
                std::string base = base_match[1].str();
                std::cout << "sub-match[0]: " << base_match[0].str() << std::endl;
                std::cout << fname << " sub-match[1]: " << base << std::endl;
            }
        }
        return 0;
    }
}

#endif
