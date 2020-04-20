# !/usr/bin/env python
# _*_  coding: utf-8 _*_

# *******************************************************************
# * Author        : cuiyunpeng
# * Email         : @163.com
# * Create time   : 2020-02-21 10:29
# * Last modified : 2020-02-21 10:29
# * Filename      : json.py
# * Description   : 
# *******************************************************************
import json

data = [1,3,4]

f = open("json.txt", "w")

json.dumps(data, f)

# print('python source data:', repr(data))
# print('json object :', json_str)
