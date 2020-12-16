#!/usr/bin/env python
# _*_  coding: utf-8 _*_

#*********************************************************************
# Author        : cuiyunpeng
# Email         : @163.com
# Create time   : 2020-08-16 22:43
# Last modified : 2020-08-16 22:43
# Filename      : arg_kwargs.py
# Description   :
#*********************************************************************
#以下方法定义可变参数:
# *args 可变参数, 一般是元组
# **kwargs 可变参数, 一般是字典, 以键值方式传递 
def foo(*args, **kwargs):
    print(args)
    print(kwargs)
    print(args, kwargs)

def main():
    foo(1, 3, 4)
    foo(a=1, b=2)
    foo(12, a=1, b=2)

if __name__ ==  "__main__":
    main()
