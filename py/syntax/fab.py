#!/usr/bin/python3
# _*_  coding: utf-8 _*_

# **********************************************************
# * Author        : cuiyunpeng
# * Email         : @163.com
# * Create time   : 2020-02-06 19:07
# * Last modified : 2020-02-06 19:07
# * Filename      : fab.py
# * Description   : 
# **********************************************************

# 斐波那契(fibonacci)数列模块
def fib(n):    # 定义到 n 的斐波那契数列
    """fib

    :param n:
    """
    a, b = 0, 1
    while b < n:
        print(b, end=' ')
        a, b = b, a+b
    print()

def fib2(n): # 返回到 n 的斐波那契数列
    """fib2

    :param n:
    """
    result = []
    a, b = 0, 1
    while b < n:
        result.append(b)
        a, b = b, a+b
    return result

