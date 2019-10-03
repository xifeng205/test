#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc ,char *argv[]){
    int fd;
    if(argc<2){
        puts("please input the open file pathname!\n");
        exit(1);
    }
    
    //如果flag参数里有O_CREAT表示,该文件如果不存在,系统则会创建该文件,该文件的权限由第三个参数决定,此处为0755
    //如果flah参数里没有O_CREAT参数,则第三个参数不起作用.此时,如果要打开的文件不存在,则会报错.
    //所以fd=open(argv[1],O_RDWR),仅仅只是打开指定文件
    if((fd=open(argv[1],O_CREAT|O_RDWR,0755))<0){
        perror("open file failure!\n");
        exit(1);
    }else{
        printf("open file %d  success!\n",fd);

    }
    close(fd);
    exit(0);
    
}
