#!/usr/bin/env bash
# *******************************************************************
# * Author        : cuiyunpeng
# * Email         : @163.com
# * Create time   : 2020-04-20 14:14
# * Last modified : 2020-04-20 14:14
# * Filename      : mv2trash.sh
# * Description   : 
# *******************************************************************
time=$(date)
tmp1=$(echo $time | awk '{print $4}')
tmp2=$(echo $time | awk '{print $3}')
tmp3=$(echo $time | awk '{print $2}')
tmp4=$(echo $time | awk  '{print $5}'| awk -F: '{print $1}')
tmp5=$(echo $time | awk  '{print $5}'| awk -F: '{print $2}')

objtime=$tmp1$tmp2$tmp3$tmp4$tmp5
mv $1 /home/cuiyunpeng/.local/share/Trash/files/$1.$objtime.trash

