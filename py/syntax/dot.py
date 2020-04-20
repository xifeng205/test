#!/usr/bin/python2
# _*_  coding: utf-8 _*_

# **********************************************************
# * Author        : cuiyunpeng
# * Email         : @163.com
# * Create time   : 2020-02-14 11:58
# * Last modified : 2020-02-14 11:58
# * Filename      : dot.py
# * Description   : 
# **********************************************************
import numpy as np
deltas = []
list1 = [1,2]
list2 = [1,2]
list1 = np.atleast_1d(list1) 
list2 = np.atleast_1d(list2) 
print(list1, list2)
print(deltas)
deltas.append(list1.dot(list2))
print(deltas)
