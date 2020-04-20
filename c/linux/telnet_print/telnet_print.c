/************************************************************
FileName: console_redirect.c
Description: console输出重定向
************************************************************/

/*
    内核的打印不能重定向过来，应用层打印可以重定向打印过来
    查看内核的打印，cat /proc/kmsg，在输出完缓冲区内容后，会阻塞卡住，内核有新的输出时会继续输出。
    如果要把内核打印到telnet，那么需要修改printk.c。
    kernel和user空间下都有一个console，关系到kernel下printk的方向和user下printf的方向，实现差别很大。
    kernel下的console是输入输出设备driver中实现的简单的输出console，只实现write函数，并且是直接输出到设备。
    user空间下的console，实际就是tty的一个特殊实现，大多数操作函数都继承tty，所以对于console的读写，都是由kernel的tty层来最终发送到设备。
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int tty = -1;
    char *tty_name = NULL;

    if(argc < 2)
    {
        printf("miss argument\n");
        return 0;
    }

    /* 获取当前tty名称 */
    tty_name = ttyname(STDOUT_FILENO);
    printf("tty_name: %s\n", tty_name);

    if(!strcmp(argv[1], "on"))
    {
        /* 重定向console到当前tty */
        tty = open(tty_name, O_RDONLY | O_WRONLY);
        ioctl(tty, TIOCCONS);
        perror("ioctl TIOCCONS");
    }
    else if(!strcmp(argv[1], "off"))
    {
        /* 恢复console */
        tty = open("/dev/console", O_RDONLY | O_WRONLY);
        ioctl(tty, TIOCCONS);
        perror("ioctl TIOCCONS");
    }
    else
    {
        printf("error argument\n");
        return 0;
    }

    close(tty);
    return 0;
}
