#!/usr/bin/env python
# _*_  coding: utf-8 _*_

#*********************************************************************
# Author        : cuiyunpeng
# Email         : @163.com
# Create time   : 2020-07-25 22:23
# Last modified : 2020-07-25 22:23
# Filename      : assert.py
# Description   :
#*********************************************************************
a = 1
b = 1
def main():
    c = 3
    # assert False, "Assert test."
    print(locals())
    print(globals())

if __name__ ==  "__main__":
    main()
