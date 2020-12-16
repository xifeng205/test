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
def partition(arr,low,high):
    i = ( low-1 )         # 最小元素索引
    pivot = arr[high]

    for j in range(low , high):
        if   arr[j] <= pivot:
            i = i+1
            arr[i],arr[j] = arr[j],arr[i]

    arr[i+1],arr[high] = arr[high],arr[i+1]
    return ( i+1 )


def quickSort(arr,low,high):
    if low < high:

        pi = partition(arr,low,high)

        quickSort(arr, low, pi-1)
        quickSort(arr, pi+1, high)

def main():
    list = [1, 2, 5, 6, 23, 0, 7, 4, 8, 3]
    quickSort(list, 0, len(list)-1)
    print(list)

if __name__ ==  "__main__":
    main()

