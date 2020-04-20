#!/usr/bin/python3
# _*_  coding: utf-8 _*_

# **********************************************************
# * Author        : cuiyunpeng
# * Email         : @163.com
# * Create time   : 2020-02-06 21:14
# * Last modified : 2020-02-06 21:14
# * Filename      : pickew.py
# * Description   : 
# **********************************************************
import pickle

# 使用pickle模块将数据对象保存到文件
data1 = {'a': [1, 2.0, 3, 4+6j],
         'b': ('string', u'Unicode string'),
         'c': None}

selfref_list = [1, 2, 3]
selfref_list.append(selfref_list)

output = open('data.pkl', 'wb')

# Pickle dictionary using protocol 0.
pickle.dump(data1, output)

# Pickle the list using the highest protocol available.
pickle.dump(selfref_list, output, -1)

output.close()
