#!/usr/bin/env bash
# *******************************************************************
# * Author        : cuiyunpeng
# * Email         : @163.com
# * Create time   : 2020-07-31 18:05
# * Last modified : 2020-07-31 18:05
# * Filename      : youdao.sh
# * Description   : 
# *******************************************************************

nohup firefox  http://dict.youdao.com/search?q=$1 >  /dev/null
