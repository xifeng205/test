
#!/usr/bin/env python
# _*_  coding: utf-8 _*_

#*********************************************************************
# Author        : cuiyunpeng
# Email         : @163.com
# Create time   : 2020-07-23 13:55
# Last modified : 2020-07-23 13:55
# Filename      : open.py
# Description   :
#*********************************************************************
import os

if __name__ ==  "__main__":
    test_file = os.open("test.txt", os.O_RDWR)
    cur_dir = os.getcwd()
    print(cur_dir)
    os.close(test_file)
    cur_dir = os.fchdir(test_file)
