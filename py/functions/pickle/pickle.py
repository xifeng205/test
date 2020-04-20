#!/usr/bin/env python
# _*_  coding: utf-8 _*_

# *******************************************************************
# * Author        : cuiyunpeng
# * Email         : @163.com
# * Create time   : 2020-02-19 12:45
## * Last modified : 2020-02-19 12:45
# * Filename      : pickle.py
# * Description   : 
# *******************************************************************

import cPickle as pickle
import pprint

# 使用pickle模块将数据对象保存到文件
data1 = {'a': [1, 2.0, 3, 4+6j],
         'b': ('string', u'Unicode string'),
         'c': None}

selfref_list = [1, 2, 3]
selfref_list.append(selfref_list)

output = open('data.pkl', 'wb')

# Pickle dictionary using protocol 0.

# Pickle the list using the highest protocol available.
pickle.dump(selfref_list, output)

pickle.dump(data1, output)
output.close()

#read pkl file
pkl_file = open('data.pkl', 'rb')

data1 = pickle.load(pkl_file)
pprint.pprint(data1)

data2 = pickle.load(pkl_file)
pprint.pprint(data2)

pkl_file.close()
