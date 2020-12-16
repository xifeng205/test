#!/usr/bin/env python
# _*_  coding: utf-8 _*_

#*********************************************************************
# Author        : cuiyunpeng
# Email         : @163.com
# Create time   : 2020-07-24 15:45
# Last modified : 2020-07-24 15:45
# Filename      : time_convert.py
# Description   :
#*********************************************************************
import time
stime = "2019-5-10 23:40:00"
def get_timestamp(stime):
    time_arr = time.strptime(stime, "%Y-%m-%d %H:%M:%S")
    return int(time.mktime(time_arr))

def make_style_time(stime):
    time_arr = time.strptime(stime, "%Y-%m-%d %H:%M:%S")
    return  time.strftime("%Y/%m/%d %H:%M:%S", time_arr)

def main():
    timestamp =  get_timestamp(stime)
    print(timestamp)
    style_time = make_style_time(stime)
    print(style_time)

if __name__ ==  "__main__":
    main()
