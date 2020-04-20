#!/usr/bin/python3
# _*_  coding: utf-8 _*_

# **********************************************************
# * Author        : cuiyunpeng
# * Email         : @163.com
# * Create time   : 2020-02-01 11:15
# * Last modified : 2020-02-01 11:15
# * Filename      : reverse.py
# * Description   : 
# **********************************************************

def reverseWords(input):

    inputWords = input.split(" ")
    inputWords = inputWords[-1::-1]
    output = ' '.join(inputWords)
    return output

if __name__ == "__main__":
    input = 'I like runoob'
    rw =  reverseWords(input)
    print(rw)




