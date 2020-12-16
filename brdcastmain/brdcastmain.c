#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>   
#include <libgen.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <sys/select.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <net/if_arp.h>
#include <error.h>
#include <net/route.h>
#include <fcntl.h>
#include <pthread.h>
#include <errno.h>
#include <signal.h>
#include "sample_comm.h"

#include "acodec.h"
#include "hi_rtc.h"
#include "rhwav2pcm.h"
#include "app_common.h"
#include "rhfunc.h"
#include "ring.h"

#define INIFILEPATH "/mnt/nand/brdcastmain.ini"
#define VER_PATH "/mnt/nand/ver.txt"
#define VER "ver=v3.0.0\r\n"

stApp gstApp;

/*紧急呼叫 拔号键 */
unsigned int guiGpioNum_up  = 9*8+3;//调度
unsigned int guiGpioNum_dwn = 9*8+4;//本地
unsigned int gdialmsgoff =0;
typedef struct NsHandleT NsHandle;

extern unsigned int guiGpioNum_LEDRED;
extern unsigned int guiGpioNum_GREEN;

extern const char *strWavPath;
int istartsd =0;
const char *NandPath = "/mnt/nand/";

int giMicVol=10;//[-20,10]
int giAudioVol=90;
int giEchoDelay;
int giEchoDelay2;
int giEchoDelay3;

int giSoftAgc=1;
int giSoftNs =1;
int giPcmWriteFile=0;
int giAecMode=2;

extern unsigned long GetTickCount();

extern  HI_U32 u32AiVqeType;  
extern  HI_U32 u32Aec;

extern void monitor_communciation_udp_ack(void);

unsigned int u32ifuseAec=0;
unsigned int u32ifuseAec2=0;
unsigned int u32ifuseAec3=0;

pthread_mutex_t audiodrivemutex;

extern pthread_mutex_t logmutex;

int get_gpio_value(int igpionum)
{
    FILE *fp;
    char gpiofilename[256];
    unsigned char buf[10];

    fp = fopen("/sys/class/gpio/export", "w");
    fprintf(fp, "%d", igpionum);
    fclose(fp);

    memset(gpiofilename, 0, 256);
    sprintf(gpiofilename, "/sys/class/gpio/gpio%d/direction", igpionum);
    fp = fopen(gpiofilename, "rb+");
    fprintf(fp, "in");
    fclose(fp);

    memset(gpiofilename, 0, 256);
    sprintf(gpiofilename, "/sys/class/gpio/gpio%d/value", igpionum);

    fp = fopen(gpiofilename, "rb+");
    memset(buf, 0, 10);
    fread(buf, sizeof(char), sizeof(buf) - 1, fp);
    fclose(fp);
    return  (buf[0]-48==0)?0:1;

}
void set_gpio_value(int igpionum, int ilevel)
{
    FILE *fp;
    char gpiofilename[256];
    unsigned char buf[10];

    fp = fopen("/sys/class/gpio/export", "w");
    fprintf(fp, "%d", igpionum);
    fclose(fp);

    memset(gpiofilename, 0, 256);
    sprintf(gpiofilename, "/sys/class/gpio/gpio%d/direction", igpionum);
    fp = fopen(gpiofilename, "rb+");
    fprintf(fp, "out");
    fclose(fp);

    memset(gpiofilename, 0, 256);
    sprintf(gpiofilename, "/sys/class/gpio/gpio%d/value", igpionum);

    fp = fopen(gpiofilename, "rb+");
    memset(buf, 0, 10);
    strcpy((char *)buf,ilevel ==0? "0":"1");
    fwrite(buf, sizeof(char), sizeof(buf) - 1, fp);
    fclose(fp);
}

