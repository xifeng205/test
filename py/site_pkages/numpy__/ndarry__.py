#!/usr/bin/env python
# _*_  coding: utf-8 _*_

#*********************************************************************
# Author        : cuiyunpeng
# Email         : @163.com
# Create time   : 2020-07-26 11:47
# Last modified : 2020-07-26 11:47
# Filename      : ndarry.py
# Description   :
#*********************************************************************
import numpy as np

def main():
    """main"""
    arr = np.array([1, 3, 4, 5])
    arr2d = np.array([[0,3,4], [5,6,7]])
    print(arr2d)
    p = np.dtype(np.int32)
    print(p)
    a = np.array([1,2,3,4,5,6], ndmin=2)
    print(a)
    b = np.dtype(np.int32)
    print(b)
    dt = np.dtype('i4')
    print(dt)
    dt = np.dtype([('age', np.int8)])
    print(dt)
    c = np.array([(10, ), (20, ), (30, )], dtype = dt)
    print(c['age'])

    a = np.arange(20)
    print(a)
    print(a.ndim)
    a = np.arange(24)
    print(a.ndim)
    b = a.reshape(2, 3, 4)
    print(b.ndim)

    b = np.array([[1,2,3], [ 2,3,4 ]])
    print(b.shape)
    print(b.itemsize)
    print(b.flags)
    b = np.array([1,2,3,4], dtype = np.float64)
    print(b.itemsize)

    b = np.empty([2,4], dtype = int)
    print(b)
    b = np.zeros(8, dtype = int)
    print(b)

    b = np.ones(5)
    print(b)

    b = np.ones([8, 8], dtype = int)
    print(b)

    b = np.asarray([1,2,3,4])
    print(b)
    x = (1,2,3,4)
    b = np.asarray(x)
    print(b)

    buf = b'helow world'
    b = np.frombuffer(buf, dtype = 'S1')
    print(b)

    list = range(4)
    it = iter(list)
    b = np.fromiter(it, dtype= int)
    print(b)

    b = np.arange(5)
    print(b)
    b = np.linspace(1, 10, 10)
    print(b)

    b = np.array([[1,2,3], [4,5,6], [7, 8, 0]])
    print(b)
    v = b[[0,1,2], [0,1,2]]
    print(v)

    b = np.array([[1,2,3], [4,5,6], [7, 8, 0]])
    print(b)
    row = np.array([[0, 0], [2, 2]])
    col = np.array([[0, 2], [0, 2]])
    v = b[row, col]
    print(v)
    s = np.array([np.nan, 1,2,3, np.nan, 4, 5])
    print(s)

if __name__ ==  "__main__":
    main()










