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
   os.write(test_file, str.encode("This is only a test."))
   ret = os.read(test_file, 19)
   print(ret)
   os.close(test_file)
   test_file = os.open("test.txt", os.O_RDWR)
   ret = os.read(test_file, 19)
   os.close(test_file)
   print(ret)
