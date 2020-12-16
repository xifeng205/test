#ifndef __APP_COMMON__
#define __APP_COMMON__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>                                                                                                                                                                  
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <sys/time.h>
#include <unistd.h>

typedef enum runMode{
    audioInit = 0, 
    genAudio_up,
    genAudio_dwn,
    iDialingFlag,
    monitor,
    monitorAndGenAudio_dwn,
    monitorAndDialingFlag,
}runMode;

typedef enum playState{
        MExit = 0,
        MStop,
        MPlay,
        MiAudioFlag,
}playState;

typedef enum audioState{
        Ainit = 0,
        Asong,
        Aaudio,
        Aring
}audioState;


typedef struct tag_stApp{
    int sckfd_udpserver;
    int sendrecvsockfd;
    int sckfd_heatbeat;
    int linktoServer;

    char up_voice_refuse;

    char dial_voice_refuse;
    char dial_num_empty;

     int ServerAudioPort;

    char acWavNamePlaying[256];
    char        acTempFile[256];
    unsigned int uifileSampleRate;

    pthread_t    threadt_ring;
    pthread_t    threadt_playwav;
    pthread_t    thread_fileplay_id;
    pthread_t    thread_audio_pro_main_id;
    pthread_t    thread_audio_in_id;
    pthread_t    thread_heatbeat_id;

    unsigned int ssrc;
    int iVol;
    int rVol;
    char ver[20];

    runMode  voiceRunMode;
    playState PlayState;
    audioState audioState;

     int keyup_close;
    int keydwn_close;
        unsigned int uiSample_Common_Init_Word;
        unsigned int uiAudio_In_Init_Word;
        unsigned int uiAudio_Out_Init_Word;

        char acLocalIp[256];
        char acNetMask[256];
        char acDhcpc[256];
        char acServerIp[256];
    char acMulticastIp[30];
    char acGateWay[256];
    int samples;

    char acDialNumber[25];
    char acPeerDialIP[256];

    unsigned char only_one_send;
    int  iMaskSound;
    int pipeForAudioFd[2];
}stApp;


#define PORT_UDP_SERVER_AUDIO              20000
#define PORT_UDP_SERVER_AUDIO_FILE         20001
#define UDP_FC_VOL_SET                     0x0001
#define UDP_FC_FILE_DW                     0x0002
#define UDP_FC_WAV_START                   0x0004
#define UDP_FC_WAV_END                     0x0005
#define UDP_FC_WAV_PAUSE                   0x0006
#define UDP_FC_WAV_RESM                    0x0007
#define UDP_FC_MD_SERVERIP                 0x0008
#define UDP_FC_MD_LOCALIP                  0x0009
#define UDP_FC_MD_MULICASTIP               0x000a
#define UDP_FC_MD_DHCP                     0x000b
#define UDP_FC_REBOOT                      0x000c
#define UDP_FC_DIAIL                       0x000d
#define UDP_FC_READCONFIG                  0x000e
#define UDP_FC_WAV_DELETE                  0x000f
#define UDP_FC_VOICE_COMMUNICATION         0x0010 
#define UDP_FC_DIAL_VOICE_COMMUNICATION    0x0011 
#define UDP_FC_BRD_COMMUNICATION           0x0012 
#define UDP_FC_MONITOR_COMMUNICATION       0x0013 
#define UDP_FC_MD_SAMPLES                  0x0014

#define UDP_FC_REQUESTPORT                 0x1008

// =================================================
#define VOICE_COMMUNCIATE_REQUEST          0x01
#define VOICE_COMMUNCIATE_ACCEPT           0x02
#define VOICE_COMMUNCIATE_REFUSE           0x03
#define VOICE_COMMUNCIATE_END              0x04
// =================================================
// =================================================
#define BRD_COMMUNCIATE_REQUEST          0x01
#define BRD_COMMUNCIATE_ACCEPT           0x02
#define BRD_COMMUNCIATE_REFUSE           0x03
#define BRD_COMMUNCIATE_END              0x04
// =================================================
#define MONITOR_COMMUNCIATE_REQUEST          0x01
#define MONITOR_COMMUNCIATE_ACCEPT           0x02
#define MONITOR_COMMUNCIATE_REFUSE           0x03
#define MONITOR_COMMUNCIATE_END              0x04
// =================================================



// =================================================
#define DIAL_VOICE_COMMUNCIATE_REQUEST      0x01
#define DIAL_VOICE_COMMUNCIATE_ACCEPT       0x02
#define DIAL_VOICE_COMMUNCIATE_REFUSE       0x03
#define DIAL_VOICE_COMMUNCIATE_END          0x04
// =================================================
#define  KEYUP           "ikeyup"
#define  KEYDWN           "ikeydn"
#define  KEYDIAL         "ikeydial"
#define  KEYDIALEND      "ikdialend"
// =================================================

#define MAX(a,b)                        ((a)>(b)?(a):(b))
#define MIX(a,b)                        ((a)<(b)?(a):(b))


#define WORD_AUDIOUSE_FOR_AUDIO_OUT      1
#define WORD_AUDIOUSE_FOR_AUDIO_FILE    (1<<1)
#define WORD_AUDIOUSE_FOR_AUDIO_IN     (1<<2)

extern void *thread_audio_execute(void *arg);
extern void *thread_udpserver_execute(void *arg);
extern void *thread_heatbeat_execute(void *arg);
// extern sem_t play_sync_audio;
// extern sem_t audio_sync_play;



#endif
