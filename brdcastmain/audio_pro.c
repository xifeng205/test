#include <stdlib.h>
#include <stdio.h>
#include "stdint.h"

#include "stddef.h"
#include <assert.h>

#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <pthread.h>
#include <errno.h>
#include <signal.h>
#include <sys/time.h>

#include <syslog.h>
#include <ifaddrs.h>  
#include <arpa/inet.h>  
#include <semaphore.h>

#include "app_common.h"
#include "ring.h"

#include "sample_comm.h"
#include <math.h>
#include "acodec.h"
#include "rhfunc.h"
#include "webrtc_AecAnsAgc_processing.h"

#define CNTCNT 300
#define IS_DIAL_CNT 1200
#define IS_UP_CNT 1200

#define IGNORE_PARAM(x) ((x) = (x))
#define VQE_SUPPORT
#define  AUDIO_BUF_LEN          640 
extern sem_t audio_sync_play;

static int sample_div = 1;

extern stApp gstApp;
unsigned int gssrc; // for RTP packet

#ifdef VQE_SUPPORT
/* 0: close, 1: talk, 2: hifi, 3: record*/
HI_U32 u32AiVqeType = 3;  
HI_U32 u32Aec = 1;
#endif
extern unsigned int u32ifuseAec;
extern unsigned int u32ifuseAec2;
extern unsigned int u32ifuseAec3;

extern int  giEchoDelay;
extern int  giEchoDelay2;
extern int  giEchoDelay3;

extern int  giSoftAgc;
extern int  giSoftNs;
extern int  giAecMode;

extern int          giPcmWriteFile;

extern int giMicVol;

extern pthread_mutex_t audiodrivemutex;

extern void dial_number_end(void);
extern void brd_communciation_udp_end(void);
unsigned int guiGpioNum_LEDRED  = 9*8+6;
unsigned int guiGpioNum_GREEN = 9*8+5;
extern   void set_gpio_value(int igpionum, int ilevel);
extern const char *strWavPath ;

unsigned char echobuf[1024]={0};
unsigned long ulechotime = 0;

HI_S16 s16ERLBand[6] = {4, 6, 36, 49, 50, 51};
HI_S16 s16ERL[7] = {7, 10, 16, 10, 18, 18, 18};

HI_S32 RTPpacket(unsigned char *pack,
        unsigned char *data,
        int size, 
        unsigned int sequ,
        HI_U64 tstamp)
{
    int offset = 0, i;
    *(pack + (offset ++) )= 0x80;//v:2,p:0,x:0,cc:0	

    *(pack + (offset ++)) = 0x60;//M;0,PT:96

    *(pack + (offset ++)) = sequ>>8;
    *(pack + (offset ++)) = sequ&0xff;

    for(i = 0;i < 4;i++)
    {
        *(pack + offset + i) = (tstamp >> (8 *(3-i))) & 0xff;
        *(pack + offset + i + 4) = (gssrc >> (8*(3-i))) & 0xff;
        *(pack + i + 8) = 0x00;
    }
    offset += (i*2);
    pack += offset;
    memcpy(pack, data, size);
    return  size + offset;
}

