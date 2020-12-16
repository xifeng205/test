#!/usr/bin/env python
# _*_  coding: utf-8 _*_

#*********************************************************************
# Author        : cuiyunpeng
# Email         : @163.com
# Create time   : 2020-07-24 12:50
# Last modified : 2020-07-24 12:50
# Filename      : calendar.py
# Description   :
#*********************************************************************
import calendar
if __name__ ==  "__main__":
    years = int(input("Enter a years: "))
    months = int(input("Enter a month: "))

    calendars = calendar.month(years, months)
    print(calendars)
