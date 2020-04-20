#!/usr/bin/python3
# _*_  coding: utf-8 _*_

# **********************************************************
# * Author        : cuiyunpeng
# * Email         : @163.com
# * Create time   : 2020-02-05 22:49
# * Last modified : 2020-02-05 22:49
# * Filename      : yield.py
# * Description   : 
# **********************************************************
import sys

def fibonacci(n):

    a, b, counter = 0, 1, 0

    while True:
        if (counter > n):
            return
    yield a

    a, b = b, a + b
    counter += 1


f = fibonacci(10)
while True:
     try:
         print(next(f), end = " ")
     except StopIteration:
         sys.exit()



