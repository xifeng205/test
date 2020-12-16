#!/usr/bin/env python
# _*_  coding: utf-8 _*_

#*********************************************************************
# Author        : cuiyunpeng
# Email         : @163.com
# Create time   : 2020-07-24 17:54
# Last modified : 2020-07-24 17:54
# Filename      : select_sort.py
# Description   :
#*********************************************************************

def select_sort(lst, low, high):
    if low > high: low, high = high, low

    for i in range(low, high):
        min_num = i
        for j in range(i+1, high):
            if lst[j] < lst[min_num]:
                min_num = j

        lst[j], lst[min_num] = lst[min_num], lst[j]

def main():
    list = [1, 2, 5, 6, 23, 0, 7, 4, 8, 3]
    select_sort(list, 0, len(list)-1)
    print(list)

if __name__ ==  "__main__":
    main()
