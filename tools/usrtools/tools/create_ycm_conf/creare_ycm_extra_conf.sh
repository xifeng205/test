#!/usr/bin/env bash
# *******************************************************************
# * Author        : cuiyunpeng
# * Email         : @163.com
# * Create time   : 2020-07-04 09:38
# * Last modified : 2020-07-04 09:38
# * Filename      : creare_ycm_extra_con.sh
# * Description   : 
# *******************************************************************
set -e
case $1 in
    -py)
        cp \
        /home/cuiyunpeng/example/test/tools/usrtools/tools/create_ycm_conf/ycm_extra_conf.py.py .ycm_extra_conf.py 
        ;;
    -cpp)
        cp \
        /home/cuiyunpeng/example/test/tools/usrtools/tools/create_ycm_conf/ycm_extra_conf.py.cpp .ycm_extra_conf.py 
        ;;
    -c)
        cp \
        /home/cuiyunpeng/example/test/tools/usrtools/tools/create_ycm_conf/ycm_extra_conf.py.c .ycm_extra_conf.py 
        ;;
    *)
        echo "cyef [-c] [-cpp] [-py]"
        ;;
esac
exit 0
