#!/usr/bin/env python
# _*_  coding: utf-8 _*_

######################################################################
# Author        : cuiyunpeng
# Email         : @163.com
# Create time   : 2020-07-21 20:51
# Last modified : 2020-07-21 20:51
# Filename      : copy+deepcopy.py
# Description   :
######################################################################
import copy

a = {1:[1,2,3,4]}
print(str(a))
b = a.copy()
print(str(b))
c = copy.deepcopy(a)
print(str(c))
