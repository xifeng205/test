#!/usr/bin/env python
# _*_  coding: utf-8 _*_

#*********************************************************************
# Author        : cuiyunpeng
# Email         : @163.com
# Create time   : 2020-07-26 10:22
# Last modified : 2020-07-26 10:22
# Filename      : inline.py
# Description   :
#*********************************************************************

def main():
    list = [2,3,4,3,5,4,6,7,4]
    list.sort()
    print(list)
    lst = sorted(list, reverse=True) 
    print(lst)

if __name__ ==  "__main__":
    main()
