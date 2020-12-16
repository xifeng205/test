#!/usr/bin/env bash
# *******************************************************************
# * Author        : cuiyunpeng
# * Email         : @163.com
# * Create time   : 2020-05-26 17:02
# * Last modified : 2020-05-26 17:02
# * Filename      : mk.sh
# * Description   : 
# *******************************************************************
C=.c
CPP=.cpp

cp /home/cuiyunpeng/example/test/tools/usrtools/tools/make/templete1 Makefile -rf


filename=`grep "int main(int argc," ./*|cut  -d .  -f 2  |cut -d / -f 2`

if [ -f $filename$CPP ] || [ -f $filename$C ]
then
    echo $filename
    sed -i "s/BASE := /BASE = $filename/" ./Makefile 
else
    echo filename is not exist!!
fi
