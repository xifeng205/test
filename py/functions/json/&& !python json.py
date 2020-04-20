!/usr/bin/env python3
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

data =  {
'no'  : 1,
'mame': 'runoob',
'url' : 'http://www.runoob.com'
}

json_str = json.dumps(data)
# # print('python source data':, repr(data))
# # print('json object :', json_str)
#