HI_S32 audio_in_init(void)
{

    HI_S32 i, j, s32Ret;
    AUDIO_DEV   AiDev = SAMPLE_AUDIO_AI_DEV;
    AI_CHN      AiChn;
    HI_S32      s32AiChnCnt;
    HI_S32      s32AencChnCnt;
    AENC_CHN    AeChn;
    AIO_ATTR_S stAioAttr;
#ifdef VQE_SUPPORT
    AI_TALKVQE_CONFIG_S stAiVqeTalkAttr;
    AI_HIFIVQE_CONFIG_S stAiVqeHifiAttr;
    AI_RECORDVQE_CONFIG_S stAiVqeRecordAttr;
    HI_VOID     *pAiVqeAttr = NULL;
#endif 
    stAioAttr.enSamplerate   = gstApp.samples;
    stAioAttr.enBitwidth     = AUDIO_BIT_WIDTH_16;
    stAioAttr.enWorkmode     = AIO_MODE_I2S_MASTER;
    stAioAttr.enSoundmode    = AUDIO_SOUND_MODE_MONO;
    stAioAttr.u32EXFlag      = 0;
    stAioAttr.u32FrmNum      = 30;
    stAioAttr.u32PtNumPerFrm = SAMPLE_AUDIO_PTNUMPERFRM/sample_div;
    stAioAttr.u32ChnCnt      = 1;
    stAioAttr.u32ClkSel      = 0;

#ifdef VQE_SUPPORT

    if ((1 == u32AiVqeType)  && (u32Aec==0))
    {
        memset(&stAiVqeTalkAttr, 0, sizeof(AI_TALKVQE_CONFIG_S));
        stAiVqeTalkAttr.s32WorkSampleRate    = AUDIO_SAMPLE_RATE_8000;
        stAiVqeTalkAttr.s32FrameSample       = SAMPLE_AUDIO_PTNUMPERFRM / sample_div;
        stAiVqeTalkAttr.enWorkstate          = VQE_WORKSTATE_COMMON;
        stAiVqeTalkAttr.stAecCfg.bUsrMode    = HI_FALSE;
        stAiVqeTalkAttr.stAecCfg.s8CngMode   = 0;
        stAiVqeTalkAttr.stAgcCfg.bUsrMode    = HI_FALSE;
        stAiVqeTalkAttr.stAnrCfg.bUsrMode    = HI_FALSE;
        stAiVqeTalkAttr.stHpfCfg.bUsrMode    = HI_TRUE;
        stAiVqeTalkAttr.stHpfCfg.enHpfFreq   = AUDIO_HPF_FREQ_150;
        stAiVqeTalkAttr.stHdrCfg.bUsrMode    = HI_FALSE;

        stAiVqeTalkAttr.u32OpenMask = AI_TALKVQE_MASK_AEC | AI_TALKVQE_MASK_AGC | AI_TALKVQE_MASK_ANR | AI_TALKVQE_MASK_HPF | AI_TALKVQE_MASK_HDR;

        pAiVqeAttr = (HI_VOID *)&stAiVqeTalkAttr;
    }
    else if ((1 == u32AiVqeType)  && (u32Aec==1))
    {
        memset(&stAiVqeTalkAttr, 0, sizeof(AI_TALKVQE_CONFIG_S));

        stAiVqeTalkAttr.s32WorkSampleRate    = AUDIO_SAMPLE_RATE_8000;
        stAiVqeTalkAttr.s32FrameSample       = SAMPLE_AUDIO_PTNUMPERFRM/ sample_div;
        stAiVqeTalkAttr.enWorkstate          = VQE_WORKSTATE_COMMON;
        stAiVqeTalkAttr.stAecCfg.bUsrMode    = 1;
        stAiVqeTalkAttr.stAecCfg.s8CngMode   = 1;
        stAiVqeTalkAttr.stAecCfg.s8NearAllPassEnergy = 1;
        stAiVqeTalkAttr.stAecCfg.s8NearCleanSupEnergy = 2;
        stAiVqeTalkAttr.stAecCfg.s16DTHnlSortQTh = 16384;
        stAiVqeTalkAttr.stAecCfg.s16EchoBandLow = 10;
        stAiVqeTalkAttr.stAecCfg.s16EchoBandHigh = 41;
        stAiVqeTalkAttr.stAecCfg.s16EchoBandLow2 = 47;
        stAiVqeTalkAttr.stAecCfg.s16EchoBandHigh2 = 63;

        memcpy(stAiVqeTalkAttr.stAecCfg.s16ERLBand,s16ERLBand,sizeof(s16ERLBand));
        memcpy(stAiVqeTalkAttr.stAecCfg.s16ERL,s16ERL,sizeof(s16ERL));
        stAiVqeTalkAttr.stAecCfg.s16VioceProtectFreqL = 3;
        stAiVqeTalkAttr.stAecCfg.s16VioceProtectFreqL1 = 6;
        //ANR config
        stAiVqeTalkAttr.stAnrCfg.bUsrMode = 1;
        stAiVqeTalkAttr.stAnrCfg.s16NrIntensity =5;
        stAiVqeTalkAttr.stAnrCfg.s16NoiseDbThr = 45;
        stAiVqeTalkAttr.stAnrCfg.s8SpProSwitch = 0;


        stAiVqeTalkAttr.stAgcCfg.bUsrMode    = HI_FALSE;

        stAiVqeTalkAttr.stHpfCfg.bUsrMode    = HI_TRUE;
        stAiVqeTalkAttr.stHpfCfg.enHpfFreq   = AUDIO_HPF_FREQ_150;
        stAiVqeTalkAttr.stHdrCfg.bUsrMode    = HI_FALSE;

        //stAiVqeTalkAttr.u32OpenMask = AI_TALKVQE_MASK_AEC | AI_TALKVQE_MASK_AGC | AI_TALKVQE_MASK_ANR | AI_TALKVQE_MASK_HPF | AI_TALKVQE_MASK_HDR;
        stAiVqeTalkAttr.u32OpenMask =  AI_TALKVQE_MASK_AGC | AI_TALKVQE_MASK_HPF | AI_TALKVQE_MASK_HDR;

        pAiVqeAttr = (HI_VOID *)&stAiVqeTalkAttr;
    }
    else if (2 == u32AiVqeType)
    {
        memset(&stAiVqeHifiAttr, 0, sizeof(AI_HIFIVQE_CONFIG_S));
        stAiVqeHifiAttr.s32WorkSampleRate    = AUDIO_SAMPLE_RATE_48000;
        stAiVqeHifiAttr.s32FrameSample       = SAMPLE_AUDIO_PTNUMPERFRM/sample_div;
        stAiVqeHifiAttr.enWorkstate          = VQE_WORKSTATE_COMMON;
        stAiVqeHifiAttr.stDrcCfg.bUsrMode    = HI_FALSE;
        stAiVqeHifiAttr.stPeqCfg.bUsrMode    = HI_FALSE;
        stAiVqeHifiAttr.stRnrCfg.bUsrMode    = HI_FALSE;
        stAiVqeHifiAttr.stHdrCfg.bUsrMode    = HI_FALSE;
        stAiVqeHifiAttr.stHpfCfg.bUsrMode    = HI_TRUE;
        stAiVqeHifiAttr.stHpfCfg.enHpfFreq   = AUDIO_HPF_FREQ_150;

        stAiVqeHifiAttr.u32OpenMask = AI_HIFIVQE_MASK_DRC | AI_HIFIVQE_MASK_PEQ | AI_HIFIVQE_MASK_HDR | AI_HIFIVQE_MASK_HPF;
        pAiVqeAttr = (HI_VOID *)&stAiVqeHifiAttr;
    }
    else if (3 == u32AiVqeType)
    {
        memset(&stAiVqeRecordAttr, 0, sizeof(AI_RECORDVQE_CONFIG_S));
        stAiVqeRecordAttr.s32WorkSampleRate    = AUDIO_SAMPLE_RATE_48000;
        stAiVqeRecordAttr.s32FrameSample       = SAMPLE_AUDIO_PTNUMPERFRM/sample_div;
        stAiVqeRecordAttr.enWorkstate          = VQE_WORKSTATE_COMMON;
        stAiVqeRecordAttr.s32InChNum           = 1;
        stAiVqeRecordAttr.s32OutChNum          = 1;
        stAiVqeRecordAttr.enRecordType         = VQE_RECORD_NORMAL;
        stAiVqeRecordAttr.stDrcCfg.bUsrMode    = HI_FALSE;
        stAiVqeRecordAttr.stRnrCfg.bUsrMode    = HI_FALSE;
        stAiVqeRecordAttr.stHdrCfg.bUsrMode    = HI_FALSE;
        stAiVqeRecordAttr.stHpfCfg.bUsrMode    = HI_TRUE;
        stAiVqeRecordAttr.stHpfCfg.enHpfFreq   = AUDIO_HPF_FREQ_80;

        stAiVqeRecordAttr.u32OpenMask = AI_RECORDVQE_MASK_DRC | AI_RECORDVQE_MASK_HDR | AI_RECORDVQE_MASK_HPF | AI_RECORDVQE_MASK_RNR;

        pAiVqeAttr = (HI_VOID *)&stAiVqeRecordAttr;
    }
    else
    {
        pAiVqeAttr = HI_NULL;
    }

#endif 
#if 0
    s32Ret = SAMPLE_COMM_AUDIO_CfgAcodec(&stAioAttr);
    if (HI_SUCCESS != s32Ret)
    {
        goto AIAENC_ERR3;
    }
#endif
    /********************************************
      step 2: start Ai
     ********************************************/
    s32AiChnCnt = stAioAttr.u32ChnCnt;
#ifdef VQE_SUPPORT
    s32Ret = SAMPLE_COMM_AUDIO_StartAi(AiDev, s32AiChnCnt, &stAioAttr, gstApp.samples, HI_FALSE, pAiVqeAttr, u32AiVqeType);
    if (u32AiVqeType != 0) HI_MPI_AI_SetVqeVolume(AiDev, 0, giMicVol);
#else
    s32Ret = SAMPLE_COMM_AUDIO_StartAi(AiDev, s32AiChnCnt, &stAioAttr, gstApp.samples, HI_FALSE, NULL, 0);
#endif
    if (s32Ret != HI_SUCCESS)
    {
        goto AIAENC_ERR3;
    }

    /********************************************
      step 3: start Aenc
     ********************************************/
    s32AencChnCnt = stAioAttr.u32ChnCnt;
    s32Ret = SAMPLE_COMM_AUDIO_StartAenc(s32AencChnCnt, SAMPLE_AUDIO_PTNUMPERFRM/sample_div, PT_LPCM);
    if (s32Ret != HI_SUCCESS)
    {
        goto AIAENC_ERR2;
    }

    /********************************************
      step 4: Aenc bind Ai Chn
     ********************************************/
    for (i = 0; i < s32AencChnCnt; i++)
    {
        AeChn = i;
        AiChn = i; 

        s32Ret = SAMPLE_COMM_AUDIO_AencBindAi(AiDev, AiChn, AeChn);
        if (s32Ret != HI_SUCCESS)
        {
            for (j=0; j<i; j++)
            {
                SAMPLE_COMM_AUDIO_AencUnbindAi(AiDev, j, j);
            }
            goto AIAENC_ERR1;
        }
        logmsg_log("Ai(%d,%d) bind to AencChn:%d ok!\n", AiDev , AiChn, AeChn);
    }
    webrtc_initialize(gstApp.samples, giSoftNs,1,giSoftAgc,2,1,giAecMode,giEchoDelay);
    return s32Ret;
AIAENC_ERR1:
    s32Ret |= SAMPLE_COMM_AUDIO_StopAenc(s32AencChnCnt);
AIAENC_ERR2:
    s32Ret |= SAMPLE_COMM_AUDIO_StopAi(AiDev, s32AiChnCnt, HI_FALSE, HI_FALSE);
AIAENC_ERR3:

    return s32Ret;
}

