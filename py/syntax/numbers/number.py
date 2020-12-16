#!/usr/bin/env python3.8
# _*_  coding: utf-8 _*_

######################################################################
# Author        : cuiyunpeng
# Email         : @163.com
# Create time   : 2020-07-21 11:51
# Last modified : 2020-07-21 11:51
# Filename      : number.py
# Description   :
######################################################################

import math
import random
def print_hellow():
    """print_hellow"""
    print("hellow world.")

if __name__ == '__main__':
    print_hellow()
    print(abs(-50))
    print(math.ceil(3.1))
    print(math.exp(2))
    print(math.fabs(2))
    print(math.floor(2.3))
    print(math.sqrt(23))
    print(math.log10(100))
    print(math.log1p(100))
    print(math.log2(100))
    print(math.log1p(100))
    print(max(1,3,4,5))
    print(min(1,3,4,5))
    print(math.modf(1.23))
    print(math.fmod(134, 2))
    print(math.fmod(134, 2))

    print(random.choice("hellow woirld."))
    a = [1,2,3,4]
    random.shuffle(a)
    print(a)
    print(random.uniform(1, 20))
    print(random.uniform(31, 20))
