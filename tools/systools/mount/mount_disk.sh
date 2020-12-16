#!/usr/bin/env bash
# *******************************************************************
# * Author        : cuiyunpeng
# * Email         : @163.com
# * Create time   : 2020-06-25 13:43
# * Last modified : 2020-06-25 13:43
# * Filename      : mount_disk.sh
# * Description   : 
# *******************************************************************
set -e
case $1 in
    on)
        mount /dev/nvme0n1p3 /home/cuiyunpeng/data/os
        ;;
    off)
        umount -l /home/cuiyunpeng/data/os
        ;;
esac
exit 0
