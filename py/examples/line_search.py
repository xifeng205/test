#!/usr/bin/env python
# _*_  coding: utf-8 _*_
# Author        : cuiyunpeng
# Email         : @163.com
# Create time   : 2020-07-24 21:31
# Last modified : 2020-07-24 21:31
# Filename      : line_search.py
# Description   :

def line_search(arry, low, high, x):
    """binary

    :param arry:
    :param low:
    :param high:
    """
    if low > high: high, low = low, high

    for i in range(low, high):
        if arry[i] == x: return i
def main():
    list = [1, 3, 4, 5, 6, 7, 8]
    ret = line_search(list, 0, len(list) , 8)
    print(ret)

if __name__ ==  "__main__":
    main()
