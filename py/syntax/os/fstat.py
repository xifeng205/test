#!/usr/bin/env python
# _*_  coding: utf-8 _*_

#*********************************************************************
# Author        : cuiyunpeng
# Email         : @163.com
# Create time   : 2020-07-23 17:59
# Last modified : 2020-07-23 17:59
# Filename      : fstat.py
# Description   :
#*********************************************************************
import os

if __name__ ==  "__main__":
    fd = os.open("foo.txt", os.O_RDWR)
    stat = os.fstat(fd)
    print(stat)
    print(stat.st_size)
    os.close(fd)
