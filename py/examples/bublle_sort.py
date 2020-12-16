#!/usr/bin/env python
# _*_  coding: utf-8 _*_

#*********************************************************************
# Author        : cuiyunpeng
# Email         : @163.com
# Create time   : 2020-07-24 17:18
# Last modified : 2020-07-24 17:18
# Filename      : quick_sort.py
# Description   :
#*********************************************************************
def bubble_sort(arr,low,high):
    n = high - low
    for i in range(low, high):
        for j in range(n-i):
            if arr[j] > arr[j+1]:
                arr[j], arr[j+1] = arr[j+1], arr[j]

def main():
    list = [1, 2, 5, 6, 23, 0, 7, 4, 8, 3]
    bubble_sort(list, 0, len(list)-1)
    print(list)

if __name__ ==  "__main__":
    main()

