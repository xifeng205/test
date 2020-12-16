#!/usr/bin/env bash
# *******************************************************************
# * Author        : cuiyunpeng
# * Email         : @163.com
# * Create time   : 2020-08-02 13:22
# * Last modified : 2020-08-02 13:22
# * Filename      : login_mysql.sh
# * Description   : 

#启动
docker run --name mysql -p 3306:3306 -e MYSQL_ROOT_PASSWORD=cuiyunpeng -d mysql

#进入容器
docker exec -it mysql bash

#登录mysql
mysql -u root -p

# ALTER USER 'root'@'localhost' IDENTIFIED BY 'Lzslov123!';

#添加远程登录用户
# CREATE USER 'liaozesong'@'%' IDENTIFIED WITH mysql_native_password BY 'Lzslov123!';
# GRANT ALL PRIVILEGES ON *.* TO 'liaozesong'@'%';
