#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<pthread.h>
#include<string.h>
#include<arpa/inet.h>
#include"chat-client.h"
#include<pthread.h>
#include<string.h>

global_ctl_t global_ctrl=
    {
        .quit = true 
    };

void *(chatThrFxn)(void *arg)
{
    char chatBuf[CHAT_BUF_LEN] = {};
    int sd = *(int *)arg;
    while(global_ctrl.quit)
    {
        recv(sd,chatBuf,sizeof(chatBuf),0);
        printf(chatBuf);
        memset(chatBuf,0,sizeof(chatBuf));
    }

    pthread_exit(0);

}

int main(int argc,char **argv)
{

    int cb_len;
    struct sockaddr_in s_addr;
    pthread_t tid;

    char chatBuf[CHAT_BUF_LEN] = {0};

    int sd = socket(AF_INET,SOCK_STREAM,0);
    if(0 == sd)
    {
        perror("cant't creat socket \n");
        return -1;
    }

    s_addr.sin_family = AF_INET;
    s_addr.sin_port = htons(PORT);
    s_addr.sin_addr.s_addr = inet_addr(S_IPADDR);

    int ret = connect(sd,(struct sockaddr *)&s_addr,sizeof(s_addr));
    if(-1 == ret)
    {
        perror("cant't connect to severa\n");
        return -1;
    }

    pthread_create(&tid,NULL,chatThrFxn,(void *)&sd);
    pthread_detach(tid);

    while(global_ctrl.quit)
    {
        fgets(chatBuf,sizeof(chatBuf),stdin);
        cb_len = sizeof(chatBuf);
        chatBuf[cb_len-1] = '\0';
        send(sd,chatBuf,cb_len,0);
        memset(chatBuf,0,cb_len);
    }

    pthread_cancel(tid);

    close(sd);
    return 0;

}




