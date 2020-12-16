#!/usr/bin/env bash
# *******************************************************************
# * Author        : cuiyunpeng
# * Email         : @163.com
# * Create time   : 2020-06-20 10:56
# * Last modified : 2020-06-20 10:56
# * Filename      : cscope_ctags.sh
# * Description   : 
# *******************************************************************
set -e

if [ $# -eq 0 ];then
    while read file
    do
        if [ -n $file ];then
            find $file -name "*.hpp" -o -name "*.c" -o -name "*.cc" \
                -o -name "*.cpp" -o -name "*.h" -o -name Makefile  >> cscope.files
        fi
        cscope -bR -i cscope.files
        ctags --options=$PWD/option-index $file 
    done<$PWD/file-index

    exit 0
fi

if [ $1 == "-h" ];then
    echo --------------------------------------------------------
    echo : cscope-index -h   get help info
    echo : cscope-index -c   only creat cscope.out
    echo : cscope-index -t   only creat tags
    echo : cscope-index -g   create option-index file-index and exclude-index file in current dir
    echo : cscope-index -u   update cscope.out and tags
    echo : cscope-index -f   option_index -f file-index create tags and cscope.out file by option-index file-index exclude-index
    echo : cscope-index -p   option_index -p file-index create tags and cscope.out file by specify specifiely file
    echo : cscope-index      create tags and cscope.out file for current dir 
    echo    
    echo --------------------------------------------------------
    echo  
    exit 0
fi

if [ $1 == "-g" ];then
    cp /home/cuiyunpeng/example/test/tools/systools/cscope/option-index .
    touch exclude-index
    echo $PWD >> file-index
    exit 0
fi

while test $1
do
    case $1 in
        -p) shift
            OPTION_FILE=$1
            ;;

        -f) shift
            while read file
            do
                if [ -n $file ];then
                    find $file -name "*.hpp" -o -name "*.c" -o -name "*.cc" \
                        -o -name "*.cpp" -o -name "*.h" -o -name Makefile  >> cscope.files
                fi
                cscope -bR -i cscope.files
                ctags --options=$OPTION_FILE $file
            done<$1
            ;;
        -u) shift
            while read file
            do
                ctags --options=$OPTION_FILE $file
            done<$1

            cscope -bR -i cscope.files
            ;;
        -s) shift
            cscope-indexer $PWD -r
            ctags -R
            exit 0;;
        -t) 
            while read file
            do
                ctags --options=$PWD/option-index $file 
            done<$PWD/file-index

            exit 0
            ;;
        -c)
            cscope -bR -i cscope.files
            exit 0
            ;;
    esac
    shift
done
exit 0

