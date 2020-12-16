#!/usr/bin/env python
# _*_  coding: utf-8 _*_

#*********************************************************************
# Author        : cuiyunpeng
# Email         : @163.com
# Create time   : 2020-07-23 17:02
# Last modified : 2020-07-23 17:02
# Filename      : fdatasync.py
# Description   :
#*********************************************************************
import os, sys

if __name__ ==  "__main__":

    fd = os.open("foo1.txt", os.O_RDWR|os.O_CREAT)

    os.write(fd, str.encode("This is test"))

    os.fsync(fd)

    os.lseek(fd, 0, 0)
    str1 = os.read(fd, 100)
    print ("读取的字符是 : ", str1)

    os.close( fd )

    print ("关闭文件成功!!")
