#!/usr/bin/env bash
# *******************************************************************
# * Author        : cuiyunpeng
# * Email         : @163.com
# * Create time   : 2020-06-20 10:51
# * Last modified : 2020-06-20 10:51
# * Filename      : read_line2.sh
# * Description   : 
# *******************************************************************
if [ $# -ne 1 ];then
    echo "Usage:$0 filename"
    exit 1
fi
file=$1
if [ ! -f $file ];then
    echo "the $file is not a file"
    exit 2
fi
count=0
while read line   #使用read命令循环读取文件内容，并将读取的文件内容赋值给变量line
do
    let count++
    echo "$count $line"
done <$file      #“done <$file”将整个while循环的标准输入指向文件$file
exit 0
