#!/usr/bin/env bash
# *******************************************************************
# * Author        : cuiyunpeng
# * Email         : @163.com
# * Create time   : 2020-06-12 20:12
# * Last modified : 2020-06-12 20:12
# * Filename      : csc1.sh
# * Description   : 
# *******************************************************************
find $PWD -name "*.hpp" -o -name "*.c" -o -name "*.cc"  -o -name "*.cpp" \
    -o -name "*.h"  >> cscope.files

if [ -n $1 ];then
    find $1 -name "*.hpp" -o -name "*.c" -o -name "*.cc"  -o -name "*.cpp" \
        -o -name "*.h"  >> cscope.files
fi

if [ -n $2 ];then
    find $2 -name "*.hpp" -o -name "*.c" -o -name "*.cc"  -o -name "*.cpp" \
        -o -name "*.h"  >> cscope.files
fi
if [ -n $2 ];then
    find $3 -name "*.hpp" -o -name "*.c" -o -name "*.cc"  -o -name "*.cpp" \
        -o -name "*.h"  >> cscope.files
fi
if [ -n $4 ];then
    find $4 -name "*.hpp" -o -name "*.c" -o -name "*.cc"  -o -name "*.cpp" \
        -o -name "*.h"  >> cscope.files
fi
if [ -n $5 ];then
    find $5 -name "*.hpp" -o -name "*.c" -o -name "*.cc"  -o -name "*.cpp" \
        -o -name "*.h"  >> cscope.files
fi
if [ -n $6 ];then
    find $6 -name "*.hpp" -o -name "*.c" -o -name "*.cc"  -o -name "*.cpp" \
        -o -name "*.h"  >> cscope.files
fi
if [ -n $7 ];then
    find $7 -name "*.hpp" -o -name "*.c" -o -name "*.cc"  -o -name "*.cpp" \
        -o -name "*.h"  >> cscope.files
fi
if [ -n $8 ];then
    find $8 -name "*.hpp" -o -name "*.c" -o -name "*.cc"  -o -name "*.cpp" \
        -o -name "*.h"  >> cscope.files
fi
if [ -n $9 ];then
    find $9 -name "*.hpp" -o -name "*.c" -o -name "*.cc"  -o -name "*.cpp" \
        -o -name "*.h"  >> cscope.files
fi
cscope -bR -i cscope.files
ctags -R
