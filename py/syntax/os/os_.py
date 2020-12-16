#!/usr/bin/env python
# _*_  coding: utf-8 _*_

#*********************************************************************
# Author        : cuiyunpeng
# Email         : @163.com
# Create time   : 2020-07-23 12:31
# Last modified : 2020-07-23 12:31
# Filename      : os.py
# Description   :
#*********************************************************************
import os, sys, stat

if __name__ == "__main__":
    test_file = open("test.txt", 'w+')
    test_file.write("hellow world.")
    test_file.close()

    os.chmod("./test.txt", stat.S_IRWXU)
