#!/usr/bin/env python
# _*_  coding: utf-8 _*_

#*********************************************************************
# Author        : cuiyunpeng
# Email         : @163.com
# Create time   : 2020-07-24 15:33
# Last modified : 2020-07-24 15:33
# Filename      : dict_merge.py
# Description   :
#*********************************************************************
if __name__ ==  "__main__":
    def dict_merge(dict1, dict2):
        return {**dict1, **dict2}
    print(dict_merge({1:3}, {3:5}))