unsigned long get_logfile_size(void)
{
    unsigned long filesize=-1;
    FILE *fp;
    fp= fopen("/mnt/nand/brdcastmain_log.txt","r");
    if(fp == NULL)
        return filesize;
    fseek(fp,0L,SEEK_END);
    filesize = ftell(fp);
    fclose(fp);
    return filesize;
}
void create_config_file(char mac[]){
    FILE *fp;
    fp = fopen(INIFILEPATH, "w");
    if(fp == NULL) {
        logmsg_error("[%s:%d]error open ini file\r\n",__FUNCTION__, __LINE__);
        return;
    }
    fprintf(fp,"DHCPC=0\r\n");
    fprintf(fp,"LocalIp=192.168.1.17\r\n");
    fprintf(fp,"Netmask=255.255.255.0\r\n");
    fprintf(fp,"Gatway=192.168.1.1\r\n");
    fprintf(fp,"ServerIp=192.168.1.11\r\n");
    fprintf(fp,"MulticastIp=234.2.2.2\r\n");
    fprintf(fp,"FilePlayVol=90\r\n");
    fprintf(fp,"MAC=%s\r\n",mac);
    fprintf(fp,"SoundMode=%d\r\n",3);
    fprintf(fp,"HardAecWhenTalk=%d\r\n",0);
    fprintf(fp,"SoftAec=%d\r\n",1);//是否启用1阶回声抑制
    fprintf(fp,"SoftAec2=%d\r\n",0);//是否启用2阶回声抑制
    fprintf(fp,"SoftAec3=%d\r\n",0);//是否启用3阶回声抑制
    fprintf(fp,"MicVol=%d\r\n",1);//麦克风音量
    fprintf(fp,"AudioVol=%d\r\n",85);//语音音量
    fprintf(fp,"rVol=%d\r\n",90);//语音音量
    fprintf(fp,"EchoDelay=%d\r\n",120);//回声时间差1
    fprintf(fp,"EchoDelay2=%d\r\n",163);//回声时间差2
    fprintf(fp,"EchoDelay3=%d\r\n",198);//回声时间差3

    fprintf(fp,"SoftAgc=%d\r\n",0);//Agc启用 
    fprintf(fp,"SoftNs=%d\r\n",0);//抑制噪声启用 
    fprintf(fp,"PcmWriteFile=%d\r\n",0);//pcm写入文件
    fprintf(fp,"AecMode=%d\r\n",2);//回声策略 2激进 1稳健 0保守
    fprintf(fp,"FilterLowVol=%d\r\n",1);//过滤低音量数据
    fprintf(fp,"FilterLowVol_Threold=%d\r\n",1200);//过滤低音量数据
    fprintf(fp,"samples=32000\r\n");

    printf("restore default set\r\n");
    fclose(fp);
}

void ver_ctl(void){
    char ver[8] = {"nover"};
    FILE *fp;

    read_conf_value("ver", ver, VER_PATH);
    if(strcmp(ver, "nover")==0){
        printf("ver wirte\n\r");
        fp = fopen(VER_PATH, "w");
        if(fp ==NULL){
            logmsg_error("[%s:%d]error open verfile\r\n",__FUNCTION__, __LINE__);
            return;
        }
        fprintf(fp,VER);
        fclose(fp);
    }
}