HI_S32 audio_in_exit(void)
{
    HI_S32 s32Ret,i;
    AI_CHN      AiChn;
    HI_S32      s32AencChnCnt = 1,s32AiChnCnt =1;
    AENC_CHN    AeChn;
    AUDIO_DEV   AiDev = SAMPLE_AUDIO_AI_DEV;

    for (i = 0; i < 1; i++)
    {
        AeChn = i;
        AiChn = i; 
        s32Ret |= SAMPLE_COMM_AUDIO_AencUnbindAi(AiDev, AiChn, AeChn);
    }

    s32Ret |= SAMPLE_COMM_AUDIO_StopAenc(s32AencChnCnt);

    s32Ret |= SAMPLE_COMM_AUDIO_StopAi(AiDev, s32AiChnCnt, HI_FALSE, HI_FALSE);

    webrtc_deinitialize();
    return s32Ret;
}

/******************************************************************************
 * function : get stream from Aenc, send it  to Adec & save it to file
 ******************************************************************************/
const char *writefilePath = "/mnt/mmc/";
int getaverage(short *as,int cnt)
{
    int i; int sum=0;
    for(i=0;i<cnt;i++)
    {
        sum+=abs(as[i]);
    }
    return (sum/cnt);
}

int getMax(short *as,int cnt)
{
    int i; int Max=0;
    Max = as[0];
    for(i=0;i<cnt;i++)
    {
        if (as[i]>Max) Max=as[i];
    }
    return Max;
}

short  g_Vol[8]={0};
int  g_p=0;

