#ifndef __CHAT_CLIENT_H
#define __CHAT_CLIENT_H
#include<stdbool.h>

#define PORT 8888
#define CHAT_BUF_LEN 1024
#define S_IPADDR "192.168.0.132"
typedef struct global_ctl
{
    bool quit;
}global_ctl_t;


#endif
