#!/usr/bin/env python
# _*_  coding: utf-8 _*_

# *******************************************************************
# * Author        : cuiyunpeng
# * Email         : @163.com
# * Create time   : 2020-02-17 14:27
# * Last modified : 2020-02-17 14:27
# * Filename      : dot.py
# * Description   : 
# *******************************************************************
import numpy as np

a = [1, 2]
b = [1, 4]

dot_list = np.dot(a, b)
print("eg1:   \n"+ str(dot_list))

a = [[1, 0], [0, 2], [1, 5]]
b = [[4, 1, 3], [2, 2, 6]]

dot_list = np.dot(a, b)
print("eg2:\n " +  str(dot_list))

a = np.arange(3*4*5*6).reshape((3,4,5,6))
b = np.arange(3*4*5*6)[::-1].reshape((5,4,6,3))
i = np.dot(a, b)[2,3,2,1,2,2]
print("eg3:\n"+ str(dot_list))


