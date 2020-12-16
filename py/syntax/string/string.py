#!/usr/bin/env python
# _*_  coding: utf-8 _*_

######################################################################
# Author        : cuiyunpeng
# Email         : @163.com
# Create time   : 2020-07-21 14:59
# Last modified : 2020-07-21 14:59
# Filename      : string.py
# Description   :
######################################################################

str0 = "hellow World";
print(str0.capitalize())

str1 = "runoob"
print(str1.center(30))
print(str1.center(30, '*'))

str2 = "runoob"
print(str2.count("o", 0, len(str2)))

str3 = "你好"
str33 = str3.encode("UTF-8")
print(str3)
str3 = "中国"
str33 = str3.encode("GBK")
print(str33)
str333 = str33.decode("GBK", "strict")
print(str333)

# print(str1.endswith("oob", 0, len(str1))) str4 = "heloow\tworld"
# print(str4.expandtabs(18))

str5 = "Runoob example....wow!!!"
str51 = "exam";
print (str5.find(str51))
print (str5.find(str51, 5))
print (str5.find(str51, 10))
print (str5.index(str51))
print (str5.index(str51, 5))

str6 = "runoob2016"  # 字符串没有空格
print (str6.isalnum())
str66 = "www.runoob.com"
print (str66.isalnum())

str7 = "runoob"
print (str7.isalpha())

# 字母和中文文字
str77 = "runoob菜鸟教程"
print (str77.isalpha())

str777 = "Runoob example....wow!!!"
print (str777.isalpha())

str8 = "123567"
print(str8.isdigit());

str88 = "1, 3, 4, 5, 'c'"
print(str88.isdigit())

str9 = "RUNOOB example....wow!!!"
print (str9.islower())

str91 = "runoob example....wow!!!"
print (str91.islower())

str10 = "RUNOOB example....wow!!!"
print (str10.islower())

str101 = "runoob example....wow!!!"
print (str91.islower())

s = '\u00B23455'
print(s.isnumeric())
# s = '½'
s = '\u00BD'
print(s.isnumeric())

a = "\u0030" #unicode for 0
print(a.isnumeric())

b = "\u00B2" #unicode for ²
print(b.isnumeric())

c = "10km2"
print(c.isnumeric())

str = "       "
print (str.isspace())

str11 = "Runoob example....wow!!!"
print (str11.isspace())
str = "This Is String Example...Wow!!!"
print (str.istitle())

str12 = "This is string example....wow!!!"
print (str12.istitle())
str13 = "THIS IS STRING EXAMPLE....WOW!!!"
print (str13.isupper())

str13 = "THIS is string example....wow!!!"
print (str13.isupper())
seq = ("1", "c", "d", "h", "l")
str13 = ""
print(str13.join(seq))

