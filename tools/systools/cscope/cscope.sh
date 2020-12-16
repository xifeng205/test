#!/usr/bin/env bash
# *******************************************************************
# * Author        : cuiyunpeng
# * Email         : @163.com
# * Create time   : 2020-03-21 23:03
# * Last modified : 2020-03-21 23:03
# * Filename      : cscope.sh
# * Description   : 
# *******************************************************************
cscope-indexer $PWD -r 
ctags -R --fields=+lS
