#!/usr/bin/env python
# _*_  coding: utf-8 _*_

#*********************************************************************
# Author        : cuiyunpeng
# Email         : @163.com
# Create time   : 2020-07-24 13:40
# Last modified : 2020-07-24 13:40
# Filename      : seconds.py
# Description   :
#*********************************************************************
import time
if __name__ ==  "__main__":
    print("Enter a 'Enter key' to start:")
    input("")

    print("start:")
    start_time = time.time()
    while True:
        try:
            while True:
                delta_time = time.time() - start_time
                delt_second = round(delta_time, 0)
                print("Time count: ", delta_time, "second")
                time.sleep(1)
        except KeyboardInterrupt:
            print("Time count end")
            break

