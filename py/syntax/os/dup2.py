#!/usr/bin/env python
# _*_  coding: utf-8 _*_

#*********************************************************************
# Author        : cuiyunpeng
# Email         : @163.com
# Create time   : 2020-07-23 15:43
# Last modified : 2020-07-23 15:43
# Filename      : dup2.py
# Description   :
#*********************************************************************
import os

if __name__ ==  "__main__":
    test_file = open("test.txt", 'a+')
    os.dup2(test_file.fileno(), 1)
    print("hellow world")
    print("hellow world")
    print("hellow world")
    print("hellow world")
    test_file.close()


