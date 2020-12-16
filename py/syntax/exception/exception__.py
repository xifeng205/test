#!/usr/bin/env python
# _*_  coding: utf-8 _*_

#*********************************************************************
# Author        : cuiyunpeng
# Email         : @163.com
# Create time   : 2020-07-24 05:52
# Last modified : 2020-07-24 05:52
# Filename      : exception__.py
# Description   :
#*********************************************************************
def this_fail():
    return 5/0

if __name__ ==  "__main__":
    # while True:
    #     try:
    #         x = int(input("Enter a intger: "))
    #         break
    #     except ValueError:
    #         print("The interger is wrong, enter agin: ")
    #
    # x = 1
    # if x > 5:
        # raise Exception("{} beyond 5".format(x))
    # try:
    #     this_fail()
    # except ZeroDivisionError as err:
    #     print("The err is {}".format(err))
    # finally:
    #     print("handel done.")
    #
    try:
        raise NameError("hellow")
    except NameError:
        print("The err is ")
        raise
