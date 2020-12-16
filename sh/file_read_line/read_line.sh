#!/usr/bin/env bash
# *******************************************************************
# * Author        : cuiyunpeng
# * Email         : @163.com
# * Create time   : 2020-06-20 10:40
# * Last modified : 2020-06-20 10:40
# * Filename      : read_line.sh
# * Description   : 
# *******************************************************************
#!/bin/bash
OLD_IFS=$IFS                     #定义一个变量bak保存IFS的值
if [ $# -ne 1 ];then             #判断位置参数是否为1
  echo "Usage $0 filename"
  exit
fi
if [ ! -f $1 ];then               #判断位置参数是否为文件
  echo "the $1 is not a file"
  exit
fi
OLD_IFS=$'\n'                    #将环境变量IFS的值修改为换行符
for i in `cat $1`                #逐行读取文件内容并打印到屏幕
do
  echo $i
done
IFS=$OLD_IFS                    #将环境变量IFS的值改回原值
