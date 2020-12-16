#!/usr/bin/env python
# _*_  coding: utf-8 _*_
# Author        : cuiyunpeng
# Email         : @163.com
# Create time   : 2020-07-24 21:31
# Last modified : 2020-07-24 21:31
# Filename      : binary_search.py
# Description   :

def binary_search(arry, low, high, x):
    """binary

    :param arry:
    :param low:
    :param high:
    """
    if low > high: high, low = low, high

    mid = int((low + high) / 2)
    if arry[mid] == x:
        return mid
    elif x < arry[mid]:
        return binary_search(arry, low, mid, x)
    else:
        return binary_search(arry, mid+1, high, x)

def main():
    list = [1, 3, 4, 5, 6, 7, 8]
    ret = binary_search(list, 0, len(list) , 8)
    print(ret)

if __name__ ==  "__main__":
    main()
