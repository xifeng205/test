#!/usr/bin/env python
# _*_  coding: utf-8 _*_

#*********************************************************************
# Author        : cuiyunpeng
# Email         : @163.com
# Create time   : 2020-07-23 20:15
# Last modified : 2020-07-23 20:15
# Filename      : listdir.py
# Description   :
#*********************************************************************
import os

if __name__ ==  "__main__":
    pwd = "." 
    files = os.listdir(pwd)
    for file in files:
        print(file)
