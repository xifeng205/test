#!/usr/bin/env python
# _*_  coding: utf-8 _*_

#*********************************************************************
# Author        : cuiyunpeng
# Email         : @163.com
# Create time   : 2020-07-26 07:36
# Last modified : 2020-07-26 07:36
# Filename      : regex.py
# Description   :
#*********************************************************************
import re

def main():
    ret = re.match("www", "www.runoob.com").span()
    ret = re.match("www", "www.runoob")
    print(ret)

    line = "Cat is samarter than dog."
    match_obj = re.match(r'(.*) is (.*) *', line, re.M|re.I)
    print(match_obj.group())
    print(match_obj.group(1))
    print(match_obj.group(2))

    pattern = re.compile(r'\d+')
    ret = pattern.match('one12twothree34four')
    ret = pattern.match('one12twothree34four', 2, 10)
    ret = pattern.match('one12twothree34four', 3, 10)
    print(ret.span())
    print(ret.start())
    print(ret.end())
    ret = pattern.findall('one12twothree34four')
    print(ret)
    ret = pattern.findall('one12twothree34four', 2, 10)
    print(ret)
    ret = pattern.findall('one12twothree34four', 3, 10)
    iter = pattern.finditer('onw234jidfi333')
    for match in iter:
        print(match.group())
    re.split('a+', "run ood")
    re.split('u', "run ood")
    m = re.split(' ', "run ood")
    print(m)

if __name__ ==  "__main__":
    main()
