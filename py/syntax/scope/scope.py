#!/usr/bin/env python
# _*_  coding: utf-8 _*_

#*********************************************************************
# Author        : cuiyunpeng
# Email         : @163.com
# Create time   : 2020-07-24 10:41
# Last modified : 2020-07-24 10:41
# Filename      : scope.py
# Description   :
#*********************************************************************
total = 1

if __name__ ==  "__main__":

    def prt(a, b):
        print(a+b)
    prt(1, 3)

    def prt1():
        total = 10
        print(total)
    prt1()

    print(total)
    def prt2():
        print(total)

