#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<pthread.h>
#include<string.h>
#include<arpa/inet.h>
#include"chat-server.h"
#include<pthread.h>
#include<string.h>

global_ctl_t global_ctrl=
    {
        .quit = true 
    };

void *(chatThrFxn)(void *arg)
{
    int cb_len;
    char chatBuf[CHAT_BUF_LEN] = {};
    int cd = *(int *)arg;
    while(global_ctrl.quit)
    {
        fgets(chatBuf,sizeof(chatBuf),stdin);
        cb_len = sizeof(chatBuf);
        chatBuf[cb_len-1] = '\0';
        send(cd,chatBuf,cb_len,0);
        memset(chatBuf,0,cb_len);
    }

    pthread_exit(0);

}

int main(int argc,char **argv)
{

    int  ret ;
    struct sockaddr_in s_addr,c_addr;
    pthread_t tid;

    int len = sizeof(c_addr);
    char chatBuf[CHAT_BUF_LEN] = {0};

    int sd = socket(AF_INET,SOCK_STREAM,0);
    if(0 == sd)
    {
        perror("cant't creat socket ");
        return -1;
    }

    s_addr.sin_family = AF_INET;
    s_addr.sin_port = htons(PORT);
    s_addr.sin_addr.s_addr = inet_addr(S_IPADDR);

    ret = bind(sd,(struct sockaddr *)&s_addr,sizeof(s_addr));
    if(-1 == ret)
    {
        perror("can't bind ");
        return -1;
    }
    ret = listen(sd,BEG_LOG);
    if(-1 == ret)
    {
        perror("cant't listen");
        return -1;
    }

    int cd = accept(sd,(struct sockaddr *)&c_addr,&len);
    if( -1 == cd )
    {
        perror("can't accept");
        return -1;
    }
    pthread_create(&tid,NULL,chatThrFxn,(void *)&cd);
    pthread_detach(tid);

    while(global_ctrl.quit)
    {
        recv(cd,chatBuf,sizeof(chatBuf),0);
        printf("%s:%s\n",inet_ntoa(c_addr.sin_addr),chatBuf);
        memset(chatBuf,0,sizeof(chatBuf));
    }

    pthread_cancel(tid);

    close(cd);
    close(sd);
    return 0;

}




