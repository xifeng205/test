#!/usr/bin/env python
# _*_  coding: utf-8 _*_

#*********************************************************************
# Author        : cuiyunpeng
# Email         : @163.com
# Create time   : 2020-07-23 17:12
# Last modified : 2020-07-23 17:12
# Filename      : fdopen.py
# Description   :
#*********************************************************************
import os

if __name__ ==  "__main__":
    test_fd = os.open("test.txt", os.O_RDWR)
    os.write(test_fd, str.encode("HELLOW WORLD."))
    read_data = os.read(test_fd, 100)
    print(read_data)
    fo = os.fdopen(test_fd, "w+")
    fo.write("hdksfjkslkfsdklf")
    os.fdatasync(test_fd)
    test_os_read = os.read(test_fd, 1000)
    os.close(test_fd)
    print(test_os_read)
