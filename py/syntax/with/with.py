#!/usr/bin/python3
# _*_  coding: utf-8 _*_

# **********************************************************
# * Author        : cuiyunpeng
# * Email         : @163.com
# * Create time   : 2020-02-07 11:55
# * Last modified : 2020-02-07 11:55
# * Filename      : with.py
# * Description   : 
# **********************************************************
with open("with.txt") as f:
    for line in f:
        print(line, end = "")
