#!/usr/bin/python3
# _*_  coding: utf-8 _*_

# **********************************************************
# * Author        : cuiyunpeng
# * Email         : @163.com
# * Create time   : 2020-02-07 11:44
# * Last modified : 2020-02-07 11:44
# * Filename      : raise.py
# * Description   : 
# **********************************************************

# x = 10
# if x > 5:
    # raise Exception('x 不能大于 5。x 的值为: {}'.format(x))

try:
    raise NameError('HiThere')
except NameError:
    print('An exception flew by!')
    raise
