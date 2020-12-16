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
   test_fd = os.open("test.txt", os.O_RDWR)
   os.write(test_fd, str.encode("This is only a test."))
   test_fd1 = os.dup(test_fd)
   os.closerange(test_fd, test_fd1)