void* SAMPLE_AUDIO_AencProc(void* parg)
{
    HI_S32 s32Ret;
    AENC_CHN    AeChn = 0;
    HI_S32 AencFd;
    AUDIO_STREAM_S stStream;
    fd_set read_fds;
    struct timeval TimeoutVal;
    unsigned int send_len;
    unsigned char sendpacket[1024];
    struct sockaddr_in mc_addr;
    int ivol;
    HI_U8* pu8AudioStream = NULL;
    VB_CONF_S stVbConf;
    FILE *fpCpy1=NULL;
    FILE *fpCpy2=NULL;
    FILE *fpCpy3=NULL;

    char acTempFile[256]; 

    char outbuf[AUDIO_BUF_LEN]={0};
    char tempbuf[AUDIO_BUF_LEN];
    char echobuf_temp[AUDIO_BUF_LEN];

    if(gstApp.samples == 8000) sample_div = 4;
    else if(gstApp.samples == 16000) sample_div = 4;
    else if(gstApp.samples == 32000) sample_div = 1;

    int n = 16;
    pthread_detach(pthread_self());
    pu8AudioStream = (HI_U8*)malloc(sizeof(HI_U8) * MAX_AUDIO_STREAM_LEN);
    if (NULL == pu8AudioStream)
    {
        logmsg_error("%s: malloc failed!\n", __FUNCTION__);
        return NULL;
    }
repeat:

    set_gpio_value(guiGpioNum_GREEN,0);
    while(!gstApp.voiceRunMode)
    {
        msleep(5);
    }

    logmsg_log("SAMPLE_AUDIO_AencProc start\r\n", __FUNCTION__);
    //-----------write fle
    if(giPcmWriteFile == 1)
    {
        logmsg_log("SAMPLE_AUDIO_AencProc start giPcmWriteFile == 1\r\n", __FUNCTION__);
        memset(acTempFile, 0, 256);
        sprintf(acTempFile,"%srecord_input.pcm",writefilePath);
        fpCpy1 = fopen(acTempFile, "wb+");
        memset(acTempFile, 0, 256);
        sprintf(acTempFile,"%srecord_echo.pcm",writefilePath);
        fpCpy2 = fopen(acTempFile, "wb+");
        memset(acTempFile, 0, 256);
        sprintf(acTempFile,"%srecord_output.pcm",writefilePath);
        fpCpy3 = fopen(acTempFile, "wb+");
    }
    logmsg_log("SAMPLE_AUDIO_AencProc start 2\r\n", __FUNCTION__);

    //end write
    //speex_echo_state_reset(echo_state);
    memset(&stVbConf, 0, sizeof(VB_CONF_S));
    pthread_mutex_lock(&audiodrivemutex);
    if(gstApp.uiSample_Common_Init_Word == 0)
    {
        s32Ret = SAMPLE_COMM_SYS_Init(&stVbConf);
        if (HI_SUCCESS != s32Ret)
        {
            logmsg_error("[%s:%d]SAMPLE_COMM_SYS_Init failed\r\n",__FUNCTION__, __LINE__);
            pthread_mutex_unlock(&audiodrivemutex);
            goto repeat;
        }
    }
    pthread_mutex_unlock(&audiodrivemutex);
    logmsg_log("SAMPLE_AUDIO_AencProc start3\r\n", __FUNCTION__);
    gstApp.uiSample_Common_Init_Word |= WORD_AUDIOUSE_FOR_AUDIO_IN;
    pthread_mutex_lock(&audiodrivemutex);
    audio_in_init();
    pthread_mutex_unlock(&audiodrivemutex);
    FD_ZERO(&read_fds);
    AencFd = HI_MPI_AENC_GetFd(AeChn);

    ivol =80;
    ioctl(AencFd, ACODEC_SET_INPUT_VOL, &ivol);
    ivol =6;
    ioctl(AencFd, ACODEC_SET_OUTPUT_VOL, &ivol);
    ivol =15;
    ioctl (AencFd,  ACODEC_SET_GAIN_MICL,   &ivol);
    ioctl (AencFd,  ACODEC_SET_GAIN_MICR,   &ivol);
    ivol =0;
    ioctl(AencFd, ACODEC_SET_DACL_VOL, &ivol);
    ioctl(AencFd, ACODEC_SET_DACR_VOL, &ivol);

    ioctl(AencFd, ACODEC_SET_ADCL_VOL, &ivol);
    ioctl(AencFd, ACODEC_SET_ADCR_VOL, &ivol);

    ivol =1;
    ioctl(AencFd, ACODEC_ENABLE_BOOSTL, &ivol);
    ioctl(AencFd, ACODEC_ENABLE_BOOSTR, &ivol);

    FD_SET(AencFd, &read_fds);
    static int cnt = 0;
    static int is_dialing_cnt = 0;
    static int is_up_cnt = 0;
    while (gstApp.voiceRunMode)
    {
        cnt++;
        TimeoutVal.tv_sec = 1;
        TimeoutVal.tv_usec = 0;

        FD_ZERO(&read_fds);
        FD_SET(AencFd, &read_fds);

        s32Ret = select(AencFd + 1, &read_fds, NULL, NULL, &TimeoutVal);
        if (s32Ret < 0)
        {
            logmsg_error("[%s:%d]select error\r\n",__FUNCTION__, __LINE__);
            break;
        }
        else if (0 == s32Ret)
        {
            logmsg_error("[%s:%d]get aenc stream select time out\r\n",__FUNCTION__, __LINE__);
            break;
        }
        if (FD_ISSET(AencFd, &read_fds))
        {
            /* get stream from aenc chn */
            s32Ret = HI_MPI_AENC_GetStream(AeChn, &stStream, HI_FALSE);
            if (HI_SUCCESS != s32Ret )
            {
                logmsg_error("[%s:%d]HI_MPI_AENC_GetStream error\r\n",__FUNCTION__, __LINE__);
                return NULL;
            }

            memcpy(echobuf_temp,echobuf,AUDIO_BUF_LEN / sample_div);
            if(GetTickCount()>ulechotime)
            {
                if(GetTickCount()-ulechotime>800)   memset(echobuf_temp, 0, 1024);
            }
            else
            {
                if(ulechotime-GetTickCount()>800)   memset(echobuf_temp, 0, 1024);
            }

            memcpy(outbuf,(char *)stStream.pStream,stStream.u32Len);

            if((1 == giPcmWriteFile) && fpCpy1  && fpCpy2  && fpCpy3)  
            {
                fwrite(outbuf,1,AUDIO_BUF_LEN / sample_div,fpCpy1);
                fwrite(echobuf_temp,1,AUDIO_BUF_LEN / sample_div,fpCpy2);
            }
            if(u32ifuseAec==1)
            {
                memcpy(tempbuf,outbuf,AUDIO_BUF_LEN / sample_div);
                memset(outbuf,0,AUDIO_BUF_LEN / sample_div);
                webrtc_frame_process(tempbuf,outbuf,echobuf_temp,50,giEchoDelay);
            }
            if(u32ifuseAec2==1)
            {
                memcpy(tempbuf,outbuf,AUDIO_BUF_LEN / sample_div);
                memset(outbuf,0,AUDIO_BUF_LEN / sample_div);
                webrtc_frame_process(tempbuf,outbuf,echobuf_temp,50,giEchoDelay2);
            }

            if(u32ifuseAec3==1)
            {
                memcpy(tempbuf,outbuf,AUDIO_BUF_LEN / sample_div);
                memset(outbuf,0,AUDIO_BUF_LEN / sample_div);
                webrtc_frame_process(tempbuf,outbuf,echobuf_temp,50,giEchoDelay3);
            }

            if((1 == giPcmWriteFile) && fpCpy1  && fpCpy2 &&  fpCpy3)
            {
                fwrite(outbuf,1,AUDIO_BUF_LEN / sample_div,fpCpy3);
            }

            send_len =  RTPpacket(sendpacket,(unsigned char *)outbuf , stStream.u32Len, stStream.u32Seq, stStream.u64TimeStamp);

            /*拔号通话*/
            if(gstApp.voiceRunMode == iDialingFlag || 
                    gstApp.voiceRunMode == monitorAndDialingFlag) {

                is_dialing_cnt++;
                if (is_dialing_cnt == IS_DIAL_CNT){
                    if(gstApp.audioState != Aaudio) {
                        dial_number_end();
                        start_play();
                        printf("The other party is disconnected\n");
                    }
                    is_dialing_cnt =0;
                }

                if (cnt == CNTCNT){
                    printf("dial communction...\n");
                    cnt =0;
                }
                set_gpio_value(guiGpioNum_GREEN,1);
                memset(&mc_addr, 0, sizeof(mc_addr));
                mc_addr.sin_family = AF_INET;
                mc_addr.sin_port = htons(PORT_UDP_SERVER_AUDIO);
                if(inet_pton(AF_INET, gstApp.acPeerDialIP, &mc_addr.sin_addr)<0)
                {
                    logmsg_error("[%s:%d]inet_pton  error\r\n",__FUNCTION__, __LINE__);
                    return NULL;
                }

                if (sendto(gstApp.sendrecvsockfd, sendpacket, send_len, 0,
                            (struct sockaddr *) &mc_addr,
                            sizeof(struct sockaddr_in)) < 0) {
                    logmsg_error("[%s:%d]auido sendto error\r\n",__FUNCTION__, __LINE__);
                }
            }
            /*与调度室通话*/
            if(gstApp.voiceRunMode == genAudio_up)
            {
                if (cnt == CNTCNT){
                    printf("diaodu communcition...\n");
                    cnt =0;}
                if ( gstApp.linktoServer == 0)
                    gstApp.voiceRunMode = audioInit;

                is_up_cnt++;
                if (is_up_cnt == IS_UP_CNT){
                    if(gstApp.audioState == Ainit) {
                        gstApp.voiceRunMode = audioInit; 
                        printf("up is disconnected\n");
                    }
                    is_up_cnt =0;
                } 
                while(gstApp.keyup_close == 1)
                {
                    if(gstApp.voiceRunMode == genAudio_up)
                    {
                        is_up_cnt++;
                        if (is_up_cnt == IS_UP_CNT){
                            if(gstApp.audioState == Ainit) {
                                gstApp.voiceRunMode = audioInit; 
                                start_play();
                                printf("up is disconnected\n");
                            }
                            is_up_cnt =0;
                        }       
                        set_gpio_value(guiGpioNum_GREEN,0);
                        msleep(5);
                    } 
                    else break;   
                }

                set_gpio_value(guiGpioNum_GREEN,1);
                if(gstApp.ServerAudioPort)
                {
                    memset(&mc_addr, 0, sizeof(mc_addr));
                    mc_addr.sin_family = AF_INET;
                    mc_addr.sin_port = htons(gstApp.ServerAudioPort);
                    if(inet_pton(AF_INET, gstApp.acServerIp, &mc_addr.sin_addr)<0)
                    {
                        logmsg_error("[%s:%d]inet_pton error\r\n",__FUNCTION__, __LINE__);
                        return NULL;
                    }
                    if (sendto(gstApp.sendrecvsockfd, sendpacket, send_len, 0,
                                (struct sockaddr *) &mc_addr,
                                sizeof(struct sockaddr_in)) < 0)  {
                        logmsg_error("[%s:%d]auido sendto error\r\n",__FUNCTION__, __LINE__);
                    }
                }
            }
            /*监控模式*/
            if(gstApp.voiceRunMode == monitor || 
                    gstApp.voiceRunMode == monitorAndDialingFlag ||
                    gstApp.voiceRunMode == monitorAndGenAudio_dwn) {
                if ( gstApp.linktoServer == 0)
                    gstApp.voiceRunMode = audioInit;

                if (cnt == CNTCNT){
                    printf("monitor communition...\n");
                    cnt =0;}
                set_gpio_value(guiGpioNum_GREEN,0);
                if(gstApp.ServerAudioPort)
                {
                    memset(&mc_addr, 0, sizeof(mc_addr));
                    mc_addr.sin_family = AF_INET;
                    mc_addr.sin_port = htons(gstApp.ServerAudioPort);
                    if(inet_pton(AF_INET, gstApp.acServerIp, &mc_addr.sin_addr)<0)
                    {
                        logmsg_error("[%s:%d]inet_pton error\r\n",__FUNCTION__, __LINE__);
                        return NULL;
                    }
                    if (sendto(gstApp.sendrecvsockfd, sendpacket, send_len, 0,
                                (struct sockaddr *) &mc_addr,
                                sizeof(struct sockaddr_in)) < 0) 
                    {
                        logmsg_error("[%s:%d]auido sendto error\r\n",__FUNCTION__, __LINE__);
                    }
                }
            }

            /*组内通话*/
            if(gstApp.voiceRunMode == genAudio_dwn ||
                    gstApp.voiceRunMode == monitorAndGenAudio_dwn){
                if (cnt == CNTCNT){
                    printf("group communition...\n");
                    cnt =0;}
                set_gpio_value(guiGpioNum_GREEN,1);

                brd_communciation_udp_end();
                memset(&mc_addr, 0, sizeof(mc_addr));
                mc_addr.sin_family = AF_INET;
                mc_addr.sin_port = htons(PORT_UDP_SERVER_AUDIO);
                if(inet_pton(AF_INET, gstApp.acMulticastIp, &mc_addr.sin_addr)<0)
                {
                    logmsg_error("[%s:%d]inet_pton error\r\n",__FUNCTION__, __LINE__);
                    return NULL;
                }

                setsockopt(gstApp.sendrecvsockfd, IPPROTO_IP, 
                        IP_MULTICAST_TTL, (char*)&n, sizeof(n));
                sendpacket[0] = 0xaa;
                if (sendto(gstApp.sendrecvsockfd, sendpacket, send_len, 0,
                            (struct sockaddr *) &mc_addr,
                            sizeof(struct sockaddr_in)) < 0) {
                    logmsg_error("[%s:%d]auido sendto error\r\n",__FUNCTION__, __LINE__);
                }
            }
            /* finally you must release the stream */
            s32Ret = HI_MPI_AENC_ReleaseStream(AeChn, &stStream);
            if (HI_SUCCESS != s32Ret )
            {
                logmsg_error("[%s:%d] HI_MPI_AENC_ReleaseStream error\r\n",__FUNCTION__, __LINE__);
                return NULL;
            }
        }
    }
    //--writefile
    if(giPcmWriteFile == 1)
    {
        if(fpCpy1) fclose(fpCpy1);
        if(fpCpy2) fclose(fpCpy2);
        if(fpCpy3) fclose(fpCpy3);

        fpCpy1 = NULL;
        fpCpy2 = NULL;
        fpCpy3 = NULL;
    }
    set_gpio_value(guiGpioNum_GREEN,0);
    audio_in_exit();

    //endof writefile
    pthread_mutex_lock(&audiodrivemutex);
    if((gstApp.uiSample_Common_Init_Word & (~WORD_AUDIOUSE_FOR_AUDIO_OUT))==0)
    {
        SAMPLE_COMM_SYS_Exit();
    }
    pthread_mutex_unlock(&audiodrivemutex);
    gstApp.uiSample_Common_Init_Word &= (~WORD_AUDIOUSE_FOR_AUDIO_OUT);
    set_gpio_value(guiGpioNum_GREEN,0);
    goto repeat;
    return NULL;
}
extern int giAudioVol;
HI_S32 audio_out_init(void)
{
    AIO_ATTR_S stAioAttr;
    HI_S32 s32Ret;
    ADEC_CHN    AdChn = 0;
    HI_S32  s32AoChnCnt;
    AO_CHN      AoChn = 0;
    AUDIO_DEV   AoDev = SAMPLE_AUDIO_AO_DEV;

    stAioAttr.enSamplerate   = gstApp.samples;
    stAioAttr.enBitwidth     = AUDIO_BIT_WIDTH_16;
    stAioAttr.enWorkmode     = AIO_MODE_I2S_MASTER;
    stAioAttr.enSoundmode    = AUDIO_SOUND_MODE_MONO;
    stAioAttr.u32EXFlag      = 0;
    stAioAttr.u32FrmNum      = 30;
    stAioAttr.u32PtNumPerFrm = SAMPLE_AUDIO_PTNUMPERFRM/sample_div;
    stAioAttr.u32ChnCnt      = 2;
    stAioAttr.u32ClkSel      = 0;

    s32Ret = SAMPLE_COMM_AUDIO_StartAdec(AdChn, PT_LPCM);
    if (s32Ret != HI_SUCCESS)
    {
        goto ADECAO_ERR3;
    }
    s32AoChnCnt = stAioAttr.u32ChnCnt;

    s32Ret = SAMPLE_COMM_AUDIO_StartAo(AoDev, s32AoChnCnt, &stAioAttr, gstApp.samples, HI_FALSE, NULL, 0);
    if (s32Ret != HI_SUCCESS)
    {
        goto ADECAO_ERR2;
    }
    for(AoChn =0 ; AoChn <=1;  AoChn++)
    {
        s32Ret = SAMPLE_COMM_AUDIO_AoBindAdec(AoDev, AoChn, AdChn);
        if (s32Ret != HI_SUCCESS)
        {
            goto ADECAO_ERR1;
        }
    }
    s32Ret = HI_MPI_AO_SetVolume( AoDev, giAudioVol*127/100-121);
    if (HI_SUCCESS != s32Ret)
    {
        goto ADECAO_ERR0;
    }
    return s32Ret;
ADECAO_ERR0:
    s32Ret = SAMPLE_COMM_AUDIO_AoUnbindAdec(AoDev, AoChn, AdChn);
    if (s32Ret != HI_SUCCESS)
    {
        logmsg_error("[%s:%d]SAMPLE_COMM_AUDIO_AoUnbindAdec error\r\n",__FUNCTION__, __LINE__);
    }

ADECAO_ERR1:
    if(AoChn == 1)
    {
        AoChn =0;
        goto ADECAO_ERR0;
    }
    s32Ret |= SAMPLE_COMM_AUDIO_StopAo(AoDev, s32AoChnCnt, HI_FALSE, HI_FALSE);
    if (s32Ret != HI_SUCCESS)
    {
        logmsg_error("[%s:%d]SAMPLE_COMM_AUDIO_StopAo error\r\n",__FUNCTION__, __LINE__);
    }
ADECAO_ERR2:
    s32Ret |= SAMPLE_COMM_AUDIO_StopAdec(AdChn);
    if (s32Ret != HI_SUCCESS)
    {
        logmsg_error("[%s:%d]SAMPLE_COMM_AUDIO_StopAdec error\r\n",__FUNCTION__, __LINE__);
    }
ADECAO_ERR3:

    return s32Ret;
}
HI_S32 audio_out_exit(void)
{
    HI_S32 s32Ret;
    ADEC_CHN    AdChn = 0;
    HI_S32  s32AoChnCnt =2;
    AO_CHN      AoChn = 0;
    AUDIO_DEV   AoDev = SAMPLE_AUDIO_AO_DEV;

    for(AoChn = 0; AoChn<=1 ; AoChn++)
    {
        s32Ret = SAMPLE_COMM_AUDIO_AoUnbindAdec(AoDev, AoChn, AdChn);
    }
    if (s32Ret != HI_SUCCESS)
    {
        logmsg_error("[%s:%d]SAMPLE_COMM_AUDIO_AoUnbindAdec error\r\n",__FUNCTION__, __LINE__);
    }

    s32Ret |= SAMPLE_COMM_AUDIO_StopAo(AoDev, s32AoChnCnt, HI_FALSE, HI_FALSE);
    if (s32Ret != HI_SUCCESS)
    {
        logmsg_error("[%s:%d]SAMPLE_COMM_AUDIO_StopAo error\r\n",__FUNCTION__, __LINE__);
    }

    s32Ret |= SAMPLE_COMM_AUDIO_StopAdec(AdChn);
    if (s32Ret != HI_SUCCESS)
    {
        logmsg_error("[%s:%d]SAMPLE_COMM_AUDIO_StopAdec error\r\n",__FUNCTION__, __LINE__);
    }
    return s32Ret;
}

