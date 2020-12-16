#!/usr/bin/env bash
# *******************************************************************
# * Author        : cuiyunpeng
# * Email         : @163.com
# * Create time   : 2020-06-20 10:44
# * Last modified : 2020-06-20 10:44
# * Filename      : read_line1.sh
# * Description   : 
# *******************************************************************
#!/bin/bash
if [ $# -ne 1 ];then             #判断脚本参数是否为1
 echo "Usage:$0 filename"
 exit 1
fi
file=$1                      #将脚本参数参数赋值给变量file
{                            #定义代码块，大括号{}中的代码即为代码块
 read line1 
 read line2
} <$file                       #使用$file将代码块的标准输入指向文件$file
echo "first line in $file is $line1"   #输出文件内容
echo "second line in $file is $line2"
exit 2
