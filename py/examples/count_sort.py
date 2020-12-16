#!/usr/bin/env python
# _*_  coding: utf-8 _*_

#*********************************************************************
# Author        : cuiyunpeng
# Email         : @163.com
# Create time   : 2020-07-25 18:42
# Last modified : 2020-07-25 18:42
# Filename      : count_sort.py
# Description   :
#*********************************************************************
def count_sort(arr):

    output = [0 for i in range(256)]

    count = [0 for i in range(256)]

    ans = ["" for _ in arr]
    for i in arr:
        count[ord(i)] += 1

    print(count)
    for i in range(256):
        count[i] += count[i-1]
    print(count)

    for i in range(len(arr)):
        output[count[ord(arr[i])]-1] = arr[i]
        count[ord(arr[i])] -= 1

    for i in range(len(arr)):
        ans[i] = output[i]
    return ans


arr = "987654321"
ans = count_sort(arr)
print ( "字符数组排序 %s"  %("".join(ans)) )