void get_ip(char *ip)
{
    int sock;
    struct sockaddr_in sin;
    struct ifreq ifr;
    char *temp_ip = NULL;

    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock == -1)
    {
        perror("socket");
        return;                
    }
    strncpy(ifr.ifr_name, "eth0", strlen("eth0"));
    ifr.ifr_name[strlen("eth0")] = 0;

    if (ioctl(sock, SIOCGIFADDR, &ifr) < 0)
    {
        perror("ioctl");
        close(sock);
        return;
    }

    memcpy(&sin, &ifr.ifr_addr, sizeof(sin));
    temp_ip = inet_ntoa(sin.sin_addr);
    strcpy(ip,temp_ip);
    close(sock);
    return;
}

void open_ao(VB_CONF_S stVbConf) {
    HI_S32 s32Ret;
    logmsg_log("[%s:%d]open ao\r\n",__FUNCTION__, __LINE__);
    gstApp.audioState = Aaudio;
    memset(&stVbConf, 0, sizeof(VB_CONF_S));

    pthread_mutex_lock(&audiodrivemutex);
    if(gstApp.uiSample_Common_Init_Word == 0)
    {  
        s32Ret = SAMPLE_COMM_SYS_Init(&stVbConf);
        if (HI_SUCCESS != s32Ret)
        { 
            gstApp.audioState = Ainit;
            logmsg_error("[%s:%d]SAMPLE_COMM_SYS_Init failed\r\n",__FUNCTION__, __LINE__);
            pthread_mutex_unlock(&audiodrivemutex);
            return;
        }
    }
    gstApp.uiSample_Common_Init_Word |= WORD_AUDIOUSE_FOR_AUDIO_OUT;

    if(gstApp.uiAudio_Out_Init_Word == 0)
    {  
        s32Ret = audio_out_init();
        if (HI_SUCCESS != s32Ret)
        {  
            gstApp.audioState = Ainit;
            if((gstApp.uiSample_Common_Init_Word & (~WORD_AUDIOUSE_FOR_AUDIO_OUT))==0)
            { 
                SAMPLE_COMM_SYS_Exit();
            }

            gstApp.uiSample_Common_Init_Word &= (~WORD_AUDIOUSE_FOR_AUDIO_OUT);
            logmsg_error("[%s:%d]audio_out_init failed\r\n",__FUNCTION__, __LINE__);
            pthread_mutex_unlock(&audiodrivemutex);
            return;
        }
    }
    pthread_mutex_unlock(&audiodrivemutex);
    gstApp.uiAudio_Out_Init_Word |= WORD_AUDIOUSE_FOR_AUDIO_OUT;
}

