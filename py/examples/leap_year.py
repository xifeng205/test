#!/usr/bin/env python
# _*_  coding: utf-8 _*_

#*********************************************************************
# Author        : cuiyunpeng
# Email         : @163.com
# Create time   : 2020-07-24 11:45
# Last modified : 2020-07-24 11:45
# Filename      : leap_year.py
# Description   :
#*********************************************************************
if __name__ ==  "__main__":
    years = int(input("Enter a year: "))
    if years % 4 == 0:
        if years % 100 == 0:
            if years % 400 == 0:
                print("{} is a leap year". format(years))
            else:print("{} is not a leap year". format(years))
        else:print("{} is a leap year". format(years))
    else: print("{} is not a leap year.". format(years))

