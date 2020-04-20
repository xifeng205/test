#!/usr/bin/env bash
# *******************************************************************
# * Author        : cuiyunpeng
# * Email         : @163.com
# * Create time   : 2020-03-18 11:04
# * Last modified : 2020-03-18 11:04
# * Filename      : paste.sh
# * Description   : 
# *******************************************************************
echo "hellow world1" > 1.txt
echo "hellow world2" > 2.txt
echo "hellow world3" > 3.txt
 
paste 1.txt 2.txt 3.txt

echo 

cat 1.txt 2.txt 3.txt

