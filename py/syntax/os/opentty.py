#!/usr/bin/env python
# _*_  coding: utf-8 _*_

#*********************************************************************
# Author        : cuiyunpeng
# Email         : @163.com
# Create time   : 2020-07-23 20:28
# Last modified : 2020-07-23 20:28
# Filename      : opentty.py
# Description   :
#*********************************************************************
import os
if __name__ ==  "__main__":
    m, s = os.openpty()
    print(m)
    print(s)
    print(os.ttyname(s))

