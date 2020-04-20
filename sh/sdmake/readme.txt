MAKE SDCARD
---------------------------
将编译好的kba8w-sw-image-r1.0.0.bin复制到建立目录
后改成12w型号，如：kba12w-sw-image-r1.2.1.bin

如果是新的系统环境，则需要编译dm3xx_boot_make_image文件，执行make就行

在建立目录下执行命令
sudo ./dm3xx_sd_boot make /dev/sd（x） 

如果好几个盘符，首先用命令看一下有几个盘符 ，命令 ls -lh /dev/sd 然后按Tab键列表显示所有盘符
然后插上要制作的SD看，再执行以上命令，查看多出来的盘符名称
例如：
ls -lh /dev/sd 加上Tab键显示
sda   sda1  sda2  sda5  sda6  sda7  sda8 

插上SD卡后，继续执行以上命令会显示

sda   sda1  sda2  sda5  sda6  sda7  sda8 sdb sdb1 sdb2

则sd卡的盘符为sdb

这时制作sd卡的命令如下：
sudo ./dm3xx_sd_boot make /dev/sdb

如果已经有两个盘符，那么sd卡的盘符可能是sdc
这时执行命令的盘符就是sudo ./dm3xx_sd_boot make /dev/sdc
