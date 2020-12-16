#!/usr/bin/env python
# _*_  coding: utf-8 _*_

#*********************************************************************
# Author        : cuiyunpeng
# Email         : @163.com
# Create time   : 2020-07-24 14:48
# Last modified : 2020-07-24 14:48
# Filename      : list_reverse.py
# Description   :
#*********************************************************************
if __name__ ==  "__main__":
    def list_reverse(lst):
        lst.reverse()
        return lst

    lists = [1, 3, 4, 5]
    ret_reverse = list_reverse(lists)
    print(ret_reverse)

    # def Reverse(lst):
        # return [ele for ele in reversed(lst)]

    # lst = [10, 11, 12, 13, 14, 15]

    # print(Reverse(lst))

    # def Reverse(lst):
        # lst.reverse()
        # return lst

    # lst = [10, 11, 12, 13, 14, 15]
    # print(Reverse(lst))
