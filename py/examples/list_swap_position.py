#!/usr/bin/env python
# _*_  coding: utf-8 _*_

#*********************************************************************
# Author        : cuiyunpeng
# Email         : @163.com
# Create time   : 2020-07-24 14:44
# Last modified : 2020-07-24 14:44
# Filename      : list_swap_position.py
# Description   :
#*********************************************************************
if __name__ ==  "__main__":
    def swapPositions(list, pos1, pos2):
        list[pos1], list[pos2] = list[pos2], list[pos1]
        return list

    List = [23, 65, 19, 90]
    pos1, pos2  = 1, 3

    print(swapPositions(List, pos1-1, pos2-1))
