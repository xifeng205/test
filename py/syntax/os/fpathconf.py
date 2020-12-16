#!/usr/bin/env python
# _*_  coding: utf-8 _*_

#*********************************************************************
# Author        : cuiyunpeng
# Email         : @163.com
# Create time   : 2020-07-23 17:37
# Last modified : 2020-07-23 17:37
# Filename      : fpathconf.py
# Description   :
#*********************************************************************
import os

if __name__ ==  "__main__":
    fd = os.open("test1.txt", os.O_RDWR | os.O_CREAT)
    # os.write(fd, str.encode("hellow world"))
    # os.fdatasync(fd)
    # data = os.read(fd, 100)
    # print(data)
    print(os.pathconf_names)
    pc_conf = os.fpathconf(fd, "PC_LINK_MAX")
    print(pc_conf)
    pc_conf = os.fpathconf(fd, "PC_NAME_MAX")
    print(pc_conf)
    os.close(fd)