int main(int argc, char *argv[])
{
    unsigned char aPar[50]={0};
    char acMicVol[10]={0};
    char acAudioVol[10]={0};
    char rVol[5]={"78"};
    char acEchoDelay[10]={0};
    char acEchoDelay2[10]={0};
    char acEchoDelay3[10]={0};
    char ctemp[256];
    char cmd[256];
    char mac[20];
    char mac_addr[7];
    char mac_str[20];

    int iIndex,iIndex1;
    int fd;
    char buf[4],rbuf[4];
    unsigned char uckeyvalue=0,uclastkey=0,startpos=0;
    char readmepath[256];
    char samples[6]={"32000"};

    daemon(0,1);

    signal(SIGPIPE, SIG_IGN);

    memset(mac, 0, 20);

    gstApp.voiceRunMode = audioInit;
    gstApp.audioState = Ainit;
    gstApp.keydwn_close = 0;
    gstApp.keyup_close = 0;
    gstApp.only_one_send = 0;
    gstApp.up_voice_refuse = 0;
    gstApp.dial_num_empty= 0;

    if(pthread_mutex_init(&logmutex, NULL) < 0)
    {
        logmsg_error("init logmutex error\r\n");
        return -1;
    }

    if(pthread_mutex_init(&audiodrivemutex, NULL) < 0)
    {
        logmsg_error("init audiodrivemutex error\r\n");
        return -1;
    }

    updatetime();
    memset(&gstApp, 0, sizeof(gstApp));

    memset(readmepath,0,256);
    sprintf(readmepath,"%sreadme.txt",NandPath);
    if(0 == access(readmepath, F_OK))
    {
        printf("error: nand not mounted\r\n");
        system("reboot");
        return -1;
    }

    if(0 != access(INIFILEPATH, F_OK))
    {
        AutoGenMac(mac);
        create_config_file(mac);
    }
    ver_ctl();
    read_conf_value("ver", gstApp.ver, VER_PATH);

    read_conf_value("MulticastIp", gstApp.acMulticastIp, INIFILEPATH);
    read_conf_value("MAC", mac, INIFILEPATH);
    read_conf_value("LocalIp", gstApp.acLocalIp, INIFILEPATH);
    read_conf_value("samples", samples, INIFILEPATH);
    read_conf_value("Netmask", gstApp.acNetMask, INIFILEPATH);
    read_conf_value("Gatway", gstApp.acGateWay, INIFILEPATH);
    read_conf_value("DHCPC", gstApp.acDhcpc, INIFILEPATH);
    read_conf_value("SoundMode", (char *)aPar, INIFILEPATH);
    read_conf_value("HardAecWhenTalk", (char *)(aPar+1), INIFILEPATH);
    read_conf_value("SoftAec", (char *)(aPar+2) , INIFILEPATH);

    read_conf_value("MicVol", acMicVol , INIFILEPATH);
    read_conf_value("AudioVol", acAudioVol , INIFILEPATH);
    read_conf_value("rVol", rVol , INIFILEPATH);
    read_conf_value("EchoDelay", acEchoDelay , INIFILEPATH);
    read_conf_value("EchoDelay2", acEchoDelay2 , INIFILEPATH);
    read_conf_value("EchoDelay3", acEchoDelay3 , INIFILEPATH);

    read_conf_value("SoftAgc", (char *)(aPar+3) , INIFILEPATH);
    read_conf_value("SoftNs", (char *)(aPar+4) , INIFILEPATH);
    read_conf_value("PcmWriteFile", (char *)(aPar+5) , INIFILEPATH);
    read_conf_value("AecMode", (char *)(aPar+6) , INIFILEPATH);
    read_conf_value("SoftAec2", (char *)(aPar+7) , INIFILEPATH);
    read_conf_value("SoftAec3", (char *)(aPar+8) , INIFILEPATH);

    read_conf_value("FilterLowVol", (char *)(aPar+10) , INIFILEPATH);

    giMicVol=atoi(acMicVol);
    gstApp.rVol=atoi(rVol);
    giAudioVol=atoi(acAudioVol);
    giEchoDelay=atoi(acEchoDelay);
    giEchoDelay2=atoi(acEchoDelay2);
    giEchoDelay3=atoi(acEchoDelay3);
    gstApp.samples = atoi(samples);

    u32AiVqeType = aPar[0]-0x30;  
    u32Aec = aPar[1]-0x30;
    u32ifuseAec=aPar[2]-0x30;
    giSoftAgc=aPar[3]-0x30;
    giSoftNs =aPar[4]-0x30;
    giPcmWriteFile=aPar[5]-0x30;
    giAecMode = aPar[6]-0x30;

    u32ifuseAec2=aPar[7]-0x30;
    u32ifuseAec3=aPar[8]-0x30;

    printf("ver:%s\r\n",gstApp.ver);
    printf("rVol:%d\r\n",gstApp.rVol);
    printf("u32AiVqeType,u32Aec,u32ifuseAec:%d %d %d \r\n",u32AiVqeType,u32Aec,u32ifuseAec);
    printf("giMicVol,giAudioVol,giEchoDelay:%d %d %d \r\n",giMicVol,giAudioVol,giEchoDelay);
    printf("giSoftAgc,giSoftNs,giPcmWriteFile:%d %d %d \r\n",giSoftAgc,giSoftNs,giPcmWriteFile);

    printf("samples:%d\r\n",gstApp.samples);

    printf("u32ifuseAec1:%d\r\n",u32ifuseAec);
    printf("u32ifuseAec2:%d\r\n",u32ifuseAec2);
    printf("u32ifuseAec3:%d\r\n",u32ifuseAec3);

    printf("giEchoDelay1:%d\r\n",giEchoDelay);
    printf("giEchoDelay2:%d\r\n",giEchoDelay2);
    printf("giEchoDelay3:%d\r\n",giEchoDelay3);

    printf("giAecMode:%d\r\n",giAecMode);

    memset(ctemp, 0, 256);
    read_conf_value("FilePlayVol", ctemp, INIFILEPATH);
    gstApp.iVol = atoi(ctemp);
    read_conf_value("ServerIp", gstApp.acServerIp, INIFILEPATH);
    system("ifconfig eth0 down");
    memset(cmd, 0, 256);
    sprintf(cmd, "ifconfig eth0 hw ether %s", mac);
    system(cmd);
    system("ifconfig eth0 up");

    memset(mac_addr, 0, 7);
    get_mac_addr("eth0", mac_addr);
    sprintf(mac_str, "%02x:%02x:%02x:%02x:%02x:%02x",mac_addr[0],
            mac_addr[1],mac_addr[2],mac_addr[3],mac_addr[4],mac_addr[5]);
    if(0 != strcmp(mac_str, mac))
    {
        write_conf_value("MAC", mac_str, INIFILEPATH);
    }
    if(gstApp.acDhcpc[0]=='0')
    {
        memset(cmd, 0, 256);
        sprintf(cmd, "ifconfig eth0 %s netmask %s", gstApp.acLocalIp, gstApp.acNetMask);
        system(cmd);
        memset(cmd, 0, 256);
        sprintf(cmd, "route add default gw %s", gstApp.acGateWay);
        system(cmd);
    }
    else
    {
        system("udhcpc");
    }
    set_gpio_value(5*8+0, 1);

    if (pipe(gstApp.pipeForAudioFd) == -1)
    {
        perror("pipe create error\n");
        exit(1);
    }

    if (pthread_create(&gstApp.thread_heatbeat_id, NULL, thread_heatbeat_execute, NULL))
    {
        logmsg_error("[%s:%d]falied to create thread:thread_heatbeat_execute\r\n",__FUNCTION__, __LINE__);
        exit(-1);
    }

    if (pthread_create(&gstApp.thread_fileplay_id, NULL, thread_udpserver_execute, NULL))
    {
        logmsg_error("[%s:%d]falied to create thread:thread_udpserver_execute\r\n",__FUNCTION__, __LINE__);
        exit(-1);
    }

    if (pthread_create(&gstApp.thread_audio_pro_main_id, NULL, thread_audio_execute, NULL))
    {
        logmsg_error("[%s:%d]failed to create thread:thread_audio_execute\r\n",__FUNCTION__, __LINE__);
        exit(-1);
    }

    logmsg_log("system init\r\n");
    static int c=0;
    while(1)
    {
        if (++c == 300){
            printf("gstApp.voiceRunMode: %d\n\r", gstApp.voiceRunMode);
            printf("gstApp.audioState: %d\n\r", gstApp.audioState);
            printf("gstApp.PlayState: %d\n\r", gstApp.PlayState);
            c =0;}

        if(get_logfile_size()>10*1024*1024)
        {
            system("rm -rf /mnt/nand/brdcastmain_log.txt");
        }
        if(GetTickCount()>=13000 && (istartsd==0))
        {
            system("mount -t vfat /dev/mmcblk0p1 /mnt/mmc");
            sync();
            memset(readmepath,0,256);
            sprintf(readmepath,"%sreadme.txt",strWavPath);
            if(0 == access(readmepath, F_OK))
            {
                logmsg_error("[%s:%d]mount sd card failed\r\n", __FUNCTION__, __LINE__);
                system("mount -t vfat /dev/mmcblk0p1 /mnt/mmc");
                sync();
                memset(readmepath,0,256);
                sprintf(readmepath,"%sreadme.txt",strWavPath);
                if(0 == access(readmepath, F_OK))
                {
                    logmsg_error("[%s:%d]mount sd card failed\r\n", __FUNCTION__, __LINE__);
                }
                else
                {
                    istartsd=1;
                }
            }
            else
            {
                istartsd=1;
            }
        }

        if (!get_gpio_value(guiGpioNum_up)){
            gstApp.keyup_close = 1; 
            gstApp.only_one_send = 0;
        }else  gstApp.keyup_close = 0;

        if (!get_gpio_value(guiGpioNum_dwn)) {
            gstApp.keydwn_close = 1; }
        else  gstApp.keydwn_close = 0;

        /* 加打印语句主要是为了工艺按键测试*/
        if ( gstApp.keyup_close == 0 && gstApp.ServerAudioPort )
        {
            if ((!gstApp.voiceRunMode ||
                        gstApp.voiceRunMode == monitor) &&
                    !gstApp.only_one_send){
                write(gstApp.pipeForAudioFd[1], KEYUP, sizeof(KEYUP));
                gstApp.only_one_send = 1;
                printf("key:diaodu\n\r");
            }
        }
        else if(gstApp.keydwn_close == 0)
        {
            if (!gstApp.voiceRunMode || gstApp.voiceRunMode == monitor) {
                write(gstApp.pipeForAudioFd[1], KEYDWN, sizeof(KEYDWN));
                printf("key:zubo\n\r");
            }
        }

        uckeyvalue = 0;
        for(iIndex=0; iIndex<4; iIndex++)
        {   memset(buf, 0, 4);
            for(iIndex1 =0; iIndex1<4; iIndex1++)
            {
                if(iIndex1 != iIndex)
                {
                    buf[iIndex1] = 1;
                }
                else
                {    buf[iIndex1] = 0;

                }
            }
            fd = open("/dev/keygpiodev", O_RDWR);
            write(fd, buf, 4);
            close(fd);
            fd = open("/dev/keygpiodev", O_RDWR);
            memset(rbuf, 0, 4);
            read(fd, rbuf, 4);
            close(fd);
            if((rbuf[0] == 1) &&
                    (rbuf[1] == 1) &&
                    (rbuf[2] == 1) &&
                    (rbuf[3] == 1))
            {
                continue;
            }
            uckeyvalue = (1<<(7-iIndex)) | (rbuf[0]<<3) | (rbuf[1]<<2) | (rbuf[2]<<1) | (rbuf[3]<<0);
        }
        //  1(135)            2(139)         3(141)           F1(142)
        //  4 (71)            5(75)          6(77)            F2(78)
        //  7(39)             8(43)          9(45)            F3(46)
        //  呼叫(23)          0 (27)         挂断(29)         F4(30)
        if(!((uckeyvalue== 135) ||
                    (uckeyvalue== 139) ||
                    (uckeyvalue== 141) ||
                    (uckeyvalue== 142) || 
                    (uckeyvalue== 71) || 
                    (uckeyvalue== 75) ||
                    (uckeyvalue== 77) ||
                    (uckeyvalue== 78) ||
                    (uckeyvalue== 39) || 
                    (uckeyvalue== 43) || 
                    (uckeyvalue== 45) ||
                    (uckeyvalue== 46) || 
                    (uckeyvalue== 23) ||
                    (uckeyvalue== 27) ||
                    (uckeyvalue== 29) || 
                    (uckeyvalue== 30))) {
            uckeyvalue=0;
        }

        if(uckeyvalue !=uclastkey)
        {
            uclastkey = uckeyvalue;

            if(uckeyvalue== 135)
            {
                gstApp.acDialNumber[startpos] = 1+48;
                startpos = (startpos+1)%20;
                printf("key:1\n\r");
            }
            else if(uckeyvalue== 139)
            {
                gstApp.acDialNumber[startpos] = 2+48;
                startpos = (startpos+1)%20;
                printf("key:2\n\r");
            }
            else if(uckeyvalue== 141)
            {
                gstApp.acDialNumber[startpos] = 3+48;
                startpos = (startpos+1)%20;
                printf("key:3\n\r");
            }
            else if(uckeyvalue== 71)
            {
                gstApp.acDialNumber[startpos] = 4+48;
                startpos = (startpos+1)%20;
                printf("key:4\n\r");
            }
            else if(uckeyvalue== 75)
            {
                gstApp.acDialNumber[startpos] = 5+48;
                startpos = (startpos+1)%20;
                printf("key:5\n\r");
            }
            else if(uckeyvalue== 77)
            {
                gstApp.acDialNumber[startpos] = 6+48;
                startpos = (startpos+1)%20;
                printf("key:6\n\r");
            }
            else if(uckeyvalue== 39)
            {
                gstApp.acDialNumber[startpos] = 7+48;
                startpos = (startpos+1)%20;
                printf("key:7\n\r");
            }
            else if(uckeyvalue== 43)
            {
                gstApp.acDialNumber[startpos] = 8+48;
                startpos = (startpos+1)%20;
                printf("key:8\n\r");
            }
            else if(uckeyvalue== 45)
            {
                gstApp.acDialNumber[startpos] = 9+48;
                startpos = (startpos+1)%20;
                printf("key:9\n\r");
            }
            else if(uckeyvalue== 27)
            {
                gstApp.acDialNumber[startpos] = 0+48;
                startpos = (startpos+1)%20;
                printf("key:0\n\r");
            }
            else if(uckeyvalue== 23)//呼叫
            {
                if(startpos>0)
                {
                    if (gstApp.voiceRunMode == audioInit ||
                            gstApp.voiceRunMode == monitor ){
                        printf("dial request\n");
                        write(gstApp.pipeForAudioFd[1], KEYDIAL, sizeof(KEYDIAL));
                    }
                    startpos = 0;
                }
                printf("key:huojiao\n\r");
            }
            else if(uckeyvalue == 29)
            {
                startpos = 0;
                memset(gstApp.acDialNumber,0,25);
                write(gstApp.pipeForAudioFd[1], 
                        KEYDIALEND, sizeof(KEYDIALEND));
                printf("key:guaduan\n\r");
            }
            else if(uckeyvalue == 142) //F1
            {
                if((startpos == 4) && (gstApp.acDialNumber[0]== 48+8) 
                        && (gstApp.acDialNumber[1]== 48+8)
                        && (gstApp.acDialNumber[2]== 48+8) 
                        && (gstApp.acDialNumber[3]== 48+8))
                {
                    set_gpio_value(guiGpioNum_LEDRED, 1);
                    set_gpio_value(guiGpioNum_GREEN , 1);
                    system("rm -rf /mnt/nand/brdcastmain.ini");
                    create_config_file(mac);
                    system("reboot");
                }
                startpos = 0;
                memset(gstApp.acDialNumber,0,25);
                printf("key:F1\n\r");
            }
            else if(uckeyvalue == 78) //F2
            {
                startpos = 0;
                memset(gstApp.acDialNumber,0,25);
                printf("key:F2\n\r");
            }
            else if(uckeyvalue == 46) //F3
            {
                startpos = 0;
                memset(gstApp.acDialNumber,0,25);
                printf("key:F3\n\r");
            }
            else if(uckeyvalue == 30) //F4
            {
                startpos = 0;
                memset(gstApp.acDialNumber,0,25);
                printf("key:F4\n\r");
            }
        }
        msleep(50); 
    }
    close(gstApp.pipeForAudioFd[1]); 
    return 0;
}


