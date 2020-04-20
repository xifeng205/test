#!/usr/bin/env python
# _*_  coding: utf-8 _*_

# **********************************************************
# * Author        : cuiyunpeng
# * Email         : @163.com
# * Create time   : 2020-02-16 16:17
# * Last modified : 2020-02-16 16:17
# * Filename      : zip.py
# * Description   : 
# **********************************************************

#main function
if __name__ == '__main__':

    '''
    zip 函数描述

    zip() 函数用于将可迭代对象作为参数，将对象中对应的元素
    打包成一个个元组，然后返回由这些元组组成的对象。

    如果各个可迭代对象的元素个数不一致，则返回的对象长度与
    最短的可迭代对象相同。

    利用 * 号操作符，与zip相反，进行解压。

    zip函数语法

    zip(iterable1,iterable2, ...)

    参数说明：
    iterable--一个或多个可迭代对象（字符串，列表，元组，字典）
    '''
    list1 = [1, 3]
    list2 = [2, 4]
    eg = "test"
    list = zip(list1, list2)
    print(eg+"1: cut zip")
    print(list)

    print(eg+"2: unzip")
    list3, list4 = zip(*list)
    print(list3, list4)

    print(eg+"3: for")
    list5 = [x+y  for x, y in zip(list1, list2)]
    print(list5)
