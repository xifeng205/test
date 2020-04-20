#!/usr/bin/python2
# _*_  coding: utf-8 _*_

# *******************************************************************
# * Author        : cuiyunpeng
# * Email         : @163.com
# * Create time   : 2020-02-29 13:57
# * Last modified : 2020-02-29 13:57
# * Filename      : pdb.py
# * Description   : 
# *******************************************************************
import pdb
def add(x, y):
    k = 10
    z = x + y
    for i in range(k):
        pdb.set_trace()
        z += i
    return z

def  main():
    x, y = 1, 2
    # pdb.set_trace()
    z = add(x, y)
    print(z)

if __name__ == '__main__':
    main()