void close_ao(void){
    memset(echobuf,0,1024);
    logmsg_log("[%s:%d]close ao\r\n",__FUNCTION__, __LINE__);
    pthread_mutex_lock(&audiodrivemutex);
    if((gstApp.uiAudio_Out_Init_Word & (~WORD_AUDIOUSE_FOR_AUDIO_OUT))==0)
    {
        audio_out_exit();
    }
    gstApp.uiAudio_Out_Init_Word &= (~WORD_AUDIOUSE_FOR_AUDIO_OUT);

    if((gstApp.uiSample_Common_Init_Word & (~WORD_AUDIOUSE_FOR_AUDIO_OUT))==0)
    {
        SAMPLE_COMM_SYS_Exit();
    }
    gstApp.uiSample_Common_Init_Word &= (~WORD_AUDIOUSE_FOR_AUDIO_OUT);
    pthread_mutex_unlock(&audiodrivemutex);
}
void *thread_audio_execute(void *arg)
{
    struct ip_mreq multiCast;

    int audio_cnt = 0;
    AUDIO_STREAM_S stAudioStream;
    VB_CONF_S stVbConf;
    HI_S32 s32AdecChn = 0;
    AUDIO_DEV   AoDev = SAMPLE_AUDIO_AO_DEV;
    HI_U8 pu8AudioStream[1024];
    static unsigned char buf[1024];
    struct sockaddr_in local_addr;
    struct sockaddr_in serv_addr;
    char cIp[20];
    char cLocalIp[20];
    struct timeval stTime;
    socklen_t addrlen;
    fd_set stRset;
    char cmd[256];
    int iMax_fd = 0;
    int fd;
    int iRet;
    int len;
    int icountTime=0;
    int iLastVol=0;

    static int brd_cnt = 0;
    HI_S32 s32Ret = HI_SUCCESS;

    pthread_detach(pthread_self());

    srand(0xffffffff);
    gstApp.ssrc = rand();
Recreatsocket:

    gstApp.sendrecvsockfd = socket(AF_INET, SOCK_DGRAM, 0);
    fd = gstApp.sendrecvsockfd;
    if(fd == -1)
    {
        logmsg_error("[%s:%d]create audio socket erro\r\n",__FUNCTION__, __LINE__);
        usleep(5000);

        goto Recreatsocket;
    }

    bzero(&local_addr, sizeof(local_addr));
    local_addr.sin_family = AF_INET;
    local_addr.sin_port = htons(PORT_UDP_SERVER_AUDIO);
    local_addr.sin_addr.s_addr = INADDR_ANY;

    if(bind(fd, (struct sockaddr*)&local_addr, sizeof(local_addr)) == -1) 
    {
        close(fd);
        logmsg_error("[%s:%d]bind socket error UDP  for audio\r\n",__FUNCTION__, __LINE__);
        usleep(5000);
        goto Recreatsocket;
    }

    memset(cmd, 0, 256);
    sprintf(cmd, "route add -net %s netmask 255.255.255.255 eth0", gstApp.acMulticastIp);
    system(cmd);

    multiCast.imr_interface.s_addr = INADDR_ANY;
    multiCast.imr_multiaddr.s_addr = inet_addr(gstApp.acMulticastIp);
    if(multiCast.imr_multiaddr.s_addr == -1) 
    {  
        close(fd);
        perror("ip not a legal multicast address"); 
        usleep(5000);

        goto Recreatsocket;
    }

    if(setsockopt(fd, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char*)&multiCast, sizeof(multiCast))<0)
    {
        perror("setsockopt:IP_ADD_MEMBERSHIP\n");
        usleep(5000);
    }
    pthread_create(&gstApp.thread_audio_in_id, 0, SAMPLE_AUDIO_AencProc, NULL); 
    stAudioStream.pStream = pu8AudioStream;
    memset(stAudioStream.pStream,0,1024);

    while(1)
    {
        FD_ZERO(&stRset);
        stTime.tv_sec = 0;
        stTime.tv_usec = 5*1000;

        FD_SET(fd, &stRset);
        iMax_fd = MAX(iMax_fd, fd);

        iRet = select(iMax_fd + 1, &stRset, NULL, NULL, &stTime);
        if (iRet == -1)
        {  
            /* signal interrupt the select */
            set_gpio_value(guiGpioNum_LEDRED,0);
            if (errno == EAGAIN || errno == EINTR)
            {
                continue;
            }
            close(fd);
            usleep(5000);
            logmsg_error("[%s:%d]udp server socket data error\r\n",__FUNCTION__, __LINE__);
            goto Recreatsocket;
        }
        if (iRet == 0)
        {     
            if(gstApp.audioState == Ainit)
            {
                icountTime=0;
            }
            else if(gstApp.audioState == Aaudio)
            {   
                icountTime++;
                if(icountTime > 40)
                {   
                    icountTime = 0;
                    set_gpio_value(guiGpioNum_LEDRED,0);
                    close_ao();
                    gstApp.audioState = Ainit;
                    start_play();
                }
            }
            set_gpio_value(guiGpioNum_LEDRED,0);
            continue;
        }
        if (FD_ISSET(fd, &stRset))
        {
            memset(buf, 0, 1024);
            addrlen = sizeof(serv_addr);
            len = recvfrom(fd, buf, 1024, 0, (struct sockaddr *)&serv_addr, &addrlen);

            if(buf[0]==0xaa && gstApp.voiceRunMode == genAudio_up) {
                printf("up, dont't interrput\n\r");
                continue;
            }else if(buf[0]!=0xaa && !gstApp.voiceRunMode) {
                printf("illeagal data\n\r");
                continue;
            }else if(buf[0]==0xaa && !gstApp.voiceRunMode) {
                if(brd_cnt == 30){
                    brd_cnt = 0;
                    stop_play();
                }
                brd_cnt++;
            }else if(buf[0]==0xaa && gstApp.voiceRunMode == iDialingFlag) {
                if(brd_cnt == 30){
                    printf("brd enter, dial end\n\r");
                    dial_number_end();
                    brd_cnt = 0;
                }
                brd_cnt++;
            }

            memset(cIp,0,20);
            sprintf(cIp,"%s",inet_ntoa(serv_addr.sin_addr));
            memset(cLocalIp,0,20);
            get_ip(cLocalIp);

            if(0 == strcmp(cIp, cLocalIp)) { continue;}

            set_gpio_value(guiGpioNum_LEDRED,1);
            if (len > 0)
            {
                icountTime = 0;

                if(gstApp.audioState==Ainit){
                    set_gpio_value(guiGpioNum_LEDRED,1);
                    gstApp.audioState = Aaudio;
                    open_ao(stVbConf);
                }else if(gstApp.audioState != Aaudio){
                    continue;
                }

                if(audio_cnt > CNTCNT )
                {
                    audio_cnt =0;
                    printf("audioing...\n\r");
                }
                audio_cnt++;

                memcpy(stAudioStream.pStream, buf+12, len-12);
                memcpy(echobuf, buf+12, len-12);
                ulechotime = GetTickCount();
                stAudioStream.u32Len =  len-12;

                if(gstApp.iVol != iLastVol)
                {
                    iLastVol = gstApp.iVol;
                    if (HI_SUCCESS != HI_MPI_AO_SetVolume( AoDev, giAudioVol*127/100-121))
                    {
                        logmsg_error("[%s:%d] HI_MPI_AO_SetVolume failed!\n", __FUNCTION__, __LINE__);
                    }
                }
                s32Ret = HI_MPI_ADEC_SendStream(s32AdecChn, &stAudioStream, HI_TRUE);
                if (HI_SUCCESS != s32Ret)
                { 
                    logmsg_error("[%s:%d]HI_MPI_ADEC_SendStream failed\r\n",__FUNCTION__, __LINE__);
                    continue;
                } 
            }
        }
    }
}
