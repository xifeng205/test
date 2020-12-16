#!/usr/bin/env bash
# *******************************************************************
# * Author        : cuiyunpeng
# * Email         : @163.com
# * Create time   : 2020-08-02 13:07
# * Last modified : 2020-08-02 13:07
# * Filename      : mysql.sh
# * Description   : 
docker run -itd --name mysql-test -p 3306:3306 -e MYSQL_ROOT_PASSWORD=cuiyunpeng mysql
