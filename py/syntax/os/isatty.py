#!/usr/bin/env python
# _*_  coding: utf-8 _*_

#*********************************************************************
# Author        : cuiyunpeng
# Email         : @163.com
# Create time   : 2020-07-23 20:08
# Last modified : 2020-07-23 20:08
# Filename      : isatty.py
# Description   :
#*********************************************************************
import os

if __name__ ==  "__main__":
    fd = os.open( "foo.txt", os.O_RDWR|os.O_CREAT )

    str = "This is runoob.com site"
    os.write(fd,bytes(str, 'UTF-8'))

    ret = os.isatty(fd)

    print ("返回值: ", ret)

    os.close( fd )
