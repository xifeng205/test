
/****************************************Copyright (c)****************************************************
**                  
**                                      
**                                 
**
**--------------File Info---------------------------------------------------------------------------------
**  File name :         CtrlUnit.c
**  Last modified Date :
**  Last Version :      V1.01
**  Descriptions :      控制输出单元(电磁阀，声光报警)
**
**--------------------------------------------------------------------------------------------------------
** Created by:          
** Created date:        
** Version:             V1.00
** Descriptions :      
**--------------------------------------------------------------------------------------------------------
** Modified by :        
** Modified date :      
** Version :            
** Descriptions :       
*********************************************************************************************************/
#define CTRL_UNIT_GLOBALS

#include "main.h"
#include <stdlib.h>
//#include "CtrlUnit.h"
#include    "..\cfg_file\TmCan\tmPortsDriv\tm_PortBank\tm_PortBank_target.h"

PSA_RTNCODE_E  PSAInit(struct tag_PSA_PROCESS_S *pstProcess);
PSA_RTNCODE_E  PSAAct(struct tag_PSA_PROCESS_S *pstProcess);
PSA_RTNCODE_E PSAIntv(struct tag_PSA_PROCESS_S *pstProcess);



const INT32U g_au32ValveReg[POS_MAX][MAX_SOLENOID] = {
   {BITNONE,
   	LOWER_CMD_E, SET_CMD_E, ADV_CMD_E, PUSH_CMD_E, FLIP_EX_CMD_E, FLIP_IN_CMD_E, FLIP2_EX_CMD_E, FLIP2_IN_CMD_E, FLIP3_EX_CMD_E, FLIP3_IN_CMD_E, SB_EX_CMD_E, SB_IN_CMD_E, STAB_EX_CMD_E,
   	STAB_IN_CMD_E, SPRAY_CMD_E,BITNONE, BASE_LIFT_CMD_E,BITNONE, SS_EX_CMD_E, SS_IN_CMD_E, LOWER_R_CMD_E, SET_R_CMD_E, BWASH1_CMD_E, BWASH2_CMD_E, TAIL_EX_CMD_E, TAIL_IN_CMD_E,SHUTTER_EX_CMD_E,
   	SHUTTER_IN_CMD_E,PUSH_R_CMD_E,PULL_R_CMD_E,FCANTI_EX_CMD_E,FCANTI_IN_CMD_E},
   {BITNONE,
   	LOWER_CMD_E, SET_CMD_E, ADV_CMD_E, PUSH_CMD_E, FLIP_EX_CMD_E, FLIP_IN_CMD_E, FLIP2_EX_CMD_E, FLIP2_IN_CMD_E, FLIP3_EX_CMD_E, FLIP3_IN_CMD_E, SB_EX_CMD_E, SB_IN_CMD_E, STAB_EX_CMD_E,
   	STAB_IN_CMD_E, SPRAY_CMD_E,BITNONE, BASE_LIFT_CMD_E,BITNONE, SS_EX_CMD_E, SS_IN_CMD_E, LOWER_R_CMD_E, SET_R_CMD_E, BWASH1_CMD_E, BWASH2_CMD_E, TAIL_EX_CMD_E, TAIL_IN_CMD_E,SHUTTER_EX_CMD_E,
   	SHUTTER_IN_CMD_E,PUSH_R_CMD_E,PULL_R_CMD_E,FCANTI_EX_CMD_E,FCANTI_IN_CMD_E},
   {BITNONE,
   	LOWER_CMD_E, SET_CMD_E, ADV_CMD_E, PUSH_CMD_E, FLIP_EX_CMD_E, FLIP_IN_CMD_E, FLIP2_EX_CMD_E, FLIP2_IN_CMD_E, FLIP3_EX_CMD_E, FLIP3_IN_CMD_E, SB_EX_CMD_E, SB_IN_CMD_E, STAB_EX_CMD_E,
   	STAB_IN_CMD_E, SPRAY_CMD_E,BITNONE, BASE_LIFT_CMD_E,BITNONE, SS_EX_CMD_E, SS_IN_CMD_E, LOWER_R_CMD_E, SET_R_CMD_E, BWASH1_CMD_E, BWASH2_CMD_E, TAIL_EX_CMD_E, TAIL_IN_CMD_E,SHUTTER_EX_CMD_E,
   	SHUTTER_IN_CMD_E,PUSH_R_CMD_E,PULL_R_CMD_E,FCANTI_EX_CMD_E,FCANTI_IN_CMD_E},     
};

//static INT32U g_su32CtrlTimer[JOG_CTRL_MAX_CMD];
static INT32U g_u32LPushCtrlTime = 0;
static JOG_SENSOR_INFO_S stJogSnrInfo = {SENSOR_NOVALUE,SENSOR_NOVALUE,0};
static BOOLEAN g_bAutoASQStat = FALSE;
/*********************************************************************************************************
** Function name:           GetShearPosition
** Descriptions:            获取采煤机位置
** input parameters:       
** output parameters:       none
** Returned value:          煤机位置
** Created by:              linguofeng 
** Created Date:            2016-03-09
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
INT8U GetShearPosition(void)
{
    return gu8ShearPos;
}
void SetPhase3PushStat(BOOLEAN bVal)
{
    g_bAutoP3Stat = bVal;
}
/*********************************************************************************************************
** Function name:           SetAutoASQStat
** Descriptions:            设置本架跟机移架状态，执行跟机移架时设置为true，否则设置为false
** input parameters:       
** output parameters:       none
** Returned value:          煤机位置
** Created by:              linguofeng 
** Created Date:            2016-03-22
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
BOOLEAN GetAutoASQStat(void)
{
    return g_bAutoASQStat;
}
void SetAutoASQStat(BOOLEAN bVal)
{
    g_bAutoASQStat = bVal;
}
/*********************************************************************************************************
** Function name:           GetPhase3PushStat
** Descriptions:            获取跟机自动化阶段3跟机执行标志              
** input parameters:        
** output parameters:       none
** Returned value:                  
** Created by:              
** Created date:            2016/03/15
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
*********************************************************************************************************/
BOOLEAN GetPhase3PushStat(void)
{
    return g_bAutoP3Stat;
}
/*********************************************************************************************************
** Function name:           GetShearLenOffset
** Descriptions:            煤机红外发射器距煤机端头距离                 
** input parameters:        
** output parameters:       none
** Returned value:                  
** Created by:              
** Created date:            2016/03/11
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
*********************************************************************************************************/
INT8U GetShearLenOffset(void)
{
    return (GetAutoShearLen()/2 + GetAutoShearLen()%2);
}
/*********************************************************************************************************
** Function name:           GetUpP4StartShield
** Descriptions:            上行阶段4首架移架编号               
** input parameters:        
** output parameters:       none
** Returned value:                  
** Created by:              
** Created date:            2016/03/11
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
*********************************************************************************************************/
INT8U GetUpP4StartShield(void)
{
    return GetAutoUpSnakeMin()-GetShearLenOffset()+GetAutoPhase4Offset();
}
/*********************************************************************************************************
** Function name:           GetDnP4StartShield
** Descriptions:            下行阶段4首架移架编号               
** input parameters:        
** output parameters:       none
** Returned value:                  
** Created by:              
** Created date:            2016/03/11
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
*********************************************************************************************************/
INT8U GetDnP4StartShield(void)
{
    return  GetAutoDownSnakeMax() + GetShearLenOffset()- GetAutoPhase4Offset() ;
}

/*********************************************************************************************************
** Function name:           CheckTaskExist
** Descriptions:            检查任务是否存在
** input parameters:        u32TaskId 任务id
** output parameters:       none
** Returned value:          TRUE存在 FALSE不存在
** Created by:              linguofeng 
** Created Date:            2015-12-17
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
BOOLEAN CheckTaskExist(INT32U u32TaskId)
{
    OS_TCB stTcb;
    BOOLEAN bRet = FALSE;
    if (OS_NO_ERR == OSTaskQuery(u32TaskId,&stTcb))
    {
        bRet = TRUE;
    }
    return bRet;
}
/*********************************************************************************************************
** Function name:           Delete_Task
** Descriptions:            在本任务中删除其他任务
** input parameters:        u32TaskId 任务id
** output parameters:       none
** Returned value:          
** Created by:              linguofeng 
** Created Date:           20160518
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
void Delete_Task(INT32U u32TaskId)
{
    OS_TCB stTcb;

    if (OS_NO_ERR == OSTaskQuery(u32TaskId,&stTcb))
    {	
    	if (stTcb.OSTCBStat == OS_STAT_RDY)
    	{
        	REQUEST_TASK_DEL(u32TaskId);
    	}
    	else
    	{
        	OSTaskDel(u32TaskId);
    	}
    }
}
/*********************************************************************************************************
** Function name:           PressureLessCheck
** Descriptions:            压力小于设定值检测，检测压力小于设置值时，置
** input parameters:        f32SnrVal:传感器压力值; f32SetVal; 设置值;eCmd动作命令;*pu32Stop驱动器动作码
** output parameters:       none
** Returned value:          u32Valve 电磁阀开口
** Created by:              linguofeng 
** Created Date:            2015-07-30
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
static INT32U PressureLessCheck(FP32 f32SnrVal, FP32 f32SetVal, INT32U *pu32Stop,CMD_CODE_E eCmd)
{
    INT32U u32Valve = 0;
    
    VALVE_TBL(u32Valve,SHIELD_POS,eCmd);
    
    if (0 != (*pu32Stop & u32Valve))
    {
        return u32Valve;
    }
    if (f32SnrVal < f32SetVal)
    {       
        CLR_VALVE(u32Valve);
        *pu32Stop |= u32Valve;
    }    
    return u32Valve;
}
/*********************************************************************************************************
** Function name:           PressureNoLessCheck
** Descriptions:            压力不小于设定值检测，检测压力小于设置值时，设置pu32Stop
** input parameters:        f32SnrVal:传感器压力值; f32SetVal; 设置值;eCmd动作命令;*pu32Stop驱动器动作码
** output parameters:       none
** Returned value:          none
** Created by:              linguofeng 
** Created Date:            2015-07-30
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
static INT32U PressureNoLessCheck(FP32 f32SnrVal, FP32 f32SetVal, INT32U *pu32Stop,CMD_CODE_E eCmd)
{
    INT32U u32Valve = 0;
    
    VALVE_TBL(u32Valve,SHIELD_POS,eCmd);
    
    if (0 != (*pu32Stop & u32Valve))
    {
        return u32Valve;
    }
    if (f32SnrVal >= f32SetVal)
    {       
        CLR_VALVE(u32Valve);
        *pu32Stop |= u32Valve;
    }    
    return u32Valve;
}

/*********************************************************************************************************
** Function name:           SetShdLeg
** Descriptions:            立柱动作
** input parameters:        u32FntLeg前柱，u32RearLeg后柱
** output parameters:       none
** Returned value:          none
** Created by:              linguofeng 
** Created Date:            2015-07-31
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
static void SetShdLeg(INT32U u32FntLeg,INT32U u32RearLeg)
{
    INT32U u32Valve = 0;
    
    VALVE_TBL(u32Valve,SHIELD_POS,u32FntLeg);
    SET_VALVE(u32Valve);
    if (0 != HAS_REAR_LEG())
    {
        // TODO:更改为后立柱电磁阀口
        VALVE_TBL(u32Valve,SHIELD_POS,u32RearLeg);
        SET_VALVE(u32Valve);
    }
}
/*********************************************************************************************************
** Function name:           ClrShdLeg
** Descriptions:            停止立柱动作
** input parameters:        u32FntLeg前柱，u32RearLeg后柱
** output parameters:       none
** Returned value:          none
** Created by:              linguofeng 
** Created Date:            2015-07-31
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
static void ClrShdLeg(INT32U u32FntLeg,INT32U u32RearLeg)
{
    INT32U u32Valve = 0;
    
    VALVE_TBL(u32Valve,SHIELD_POS,u32FntLeg);
    CLR_VALVE(u32Valve);
    if (0 != HAS_REAR_LEG())
    {
        // TODO:更改为后立柱电磁阀口
        VALVE_TBL(u32Valve,SHIELD_POS,u32RearLeg);
        CLR_VALVE(u32Valve);
    }
}

INT32U SetLPushCtrlTime(INT32U u32Time)
{
    g_u32LPushCtrlTime = u32Time;
    return g_u32LPushCtrlTime;
}
INT32U GetLPushCtrlTime(void)
{
    return g_u32LPushCtrlTime;
}
#if 0

void CtrlUnit_ValveInit(void)
{
    /* 获取当前支架位置,*/
    g_pValveReg = (INT32U *)g_au32ValveReg[SHIELD_POS];
}

static INT32U KeyVal2SolenoidVal(INT32U u32KeyVal)
{
    INT8U u8Loopi = 0;
    INT8U u8MaxItem = sizeof(g_au32KeyValTable)/sizeof(INT32U);
    INT32U u32Ret = 0;

    for ( u8Loopi = 0; u8Loopi < u8MaxItem; u8Loopi++)
    {
        if ( g_au32KeyValTable[u8Loopi] & u32KeyVal)
        {
            u32Ret |= g_pValveReg[u8Loopi];
        }
    }
    
    return u32Ret;
}
#endif
/*********************************************************************************************************
** Function name:          SecTimeCheck 
** Descriptions:           检查支架各部件控制时间参数是否到达设置值
** input parameters:        none
** output parameters:       none
** Returned value:          
** Created by:               linguofeng
** Created Date:            2015-07-24
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
BOOLEAN SecTimeCheck(INT32U u32StartTime,INT32U u32SetTime)
{
    BOOLEAN bRet = FALSE;
    //if ((SEC_TIMER - u32StartTime) > u32SetTime)
	if ((SEC_TIMER - u32StartTime) >= u32SetTime)
    {
        bRet = TRUE;
    }
    return bRet;
}
/*********************************************************************************************************
** Function name:          mSecTimeCheck 
** Descriptions:           检查支架各部件控制时间参数是否到达设置值
** input parameters:        u32StartTime 启动时间；u32SetTime执行时间；单位:ms
** output parameters:       none
** Returned value:          
** Created by:               gaocen
** Created Date:            2015-09-10
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
BOOLEAN mSecTimeCheck(INT32U u32StartTime,INT32U u32SetTime)
{
    BOOLEAN bRet = FALSE;
 
	//if ((MS_TIMER - u32StartTime) > u32SetTime)
	if ((MS_TIMER - u32StartTime) >= u32SetTime)	
    {
        bRet = TRUE;
    }
    return bRet;
}
/*********************************************************************************************************
** Function name:           LastShdActBack
** Descriptions:            动作末架闭环反馈
** input parameters:        none
** output parameters:       none
** Returned value:          
** Created by:               gaocen
** Created Date:            2016-05-12
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
static void LastShdActBack(CONTROL_PKT_S stPkt)
{
	if (AWAY_OPERATOR == stPkt.bAwayOper)
	{
		//pstPkt->u8Area = pstPkt->u8SArea;
		stPkt.u8Area = stPkt.u8SArea-1;			
		NBRCAN_COMM_REP(stPkt.u8CommDir); 
	}	
	stPkt.u8Offset = stPkt.u8NumOper;	
	/*线路状况已验证，无需再判断*/
	tmWrite(stPkt.u8CommDir,0,RH_PORT_REP_BANK,sizeof(CONTROL_PKT_S),(void *)&stPkt,NOT_NEED_ACK);	
}
/*********************************************************************************************************
** Function name:           SendNextShd
** Descriptions:            成组动作发送下一架动作命令
** input parameters:        none
** output parameters:       none
** Returned value:          
** Created by:               linguofeng
** Created Date:            2015-07-24
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
void SendNextShd(PKT_REFRESH_SCN_S stRfhPkt,struct tag_SHILD_COMPONENT_S *pstComp)
{
    if (pstComp->u32Stat & SHD_COMP_SNEXT)
    {
        return;
    }
    if (stRfhPkt.stPkt.u8Area > 0)
    {
        //stRfhPkt.stPkt.u8Area--;
        tmWrite(stRfhPkt.stPkt.u8CommDir,0,stRfhPkt.u32PortAddr,sizeof(CONTROL_PKT_S),
            (void *) &stRfhPkt.stPkt,NOT_NEED_ACK);   
    }
    pstComp->u32Stat |= SHD_COMP_SNEXT;
}
/*********************************************************************************************************
** Function name:           SendNextNull
** Descriptions:            成组动作是否到达下一架动作时间
** input parameters:        none
** output parameters:       none
** Returned value:          
** Created by:               linguofeng
** Created Date:            2015-07-24
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
void SendNextNull(PKT_REFRESH_SCN_S stRfhPkt,struct tag_SHILD_COMPONENT_S *pstComp)
{
    if (pstComp->pfTimeCheck(pstComp->u32StartTime,pstComp->u32DlySendNext))
    {
        pstComp->pfSendNext = SendNextShd;
        pstComp->pfSendNext(stRfhPkt,pstComp);
    }
}
/*********************************************************************************************************
** Function name:           LinkSendNextNull
** Descriptions:            成组联动是否到达下一架动作时间
** input parameters:        none
** output parameters:       none
** Returned value:          
** Created by:               gaocen
** Created Date:            2015-08-24
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
void LinkSendNextNull(PKT_REFRESH_SCN_S stRfhPkt,struct tag_SHILD_LINKAGE_S *pstLkg)
{
    if (pstLkg->pfLTimeCheck(pstLkg->u32LStartTime,pstLkg->u32LDlySendTime))
    {
        pstLkg->pfLSendNext= LinkSendNextShd;
        pstLkg->pfLSendNext(stRfhPkt,pstLkg);
    }
}
/*********************************************************************************************************
** Function name:           LinkSendNextShd
** Descriptions:            成组联动发送下一架动作命令
** input parameters:        none
** output parameters:       none
** Returned value:          
** Created by:               gaocen
** Created Date:            2015-08-24
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
void LinkSendNextShd(PKT_REFRESH_SCN_S stRfhPkt,struct tag_SHILD_LINKAGE_S *pstLkg)
{
    if (pstLkg->u32LStat & LKG_SNEXT)
    {
        return;
    }
    if (stRfhPkt.stPkt.u8Area > 0)
    {
        tmWrite(stRfhPkt.stPkt.u8CommDir,0,stRfhPkt.u32PortAddr,sizeof(CONTROL_PKT_S),
            (void *) &stRfhPkt.stPkt,NOT_NEED_ACK);   
    }
    pstLkg->u32LStat |= LKG_SNEXT;
}
/*********************************************************************************************************
** Function name:           ShdPressureCtrl
** Descriptions:            成组动作当前动作支架压力控制
** input parameters:        none
** output parameters:       none
** Returned value:          
** Created by:               linguofeng
** Created Date:            2015-07-24
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
void ShdPressureCtrl(struct tag_SHILD_COMPONENT_S *pstComp)
{
    INT32U u32Valve = 0;
    if (pstComp->u32Stat & SHD_COMP_TOUT)
    {
        return;
    }
    /* 护帮压力到 */  
    if (pstComp->pfPCheck(pstComp->u8Type))
    {
        VALVE_TBL(u32Valve,SHIELD_POS,pstComp->u8Type);
        CLR_VALVE(u32Valve);
        pstComp->u32Stat |= SHD_COMP_TOUT;        
    }
}
/*********************************************************************************************************
** Function name:           ShdLinkPrsCtrl
** Descriptions:            成组联动当前动作压力控制
** input parameters:        none
** output parameters:       none
** Returned value:          
** Created by:               gaocen
** Created Date:            2015-08-24
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
void ShdLinkPrsCtrl(struct tag_LKG_COMP_S * pstLkgComp)
{
    INT32U u32Valve = 0;
	INT32U u32PrsStat = 0;

	GET_COND_STAT(u32PrsStat,pstLkgComp->u8Type);
    if (pstLkgComp->u32Stat & u32PrsStat)
    {
        return;
    }
    /* 护帮压力到 */  
    // TODO: 压力到
    if (pstLkgComp->pfCompPCheck(pstLkgComp->u8Type))
    {
        VALVE_TBL(u32Valve,SHIELD_POS,pstLkgComp->u8Type);
        CLR_VALVE(u32Valve);
        SET_COND_STAT(pstLkgComp->u32Stat, pstLkgComp->u8Type);       
    }
}
void ShdLinkPrsCtrlNull(struct tag_LKG_COMP_S * pstLkgComp)
{
	return;
}
/*********************************************************************************************************
** Function name:          ShdTimeCtrl 
** Descriptions:            成组动作当前支架时间控制
** input parameters:        none
** output parameters:       none
** Returned value:          
** Created by:               linguofeng
** Created Date:            2015-07-24
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
void ShdTimeCtrl(struct tag_SHILD_COMPONENT_S *pstComp)
{
    INT32U u32Valve = 0;

    if (pstComp->u32Stat & SHD_COMP_TOUT)
    {
        return;
    }
    if (pstComp->pfTimeCheck(pstComp->u32StartTime,pstComp->u32ShdExtTime))
    {
        VALVE_TBL(u32Valve,SHIELD_POS,pstComp->u8Type);
        CLR_VALVE(u32Valve);
        SetErrMsg(pstComp->u32ErrIndex,TRUE,NO_ERRMSG_PARA);
        pstComp->u32Stat |= SHD_COMP_TOUT;
    }
}
/*********************************************************************************************************
** Function name:          ShdLinkTimeCtrl 
** Descriptions:            成组联动当前动作时间控制
** input parameters:        none
** output parameters:       none
** Returned value:          
** Created by:              gaocen
** Created Date:            2015-08-24
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
void ShdLinkTimeCtrl(struct tag_LKG_COMP_S *pstLkgComp)
{
    INT32U u32Valve = 0;
	INT32U u32TimeStat = 0;

	GET_COND_STAT(u32TimeStat,pstLkgComp->u8Type);
    if (pstLkgComp->u32Stat & u32TimeStat)
    {
        return;
    }

    if (pstLkgComp->pfCompTCheck(pstLkgComp->u32BaseTime,pstLkgComp->u32ExtTime))
    {
        VALVE_TBL(u32Valve,SHIELD_POS,pstLkgComp->u8Type);
        CLR_VALVE(u32Valve);
        SetErrMsg(pstLkgComp->u32ErrIndex,TRUE,NO_ERRMSG_PARA);
        SET_COND_STAT(pstLkgComp->u32Stat, pstLkgComp->u8Type);
    }
}
/*********************************************************************************************************
** Function name:          ShdLinkStartCtrl 
** Descriptions:            成组联动当前动作启动控制
** input parameters:        none
** output parameters:       none
** Returned value:          
** Created by:               gaocen
** Created Date:            2015-08-24
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
void ShdLinkStartCtrl(struct tag_LKG_COMP_S *pstLkgComp)
{
    INT32U u32Valve = 0;
	INT32U u32ExeStat = 0;
	
	GET_EXE_STAT(u32ExeStat,pstLkgComp->u8Type);
    if (pstLkgComp->u32Stat & u32ExeStat)
    {
		pstLkgComp->pfCompTCtrl(pstLkgComp);
		pstLkgComp->pfCompPCtrl(pstLkgComp);
		return;
    }

	if (pstLkgComp->pfCompTCheck(pstLkgComp->u32BaseTime,pstLkgComp->u32StartTime))
    {
    	pstLkgComp->u32BaseTime = MS_TIMER;
        VALVE_TBL(u32Valve,SHIELD_POS,pstLkgComp->u8Type);
        SET_VALVE(u32Valve);
		SET_EXE_STAT(pstLkgComp->u32Stat, pstLkgComp->u8Type);
    }
}
/*********************************************************************************************************
** Function name:           InitShieldPosition
** Descriptions:            根据参数设置确定支架的位置:端头架;过渡架;中间架
** input parameters:        none
** output parameters:       none
** Returned value:          
** Created by:               linguofeng
** Created Date:            2015-07-14
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
void InitShieldPosition(void)
{
    INT8U u8CurrShd = GetShieldNum();
    INT8U u8MinShd = GetMinShdNum();
    INT8U u8MinMidShd = GetMinMidShdNum();
    INT8U u8MaxMidShd = GetMaxMidShdNum();
    INT8U u8MinEndShd = GetMinEndShdNum();
    INT8U u8MaxEndShd = GetMaxEndShdNum();
    
    /* 当前支架和参数中的端头架，中间架区间段比较，落在哪个区间段则属于那种支架形式*/
    if ((u8CurrShd <= u8MaxMidShd)&&((u8CurrShd >= u8MinMidShd)))
    {
        g_u32ShdPos = POS_MIDDLE;
    }
    else if (((u8CurrShd < u8MinShd)&&(u8CurrShd > u8MinEndShd))||
        ((u8CurrShd > u8MaxMidShd)&&(u8CurrShd < u8MaxEndShd)))
    {
        g_u32ShdPos = POS_TRANSIT;
    }
    else 
    {
        g_u32ShdPos = POS_HEAD;
    }
}

/*********************************************************************************************************
** Function name:           JogCtrlLower
** Descriptions:           条件执行单控降柱
** input parameters:        none
** output parameters:       none
** Returned value:          
** Created by:              gaocen 
** Created Date:            2015-07-08
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
void JogCtrlLower(void)
{
	CONTROL_PKT_S stCtrlPkt;
    
	/*检查降柱喷雾功能是否开启*/
	if(GetLowerSpryEn())
	{
	    stCtrlPkt.u32CmdCode = SPRAY_CMD_E;
		/*降柱喷雾功能开启执行降柱动作同时执行喷雾动作*/
	    CreateNbrRelatedTask();
        sysMsgPost(gu32NbrRelatedMsg,(INT8U *)&stCtrlPkt.u32CmdCode,0);
        
		/*降柱喷雾功能开启向左右邻架发送顶梁喷雾命令*/
		stCtrlPkt.u8Area = 1;
		stCtrlPkt.u8CmdType = ACTION_CMD_TYPE;
		stCtrlPkt.u8NumOper = 0;
		stCtrlPkt.u8Offset	= 0;		
		tmWrite(CAN_RIGHT,0,RH_PORT_NEIGHBOR_RELATED,sizeof(CONTROL_PKT_S),(void*)&stCtrlPkt,NOT_NEED_ACK);  
		tmWrite(CAN_LEFT,0, RH_PORT_NEIGHBOR_RELATED,sizeof(CONTROL_PKT_S),(void*)&stCtrlPkt,NOT_NEED_ACK); 
	}

	stJogSnrInfo.fp32FormerPrs = GetFormerPropPressure();
	
	return;
}
/*********************************************************************************************************
** Function name:           JogCtrlAdvance
** Descriptions:            条件执行单控移架
** input parameters:        none 
** output parameters:       none
** Returned value:          
** Created by:              gaocen 
** Created Date:            2015-07-08
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
void JogCtrlAdvance(void)	
{
	CONTROL_PKT_S stCtrlPkt;
	
	/*检查移架喷雾功能是否开启*/
	if(GetAdvSpryEn())
	{
		/*移架动作与推溜动作只能操作其一*/
		CLR_VALVE(PUSH_CMD_E);
		
		/*移架喷雾功能开启执行移架动作同时执行喷雾动作*/
		SET_VALVE(SPRAY_CMD_E);
		
		/*构造发送结构体向左右邻架发送顶梁喷雾命令*/
		stCtrlPkt.u32CmdCode = SPRAY_CMD_E;
    	stCtrlPkt.u8Area = 1;
    	stCtrlPkt.u8CmdType = ACTION_CMD_TYPE;
    	stCtrlPkt.u8NumOper = 0;
    	stCtrlPkt.u8Offset  = 0;		
		tmWrite(CAN_RIGHT,0,RH_PORT_NEIGHBOR_RELATED,sizeof(CONTROL_PKT_S),(void*)&stCtrlPkt,NOT_NEED_ACK);  
		tmWrite(CAN_LEFT,0,RH_PORT_NEIGHBOR_RELATED,sizeof(CONTROL_PKT_S),(void*)&stCtrlPkt,NOT_NEED_ACK); 
	}

	stJogSnrInfo.fp32ConvPos = GetConveyorExtens();

	return;
}
/*********************************************************************************************************
** Function name:           JogCtrlSet
** Descriptions:            条件执行单控升柱
** input parameters:        none
** output parameters:       none
** Returned value:          
** Created by:              gaocen 
** Created Date:            2015-07-08
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
void JogCtrlSet(void)	
{
	stJogSnrInfo.fp32FormerPrs = GetFormerPropPressure();

	return;
}
/*********************************************************************************************************
** Function name:           JogCtrlPush
** Descriptions:            条件执行单控推溜
** input parameters:        none
** output parameters:       none
** Returned value:          
** Created by:              gaocen 
** Created Date:            2015-07-08
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
void JogCtrlPush(void)	
{	
	stJogSnrInfo.fp32ConvPos = GetConveyorExtens();
	
	return;
}
/*********************************************************************************************************
** Function name:           JogCtrl1stFlipOut
** Descriptions:            条件执行单控一级护帮伸
** input parameters:        none
** output parameters:       none
** Returned value:          
** Created by:              gaocen 
** Created Date:            2015-07-08
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
void JogCtrl1stFlipOut(void)	
{
	// TODO: 条件执行单控一级护帮伸
	return;
}
/*********************************************************************************************************
** Function name:           JogCtrl1stFlipIn
** Descriptions:            条件执行单控一级护帮收
** input parameters:       none
** output parameters:       none
** Returned value:          
** Created by:              gaocen 
** Created Date:           2015-07-08
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
void JogCtrl1stFlipIn(void)	
{
	// TODO: 条件执行单控一级护帮收
	return;
}
/*********************************************************************************************************
** Function name:           JogCtrl2ndFlipOut
** Descriptions:            条件执行单控二级护帮伸
** input parameters:        none
** output parameters:       none
** Returned value:          
** Created by:              gaocen 
** Created Date:           2015-07-08
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
void JogCtrl2ndFlipOut(void)	
{
	// TODO: 条件执行单控二级护帮伸
	return;
}
/*********************************************************************************************************
** Function name:           JogCtrl2ndFlipIn
** Descriptions:            条件执行单控二级护帮收
** input parameters:        none
** output parameters:       none
** Returned value:          
** Created by:              gaocen 
** Created Date:            2015-07-08
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
void JogCtrl2ndFlipIn(void)	
{
	// TODO: 条件执行单控二级护帮收
	return;
}
/*********************************************************************************************************
** Function name:           JogCtrl3rdFlipOut
** Descriptions:            条件执行单控三级护帮伸
** input parameters:        none
** output parameters:       none
** Returned value:          
** Created by:              gaocen 
** Created Date:            2015-07-08
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
void JogCtrl3rdFlipOut(void)	
{
	// TODO: 条件执行单控三级护帮伸
	return;
}
/*********************************************************************************************************
** Function name:           JogCtrl3rdFlipIn
** Descriptions:            条件执行单控三级护帮收
** input parameters:        none
** output parameters:       none
** Returned value:          
** Created by:              gaocen 
** Created Date:            2015-07-08
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
void JogCtrl3rdFlipIn(void)	
{
	// TODO: 条件执行单控三级护帮收
	return;
}
/*********************************************************************************************************
** Function name:           JogCtrlSlideBarOut
** Descriptions:            条件执行单控伸缩梁伸
** input parameters:       none
** output parameters:       none
** Returned value:          
** Created by:              gaocen 
** Created Date:            2015-07-08
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
void JogCtrlSlideBarOut(void)	
{
	// TODO: 条件执行单控伸缩梁伸
	return;
}
/*********************************************************************************************************
** Function name:           JogCtrlSlideBarIn
** Descriptions:            条件执行单控伸缩梁收
** input parameters:        none
** output parameters:       none
** Returned value:          
** Created by:              gaocen 
** Created Date:            2015-07-08
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
void JogCtrlSlideBarIn(void)	
{
	// TODO: 条件执行单控伸缩梁收
	return;
}
/*********************************************************************************************************
** Function name:           JogCtrlStabOut
** Descriptions:            条件执行单控伸平衡
** input parameters:        none
** output parameters:       none
** Returned value:          
** Created by:              gaocen 
** Created Date:            2015-07-08
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
void JogCtrlStabOut(void)	
{
	// TODO: 条件执行单控伸平衡
	return;
}
/*********************************************************************************************************
** Function name:           JogCtrlStabIn
** Descriptions:            条件执行单控收平衡
** input parameters:        none
** output parameters:       none
** Returned value:          
** Created by:              gaocen 
** Created Date:            2015-07-08
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
void JogCtrlStabIn(void)	
{
	// TODO: 条件执行单控收平衡
	return;
}
/*********************************************************************************************************
** Function name:           JogCtrlSpray
** Descriptions:            条件执行单控喷雾
** input parameters:       none
** output parameters:       none
** Returned value:          
** Created by:              gaocen 
** Created Date:            2015-07-08
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
void JogCtrlSpray(void)	
{
	// TODO: 条件执行单控喷雾
	return;
}
/*********************************************************************************************************
** Function name:           JogCtrlLift
** Descriptions:            条件执行单控抬底
** input parameters:        none
** output parameters:       none
** Returned value:          
** Created by:              gaocen 
** Created Date:            2015-07-08
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
void JogCtrlLift(void)	
{
	// TODO: 条件执行单控抬底
	return;
}

/*********************************************************************************************************
** Function name:           JogCtrlSideSealOut
** Descriptions:            条件执行单控伸侧护
** input parameters:        none
** output parameters:       none
** Returned value:          
** Created by:              gaocen 
** Created Date:            2015-07-08
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
void JogCtrlSideSealOut(void)	
{
	// TODO: 条件执行单控伸侧护
	return;
}
/*********************************************************************************************************
** Function name:           JogCtrlSideSealIn
** Descriptions:            条件执行单控收侧护
** input parameters:        none
** output parameters:       none
** Returned value:          
** Created by:              gaocen 
** Created Date:            2015-07-08
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
void JogCtrlSideSealIn(void)	
{
	// TODO: 条件执行单控收侧护
	return;
}
/*********************************************************************************************************
** Function name:           JogCtrlSnrSend
** Descriptions:            单控压力行程传感器值传送
** input parameters:        pstPkt  :单控动作信息指针
** output parameters:       none
** Returned value:          
** Created by:              gaocen 
** Created Date:            2015-07-08
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
static void JogCtrlSnrSend(CONTROL_PKT_S *pstPkt)	
{

	stJogSnrInfo.u8Offset = pstPkt->u8Offset;
	tmWrite(pstPkt->u8CommDir,0,RH_PORT_NBRINFO,sizeof(JOG_SENSOR_INFO_S),(void*)&stJogSnrInfo,NOT_NEED_ACK);
	stJogSnrInfo.fp32ConvPos = SENSOR_NOVALUE;
	stJogSnrInfo.fp32FormerPrs = SENSOR_NOVALUE;

	return;
}

void (*g_pfJogCtrl[])(void) = {
	FuncNull,
    JogCtrlLower,
	JogCtrlSet,
    JogCtrlAdvance, 
    JogCtrlPush,
    JogCtrl1stFlipOut,
    JogCtrl1stFlipIn,
    JogCtrl2ndFlipOut,
    JogCtrl2ndFlipIn,
    JogCtrl3rdFlipOut,
    JogCtrl3rdFlipIn,
    JogCtrlSlideBarOut,
    JogCtrlSlideBarIn,
    JogCtrlStabOut,
    JogCtrlStabIn,
    JogCtrlSpray,
    FuncNull,
    JogCtrlLift,
    FuncNull, 
    JogCtrlSideSealOut,
    JogCtrlSideSealIn,
};
/*********************************************************************************************************
** Function name:           JogCtrlFunc
** Descriptions:            单控条件执行函数
** input parameters:        
** output parameters:       none
** Returned value:          none
** Created by:              gaocen 
** Created Date:            2015-07-08
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
void JogCtrlFunc(INT8U JogCtrlCmd)
{ 
    INT32U u32MaxCmd = sizeof(g_pfJogCtrl)/4;
    if (JogCtrlCmd >= u32MaxCmd)
    {
        GUI_Printf(0,0,0,"CmdErr=%d",JogCtrlCmd);
        return;
    }
    g_pfJogCtrl[JogCtrlCmd](); 	
}

INT8U Jog_Ctrl_Warning(CONTROL_PKT_S stPkt)
{
    INT8U u8Err = 0;
    OSFlagPost(pstFlagGrp,(OS_FLAGS)WARN_CMD_FLG, OS_FLAG_SET, &u8Err);
    return u8Err;
}
INT8U Jog_Ctrl_StopWarning(CONTROL_PKT_S stPkt)
{
    INT8U u8Err = 0;
    OSFlagPost(pstFlagGrp,(OS_FLAGS)WARN_CMD_FLG, OS_FLAG_CLR, &u8Err);
    return u8Err;
}
static void JogLinkageSpray(INT32U *pu32Valve)
{
    BOOLEAN abSpryEn[3] ;
    INT8U u8Loop = 0;

    abSpryEn[0] = GetLowerSpryEn();
    abSpryEn[1] = GetAdvSpryEn();
    abSpryEn[2] = GetFlipSpryEn();
    if (!CheckTaskExist(TASK_NBRRELATED_ID))
    {
        return;
    }
    for (u8Loop = 0;u8Loop<sizeof(abSpryEn)/sizeof(BOOLEAN);u8Loop++)
    {
        if (abSpryEn[u8Loop])
        {
            *pu32Valve = GET_VALVE() & SPRAY_CMD_E;
        }
    }    
}
INT8U Jog_Ctrl_StopExecute(CONTROL_PKT_S stPkt)
{
    INT32U u32Valve = 0;
    JogLinkageSpray(&u32Valve);

    RST_VALVE();
    SET_VALVE(u32Valve);
    return TRUE;
    
}
 
INT8U Jog_Ctrl_Execute(CONTROL_PKT_S stPkt)
{

	INT32U u32ValveOn;
	INT8U u8JogCmd;
		
	RST_VALVE();
	SET_VALVE(stPkt.u32CmdCode);
	
	for(u8JogCmd=LOWER_LEG_CMD; u8JogCmd<MAX_SOLENOID; u8JogCmd++)
	{
		VALVE_TBL(u32ValveOn,SHIELD_POS,u8JogCmd);  //获取单控动作对应电磁阀位
		if(!(stPkt.u32CmdCode & u32ValveOn))
		{
			continue;
		}
		JogCtrlFunc(u8JogCmd);
	}
	
	JogCtrlSnrSend(&stPkt);    //单控压力行程传感器值传送
	
    return TRUE;
}

static BOOLEAN Check3rdFlipLmtP(INT8U u8Type)
{
    // TODO: 待添加限位判断,压力判断
    return FALSE;
}
static BOOLEAN Check2ndFlipLmtP(INT8U u8Type)
{
    // TODO: 待添加限位判断,压力判断
    return FALSE;
}
static BOOLEAN Check1stFlipLmtP(INT8U u8Type)
{
    // TODO: 待添加限位判断,压力判断
    return FALSE;
} 
static BOOLEAN CheckSlidBarLmtP(INT8U u8Type)
{
    // TODO: 待添加伸缩梁限位判断,压力判断
    return FALSE;
}
static BOOLEAN CheckSprayWaterP(INT8U u8Type)
{
    // TODO: 待添加水压判断
    return FALSE;
}
static BOOLEAN CheckTailLeverLmtP(INT8U u8Type)
{
    // TODO: 待添加尾梁限位判断，压力判断
    return FALSE;
}
static BOOLEAN CheckPlateLmtP(INT8U u8Type)
{
    // TODO: 待添加插板限位判断，压力判断
    return FALSE;
}


/*********************************************************************************************************
** Function name:           IndicatorLEDPassword
** Descriptions:            进入密码输入状态时数字指示灯点亮
** input parameters:        
** output parameters:       none
** Returned value:          none
** Created by:              linguofeng 
** Created Date:            2015-04-13
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
void IndicatorLEDPassword(void)
{
    __GuiLed = LED_1 | LED_2 | LED_3 | LED_4 | LED_5 | LED_6 |
        LED_7 | LED_8 | LED_9 | LED_0 | LED_K | LED_M;
}

void IndicatorLEDComm(void)
{
    __GuiLed ^= LED_COMM;
}
void SetCommLED(void)
{
    __GuiLed |= LED_COMM;
}
void ClrCommLED(void)
{
    __GuiLed &= (~LED_COMM);
}
void IndicatorLEDErr(void)
{
    __GuiLed ^= LED_ERR;
}
void ClearLEDErr(void)
{
    __GuiLed &= (~LED_ERR);
}
void IndicatorLEDNull(void)
{
    __GuiLed = BITNONE;
}
void IndicatorLEDNeighborSlt(void)
{
    __GuiLed = BITALL;
    __GuiLed &= (~LED_U)&(~LED_D)&(~LED_B)&(~LED_L)&(~LED_R)&(~LED_Q)&(~LED_ERR);
}
#if 0
void IndicatorLEDBankSlt(void)
{
    __GuiLed = LED_C | LED_G | LED_1 | LED_2 | LED_3 | LED_4 | LED_5 | 
        LED_6 | LED_7 | LED_8 | LED_9 | LED_0 | LED_S | LED_T | LED_B ;
}
#endif
void IndicatorLEDBankSlt(void)/*新添加几个按键指示灯，测试用*/
{
    __GuiLed = LED_C | LED_G | LED_F | LED_H | LED_J | LED_N | LED_S | LED_T | LED_B | 
        LED_1 | LED_2 | LED_3 | LED_4 | LED_5 | LED_6 | LED_7 | LED_8 | LED_9 | LED_0 ;
}

/*********************************************************************************************************
** Function name:           KeyBrdIndicatorLEDUpdate
** Descriptions:            有效按键指示灯刷新
** input parameters:        
** output parameters:       none
** Returned value:          none
** Created by:              linguofeng 
** Created Date:            2015-04-13
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
void KeyBrdIndicatorLEDUpdate(void)
{
    spiWrite(SPI0, (uint8 *)&__GuiLed, 4);
}
/*********************************************************************************************************
** Function name:           SoftWareTimerDiv
** Descriptions:            软件定时分频器，将任务中某功能调度周期分频
** input parameters:        pu32Cnt 已定时时间记录 u32Div 分频因子
** output parameters:       none
** Returned value:          none
** Created by:              linguofeng 
** Created Date:            2015-08-27
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
BOOLEAN SoftWareTimerDiv(INT32U *pu32Cnt, INT32U u32Div)
{
    BOOLEAN bRet = FALSE;
    INT32U u32Divi = u32Div + 1;
    /* 入参检查 */
    if (NULL == pu32Cnt)
    {
        return bRet;
    }
    (*pu32Cnt)++;
    if (((*pu32Cnt) % u32Divi) == 0)
    {
        *pu32Cnt = 0;
         bRet = TRUE;
    }
    return bRet;
}
/*********************************************************************************************************
** Function name:           ExecSoundLightAlarm
** Descriptions:            执行声光报警
** input parameters:        
** output parameters:       none
** Returned value:          none
** Created by:              linguofeng 
** Created Date:            2015-08-27
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
static void ExecSoundLightAlarm(INT8U *pu8Cmd)
{
    INT8U u8Err = 0;
    OS_FLAGS osfWarn = 0;
    
    osfWarn = OSFlagQuery(pstFlagGrp,&u8Err);
    if (0 == (osfWarn & WARN_CMD_FLG))
    {
        *pu8Cmd = STOP_WARNING;
        CTRL_WARNING(*pu8Cmd); 
        return;
    }
    *pu8Cmd = (*pu8Cmd) ^ 1;    
    CTRL_WARNING(*pu8Cmd);    
}
    
/*********************************************************************************************************
** Function name:           Schedual200ms
** Descriptions:            20ms任务的分频子任务
** input parameters:        pu32Cnt 定时时间记录,pu8AlarmCmd声光报警状态寄存器
** output parameters:       none
** Returned value:          none
** Created by:              linguofeng 
** Created Date:            2015-08-27
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
static void Schedual200ms(INT32U *pu32Cnt, INT8U *pu8AlarmCmd)
{

    if (pu32Cnt == NULL)
    {
        ERR_MESSAGE("Schedual200ms para err");
        return;
    }
    
    if (!SoftWareTimerDiv(pu32Cnt,TIME_DLY_200MS/TIME_DLY_20MS))
    {
        return;
    }
	
    ExecSoundLightAlarm(pu8AlarmCmd);

    if (CheckErrMsg())
    {
        IndicatorLEDErr();
    } 
    else
    {
        ClearLEDErr();
    }
}
/*********************************************************************************************************
** Function name:           CommLEDTwinkle
** Descriptions:            执行通讯灯闪烁
** input parameters:        
** output parameters:     none
** Returned value:          none
** Created by:               gaocen 
** Created Date:            2016-04-09
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
static void CommLEDTwinkle()
{

	if (g_u32CommCnt > 0)
	{
		IndicatorLEDComm();
		DEC_COMM_ONCE();
	} 
	else
	{
		ClrCommLED();
	}	

	return;
}

static void SolenoidDriverCtrl(INT32U *pu32Valve)
{
    INT32S s32Ret = 0;
    
    /* 检查急停闭锁状态 */
    if (ESTOP_ACCURED == GetEStopStat())
    {
        *pu32Valve = 0;
    }

    s32Ret = tmWrite(LPC2294_UART0,0,RH_PORT_VALVE_CTRL,sizeof(INT32U),(void *)pu32Valve,NOT_NEED_ACK);
    if (s32Ret < 0)
    {
        ERR_MESSAGE("驱动器连线断    ");
    }    
}
#if 0

/*********************************************************************************************************
** Function name:           TimerCtrl
** Descriptions:            电磁阀时间控制，到达控制时间关闭电磁阀
** input parameters:        pu32Timer 软件定时器首地址
** output parameters:       none
** Returned value:          
** Created by:              linguofeng 
** Created Date:            2015-05-28
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
static void TimerCtrl(INT32U *pu32Timer)
{
    INT32U u32Loop = 0;
    INT32U u32Valve = 0;
    for (u32Loop = 0; u32Loop < JOG_CTRL_MAX_CMD; u32Loop++)
    {
        if (0 == pu32Timer[u32Loop])
        {
            continue;
        }

        if (SEC_TIMER > pu32Timer[u32Loop])
        {
            pu32Timer[u32Loop] = 0;
            VALVE_TBL(u32Valve,SHIELD_POS,u32Loop);
            CLR_VALVE(u32Valve);            
        }
    }
}

/*********************************************************************************************************
** Function name:           SensorCtrl
** Descriptions:            传感器条件控制，达到设定传感器值是关闭对应电磁阀动作
** input parameters:       
** output parameters:       none
** Returned value:          
** Created by:              linguofeng 
** Created Date:            2015-05-28
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/

static void SensorCtrl(void)
{
    INT32U u32Valve = 0;

    if (GetConveyorExtens() > GetASQEndStrk())
    {
        VALVE_TBL(u32Valve,SHIELD_POS,ADVANCE_CMD);
        CLR_VALVE(u32Valve);
    }
    // TODO: 备用数字传感器电源电流值超过多少时关闭电源
    //if (GetBackSigSnrCurrent() >)
    {
      //关闭电源
    }
    // TODO: 电源电流超过多少时关闭电源
    //if (GetPowerCurrent() >)
    {
        // 关闭电源
    }
    /* 升柱停止压力 */
    if (GetFormerPropPressure() > GetASQADVP2())
    {
        VALVE_TBL(u32Valve,SHIELD_POS,SET_LEG_CMD);
        CLR_VALVE(u32Valve);
    }
    /* 降柱停止压力 */
    if (GetFormerPropPressure() < GetASQADVP0())
    {
        VALVE_TBL(u32Valve,SHIELD_POS,LOWER_LEG_CMD);
        CLR_VALVE(u32Valve);
    }
    if (0 != HAS_REAR_LEG())
    {
        if (GetRearPropPressure() >= GetASQADVP2())
        {
            VALVE_TBL(u32Valve,SHIELD_POS,SET_REAR_LEG_CMD);
            CLR_VALVE(u32Valve);           
        }
        if (GetRearPropPressure() <= GetASQADVP0())
        {
            VALVE_TBL(u32Valve,SHIELD_POS,LOWE_REAR_LEG_CMD);
            CLR_VALVE(u32Valve);                      
        }
    }
    // TODO: 驱动器电流超过多少关闭电源
   // if (GetDrvPwrCurrent())
    {

    }
    // TODO: 最小系统外围模块电流超多少关闭电源
  //  if (GetPeripheralCurrent())
    {

    }
    //移架到达抬底目标时，停止抬底动作
//    if (GetASQLiftDist())
    {

    }
}
#endif
/*********************************************************************************************************
** Function name:           LocalPushCtrl
** Descriptions:            本架推溜控制接口，时间或传感器到达设定值后停止电磁阀动作
** input parameters:       
** output parameters:       none
** Returned value:          
** Created by:              linguofeng 
** Created Date:            2015-06-24
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
static void LocalPushCtrl(void)
{
    SCN_RFH_MSG_S stRfhMsg;
    CONTROL_PKT_S stPkt;
    INT32U u32Time = 0;
    INT32U u32Valve = 0;
    INT32U u32RealTime = 0;
    INT32U u32SetPushTime = GetBPLPushTime();
    
    u32Time = GetLPushCtrlTime();      
    if (0 == u32Time)
    {
        return;
    }
    u32RealTime = SEC_TIMER;
    if (((u32RealTime - u32Time) > u32SetPushTime)||
        ((INT32U)GetConveyorExtens() >= GetBPFinalStroke()))
    {
        SetLPushCtrlTime(0);
        Jog_Ctrl_StopWarning(stPkt);
        VALVE_TBL(u32Valve,SHIELD_POS,PUSH_CONVEYOR_CMD);
        CLR_VALVE(u32Valve);      

        POST_INFO2SCN(stRfhMsg,IDLE_SCREEN,NULL_INFO,NULL_INFO);
    }
}


/*********************************************************************************************************
** Function name:           PSA_Ctrl
** Descriptions:            两柱支架 自动补压控制
** input parameters:        
** output parameters:       none
** Returned value:          
** Created by:              linguofeng 
** Created Date:            2015-07-16
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/

PSA_RTNCODE_E  PSAInit(struct tag_PSA_PROCESS_S *pstProcess)
{
    INT32U u32Valve = 0;

    if ((GetFormerPropPressure() < GetPSAP1())&&(GetFormerPropPressure() > GetPSAP0()))
    {
        VALVE_TBL(u32Valve,SHIELD_POS,SET_LEG_CMD);
        SET_VALVE(u32Valve);        
        pstProcess->pfunc = PSAAct;
        pstProcess->u8IsPSA = TRUE;
        pstProcess->u8PSACnt = 0;
        pstProcess->u32STime = OSTimeGet();
    }
    return PSA_NULL;
}
PSA_RTNCODE_E  PSAAct(struct tag_PSA_PROCESS_S *pstProcess)
{
    INT32U u32Valve = 0;
    PSA_RTNCODE_E eRet = PSA_NULL;
    BOOLEAN *pbPsaEn = &GetPropPSAEnable();
    if ((OSTimeGet() - pstProcess->u32STime) > GetPSADurTime())
    {
        VALVE_TBL(u32Valve,SHIELD_POS,SET_LEG_CMD);
        CLR_VALVE(u32Valve);
        pstProcess->u8PSACnt++;
        pstProcess->u32ITime = OSTimeGet();
        pstProcess->pfunc = PSAIntv;
        pstProcess->u8IsPSA = FALSE;
        eRet = PSA_TIMEOUT;
    }
    if (GetFormerPropPressure() > GetPSAFntP2())
    {
        VALVE_TBL(u32Valve,SHIELD_POS,SET_LEG_CMD);
        CLR_VALVE(u32Valve);
        pstProcess->u8IsPSA = FALSE;
        pstProcess->pfunc  = PSAInit;
        eRet = PSA_COMPLETE;
    }
    if (pstProcess->u8PSACnt > GetPSACntMax())
    {
        *pbPsaEn = FALSE;
        pstProcess->u8IsPSA = FALSE;
        pstProcess->pfunc = PSAIntv;
        eRet = PSA_EXCEED;
    }
    return eRet;
}
PSA_RTNCODE_E PSAIntv(struct tag_PSA_PROCESS_S *pstProcess)
{
    PSA_RTNCODE_E eRet = PSA_NULL;
    INT32U u32Valve = 0;
    
    if ((OSTimeGet() - pstProcess->u32ITime) > GetPSAIntvTime())
    {
        VALVE_TBL(u32Valve,SHIELD_POS,SET_LEG_CMD);
        SET_VALVE(u32Valve);
        eRet = PSA_INTERVAL;
        pstProcess->pfunc = PSAAct;
        pstProcess->u8IsPSA = TRUE;
    }
    return eRet;
}



void PSA_Ctrl(struct tag_PSA_PROCESS_S *pstProcess)
{
    INT32U u32Valve = 0;

    if (NULL == pstProcess)
    {
        return;
    }
    
    /* 自动补压功能禁止 *//* 非空闲状态 *//* 压力传感器坏 *//* 自动补压压力范围之外 */
    if ((FALSE == GetPropPSAEnable())||
        (pCurrScreen != &g_astScreen[IDLE_SCREEN])||
        (GetFormerPropPressure() < GetPSAP0())||
        (GetFormerPropPressure() > GetPSAFntP2())/*||( 传感器坏)*/)        
    {
        PSAING_CHECK(pstProcess->u8IsPSA,u32Valve);
        return;
    }

    pstProcess->pfunc(pstProcess);
}




/*********************************************************************************************************
** Function name:           Task_20msCycle
** Descriptions:            20ms定时调度任务，10分频用于声光预警控制；电磁阀软件定时器控制；电磁阀开关控制
** input parameters:        
** output parameters:       none
** Returned value:          
** Created by:              linguofeng 
** Created Date:            2015-05-28
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
void Task_20msCycle(void *pdata)
{
    PSA_PROCESS_S stPSA = {FALSE,0,0,0,PSAInit};
    INT32U u32Schdl200 = 0;
	INT8U u8AlarmCmd = 0;


    while(1)
    {         
        Schedual200ms(&u32Schdl200,&u8AlarmCmd);
		CommLEDTwinkle();
  
       // TimerCtrl(g_su32CtrlTimer);
   #if 0 //传感器条件暂时不满足，先注释掉linguofeng 15/6/4   
        SensorCtrl();
   #endif
        LocalPushCtrl();
        PSA_Ctrl(&stPSA);
        SolenoidDriverCtrl(&GET_VALVE());
        
        KeyBrdIndicatorLEDUpdate();
        
        OSTimeDly(TIME_DLY_20MS);   
        //wdtFeed(WDT0);

        
    }
}
/*********************************************************************************************************
** Function name:           BroadcastEstopShdNum
** Descriptions:            广播急停支架编号到工作面
** input parameters:        u8ShdNum 本架支架编号 s32LastStat 本架闭锁键状态
** output parameters:       none
** Returned value:          
** Created by:              linguofeng 
** Created Date:            2015-04-22
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
static void BroadcastEstopShdNum(INT8U u8ShdNum, INT32S s32LastStat)
{
    CONTROL_PKT_S stCtrlPkt;

    stCtrlPkt.u8CmdType = E_STOP_CMD_TYPE;
    stCtrlPkt.bAwayOper = AWAY_OPERATOR;
    stCtrlPkt.u8NumOper = u8ShdNum;
    stCtrlPkt.u8Area = 0xff;
    stCtrlPkt.u8Offset = 0;
    stCtrlPkt.u8SArea = 0;
    

    /* 发送解急停命令到整个工作面 */
    stCtrlPkt.u32CmdCode = E_STOP_CMD + s32LastStat;
    stCtrlPkt.u8CommDir = CAN_LEFT;
    tmWrite(CAN_LEFT,0,RH_PORT_BANK,sizeof(CONTROL_PKT_S),(void *) &stCtrlPkt,NOT_NEED_ACK);
    stCtrlPkt.u8CommDir = CAN_RIGHT;
    tmWrite(CAN_RIGHT,0,RH_PORT_BANK,sizeof(CONTROL_PKT_S),(void *) &stCtrlPkt,NOT_NEED_ACK);  

	/*本架急停记录     */
	WriteRecord(&stCtrlPkt, RH_PORT_BANK);
}
/*********************************************************************************************************
** Function name:           PostLockShdNum
** Descriptions:              发送闭锁命令到左右邻架
** input parameters:        u8ShdNum 本架支架编号 s32LastStat 本架闭锁键状态
** output parameters:      pErrTypeLock  左右邻架自锁错误信息
** Returned value:          
** Created by:                gaocen 
** Created Date:             2015-04-24
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
static void PostLockShdNum(INT8U u8ShdNum, INT32S s32LastStat, LOCK_ERR_S *pErrTypeLock)
{
    CONTROL_PKT_S stCtrlPkt;
	
    stCtrlPkt.u8CmdType = LOCK_CMD_TYPE;
    stCtrlPkt.bAwayOper = AWAY_OPERATOR;
    stCtrlPkt.u8NumOper = u8ShdNum;
    stCtrlPkt.u8Area = 1;
    stCtrlPkt.u8Offset = 0;
    stCtrlPkt.u8SArea = 0;

    stCtrlPkt.u32CmdCode = L_LOCK_CMD + s32LastStat;
    stCtrlPkt.u8CommDir = CAN_LEFT;
    pErrTypeLock->U8LockLeftErr = tmWrite(CAN_LEFT,0, RH_PORT_BANK, sizeof(CONTROL_PKT_S), (void *) &stCtrlPkt, NOT_NEED_ACK);
    stCtrlPkt.u8CommDir = CAN_RIGHT;
    pErrTypeLock->U8LockRightErr = tmWrite(CAN_RIGHT,0, RH_PORT_BANK, sizeof(CONTROL_PKT_S), (void *) &stCtrlPkt, NOT_NEED_ACK);  

	/*本架闭锁记录    */
	WriteRecord(&stCtrlPkt, RH_PORT_BANK);
}

/*********************************************************************************************************
** Function name:           EStopListInit
** Descriptions:            被按下的急停键支架列表初始化
** input parameters:        
** output parameters:       none
** Returned value:          
** Created by:              linguofeng 
** Created Date:            2015-04-22
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/

void EStopListInit(void)
{
    INT8U u8Data = 0;/* 头结点 0号架 */
    g_pEStopList = NULL;
    g_pEStopList = ListCreat(u8Data);
    if (NULL == g_pEStopList)
    {
        ERR_MESSAGE("EStopListInit err");
        while(1);
    }
}
/*********************************************************************************************************
** Function name:           LockListInit
** Descriptions:             被按下的闭锁键支架列表初始化
** input parameters:        
** output parameters:       none
** Returned value:          
** Created by:               gaocen 
** Created Date:            2015-04-24
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
void LockListInit(void)
{
    INT8U u8Data = 0;/* 头结点 0号架 */
    
    g_pLockList = NULL;
    g_pLockList = ListCreat(u8Data);
    if (NULL == g_pLockList)
    {
        ERR_MESSAGE("LockListInit err");
        while(1);
    }
}

/*********************************************************************************************************
** Function name:           EStopNodeAddSelf
** Descriptions:            添加删除本架急停按键到急停列表中
** input parameters:        
** output parameters:       none
** Returned value:          
** Created by:              linguofeng 
** Created Date:            2015-04-22
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
void EStopNodeAddDelSelf(void)
{
    LIST_NODE *pNode = NULL;
    static INT32S s32LastStat = NONE_ESTOP;
    INT8U u8ShdNum = GetCurrShieldNo();
    /* 状态为改变 */
    if ( s32LastStat == gpioGet(E_STOP))
    {
        return ;
    }
    s32LastStat = gpioGet(E_STOP);

    if (ESTOP_ACCURED == s32LastStat)
    {
        pNode = ListInsertEnd(g_pEStopList,u8ShdNum);
        if (NULL == pNode)
        {
            ERR_MESSAGE("EStopNodeAdd err");
            return;
        }
    }
    else
    {
        ListRemoveNodebyData(&g_pEStopList,u8ShdNum);
    }
    

    REQUEST_TASK_DEL(TASK_CTRLPKT_SEND_ID);
    /* 广播本架急停状态到工作面 */
    BroadcastEstopShdNum(u8ShdNum,s32LastStat);
}
/*********************************************************************************************************
** Function name:           LockNodeAddSelf
** Descriptions:            添加删除本架闭锁按键到闭锁列表中
** input parameters:        
** output parameters:       pErrTypeLock 左右邻架自锁错误信息
** Returned value:          
** Created by:              gaocen 
** Created Date:            2015-04-24
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
void LockNodeAddDelSelf(LOCK_ERR_S *pErrTypeLock)
{
    LIST_NODE *pNode = NULL;
    static INT32S s32LastStat = NONE_LOCK;
    INT8U u8ShdNum = GetCurrShieldNo();
	
    /* 急停发生不处理 */
    if (ESTOP_ACCURED == gpioGet(E_STOP))
    {
        return ;
    }
	
	/*闭锁状态未改变不处理 */
	if(s32LastStat == gpioGet(SHIELD_LOCK))
	{
		return ;
	}
	
    s32LastStat = gpioGet(SHIELD_LOCK);

    if (LOCK_ACCURED == s32LastStat)
    {
    	pNode = ListInsertEnd(g_pLockList,u8ShdNum);
        if (NULL == pNode)
        {
            ERR_MESSAGE("LockNodeAdd err");
            return;
        }
    }
    else
    {
        ListRemoveNodebyData(&g_pLockList,u8ShdNum);
    }
    
  
    REQUEST_TASK_DEL(TASK_CTRLPKT_SEND_ID);
    /* 发布闭锁信号到左右邻架 */
    PostLockShdNum(u8ShdNum, s32LastStat, pErrTypeLock);
}

/*********************************************************************************************************
** Function name:           EStopNodeAddOther
** Descriptions:            添加删除别架急停按键到急停列表中
** input parameters:        u8ShdNum 急停架号 u32CmdCode 急停or解急停
** output parameters:       none
** Returned value:          
** Created by:              linguofeng 
** Created Date:            2015-04-22
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
void EStopNodeAddDelOther(INT8U u8ShdNum,INT32U u32CmdCode)
{
    LIST_NODE *pNode = NULL;

    if (E_STOP_CMD == u32CmdCode)
    {
        pNode = ListInsertEnd(g_pEStopList,u8ShdNum);
        if (NULL == pNode)
        {
            ERR_MESSAGE("EStopNodeAdd err");
            return;
        }   
    }
    else
    {
        ListRemoveNodebyData(&g_pEStopList,u8ShdNum);
    }
}
/*********************************************************************************************************
** Function name:           LockNodeAddOther
** Descriptions:            添加删除别架闭锁按键到闭锁列表中
** input parameters:        u8ShdNum 闭锁架号 u32CmdCode 闭锁or 解闭锁
** output parameters:       none
** Returned value:          
** Created by:              gaocen 
** Created Date:            2015-04-24
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
void LockNodeAddDelOther(INT8U u8ShdNum,INT32U u32CmdCode)
{
    LIST_NODE *pNode = NULL;

    if (L_LOCK_CMD == u32CmdCode)
    {
        pNode = ListInsertEnd(g_pLockList,u8ShdNum);
        if (NULL == pNode)
        {
            ERR_MESSAGE("LockNodeAdd err");
            return;
        }   
    }
    else
    {
        ListRemoveNodebyData(&g_pLockList,u8ShdNum);
    }
}


/*********************************************************************************************************
** Function name:           GetSafeOperListLen()
** Descriptions:            获取安全操作链表长度
** input parameters:        
** output parameters:       none
** Returned value:          
** Created by:              linguofeng 
** Created Date:            2015-11-28
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
INT16U GetSafeOperListLen(LIST_NODE * plist)
{
    INT16U u16ListLen = 0;
    LIST_NODE *pNode = NULL;
    if (NULL == plist)
    {
        return u16ListLen;
    }
    
    pNode = plist->pNext;
    while(NULL != pNode)
    {
        pNode = pNode->pNext;
        u16ListLen++;
    }
    
    return u16ListLen;
}

/*********************************************************************************************************
** Function name:           GetFaceSafeNode()
** Descriptions:            启动时获取工作面安全操作节点号
** input parameters:        
** output parameters:       none
** Returned value:          
** Created by:              linguofeng 
** Created Date:            2015-11-28
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
static void GetFaceSafeNode(INT32U u32Chnnl,INT32U u32Addr,LIST_NODE *pList,INT16U u16Len)
{
    INT8U *pu8Data = NULL;
    INT16U u16Loop = 0;
    INT16U u16ReadLen = 0;
    
    if (u16Len == 0)
    {
        return;
    }
    
    pu8Data = sysHeapMalloc(u16Len);
    u16ReadLen = tmRead(u32Chnnl,0,(INT8U)u32Addr,u16Len,(void * )pu8Data);
    for (u16Loop=0;u16Loop<u16ReadLen;u16Loop++)
    { 
        ListInsertEnd(pList,*pu8Data);
        pu8Data++;
    }    
    sysHeapFree(pu8Data);
}
/*********************************************************************************************************
** Function name:           GetFaceSafeStat()
** Descriptions:            启动时获取工作面安全操作状态
** input parameters:        
** output parameters:       none
** Returned value:          
** Created by:              linguofeng 
** Created Date:            2015-11-28
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
void GetFaceSafeStat(void)
{
    INT32S s32Ret = 0;
    SAFE_OPER_NUM_S stSafe;
    INT32U u32Chnnl = 0;
    
    memset(&stSafe,0,sizeof(stSafe));
    
    s32Ret = tmRead(CAN_LEFT,0,(INT8U)RH_PORT_GET_SAFE_NUM,sizeof(SAFE_OPER_NUM_S),(void *)&stSafe);
    u32Chnnl = CAN_LEFT;
    if (s32Ret < 0)
    {
        s32Ret = tmRead(CAN_RIGHT,0,(INT8U)RH_PORT_GET_SAFE_NUM,sizeof(SAFE_OPER_NUM_S),(void *)&stSafe);
        u32Chnnl = CAN_RIGHT;
        if (s32Ret < 0)
        {
            return;
        }
    }
    
    GetFaceSafeNode(u32Chnnl,RH_PORT_GET_ESTOP_LIST,g_pEStopList,stSafe.u16EstopLen);
    GetFaceSafeNode(u32Chnnl,RH_PORT_GET_LOCK_LIST,g_pLockList,stSafe.u16LockLen);

}

#if 0
 /*********************************************************************************************************
 ** Function name:           DelCtrlTask
 ** Descriptions:           收到停止命令，请求删除正在执行的成组动作,ASQ动作任务
 ** input parameters:        u32Msg 成组或asq消息 u32TaskId 任务ID
 **                         
 **                          
 ** output parameters:       none
 ** Returned value:          
 ** Created by:              
 ** Created Date:            2015-4-12
 **--------------------------------------------------------------------------------------------------------
 ** Modified by:
 ** Modified date:
 **--------------------------------------------------------------------------------------------------------
 *********************************************************************************************************/  
void DelCtrlTask(INT32U u32Msg,INT32U u32TaskId)
{
    OS_TCB stTcb;
    INT8U u8Err = 0;
    ASQ_BANK_CTRL_INFO_S stDispInfo;
    
    strcpy((char *)stDispInfo.au8FstL,NULL_INFO);    
    u8Err = OSTaskQuery(u32TaskId,&stTcb);
    if (OS_NO_ERR == u8Err)
    {
        if (0 != u32Msg)
        {
            sysMsgPost(u32Msg,(INT8U *) &stDispInfo,0);
        }
        while(OSTaskDelReq(u32TaskId) != OS_TASK_NOT_EXIST)
        {
            OSTimeDly(1);
        }
    }
}
#endif 
/*********************************************************************************************************
** Function name:           SafeOperRstStat
** Descriptions:            执行安全操作时复位初始状态
** input parameters:        
**                         
**                          
** output parameters:       none
** Returned value:          
** Created by:              linguofeng
** Created Date:            2015-8-19
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/  
void SafeOperRstStat(void)
{
    CONTROL_PKT_S stPkt;
    OS_TCB stTcb;
	
    VOLTAGE_CTRL_OFF(V12V_CTRL);
    Jog_Ctrl_StopWarning(stPkt);
    RST_VALVE();
    SetLPushCtrlTime(0);

    if (OS_NO_ERR == OSTaskQuery(TASK_BANKCTRL_ID,&stTcb))
    {	
    	if (stTcb.OSTCBStat == OS_STAT_RDY)
    	{
        	REQUEST_TASK_DEL(TASK_BANKCTRL_ID);
    	}
    	else
    	{
        	OSTaskDel(TASK_BANKCTRL_ID);
    	}
    }
    REQUEST_TASK_DEL(TASK_ASQ_ID);
    REQUEST_TASK_DEL(TASK_CTRLPKT_SEND_ID);
    FreeBankCtrlPktMem();
}
/*********************************************************************************************************
** Function name:           DisposeEStopStat
** Descriptions:            急停动作处理
** input parameters:        
** output parameters:       none
** Returned value:          true 安全操作界面 false 
** Created by:              linguofeng 
** Created Date:            2015-04-22
**-------------------------------------------------------------------------------------------------------
** Descriptions:             补充了与闭锁状态的联动控制
** Modified by:		   gaocen
** Modified date:           2015-04-24
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
void DisposeEStopStat(void)
{
    static LIST_NODE *pNode = NULL;
    LIST_NODE *pEstoplist = g_pEStopList->pNext;
    INT8U u8ShdNum =  GetCurrShieldNo();
    SCREEN_DATA_S *pstData = g_astScreen[SAFE_SCREEN].pstData;
    CONTROL_PKT_S stPkt;
	
    if (pNode == pEstoplist)
    {
        return ;
    }

    pNode = pEstoplist;
        
    if (NULL == pEstoplist)
    {
        return;
    }
   
    SafeOperRstStat();
	CLEAR_COMM_CNT();
	Jog_Ctrl_Warning(stPkt);  
    SetScnItem2Null(pstData,NULL_INFO,0);
    /* 显示急停架号 */
    if (u8ShdNum == pEstoplist->u8ShdNum)
    {
        sprintf((char*)pstData->stScnItem[1].pcDispData,"%s",(char *)ESTOP_MSG);
    }
    else
    {
        sprintf((char*)pstData->stScnItem[1].pcDispData,"  %4d%s",pEstoplist->u8ShdNum,(char *)"号架急停  ");
    }

    if (pCurrScreen != &g_astScreen[SAFE_SCREEN])
    {
        pCurrScreen = &g_astScreen[SAFE_SCREEN];
        PushScreen(&pCurrScreen);        
    }
    SAFE_OPER_BUZZ();

    
}
/*********************************************************************************************************
** Function name:           DisposeLockStat
** Descriptions:              闭锁动作处理
** input parameters:        
** output parameters:       none
** Returned value:          
** Created by:               gaocen 
** Created Date:            2015-04-24
**-------------------------------------------------------------------------------------------------------
** Modified by:           linguofeng
** Modified date:         2015-08-21
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
void DisposeLockStat(LOCK_ERR_S *pErrTypeLock)
{
    static LIST_NODE *pNode_Lock = NULL;
    LIST_NODE *pLockNode = g_pLockList->pNext;
    SCREEN_DATA_S *pstData = g_astScreen[SAFE_SCREEN].pstData;
    INT8U u8ShdNum =  GetCurrShieldNo();
    CONTROL_PKT_S stPkt;
	
    /* 没有急停信号时才处理闭锁信号*/
    if (NULL != g_pEStopList->pNext)
    {
        return;
    }
    /*急停闭锁状态无变化 */	
    if (pNode_Lock == pLockNode) 
    {
        return;
    }

    pNode_Lock = pLockNode;

    SafeOperRstStat(); 
	CLEAR_COMM_CNT();
	Jog_Ctrl_Warning(stPkt); 
    SetScnItem2Null(pstData,NULL_INFO,0);

    /* 显示闭锁架号 */
    if (u8ShdNum != pLockNode->u8ShdNum)
    {
        sprintf((char *)pstData->stScnItem[1].pcDispData, "%s", (char *)CAN_LOCK_MSG); 
    }
    else
    {
        sprintf((char *)pstData->stScnItem[0].pcDispData, "%s", (char *)LOCK_MSG);
        	
		if(pErrTypeLock->U8LockLeftErr < 0)
		{	
			sprintf((char *)pstData->stScnItem[2].pcDispData, "%s", (char *)LEFTLOCK_ERR_MSG);
		}
		if(pErrTypeLock->U8LockRightErr < 0)
		{
			sprintf((char *)pstData->stScnItem[1].pcDispData, "%s", (char *)RIGHTLOCK_ERR_MSG);
		}
    }
    memset(pErrTypeLock,0,sizeof(LOCK_ERR_S));
    if (pCurrScreen != &g_astScreen[SAFE_SCREEN])
    {
        pCurrScreen = &g_astScreen[SAFE_SCREEN];
        PushScreen(&pCurrScreen);        
    }
    SAFE_OPER_BUZZ();

}
/*********************************************************************************************************
** Function name:           GetEStopStat
** Descriptions:            获取急停闭锁状态
** input parameters:        
** output parameters:       none
** Returned value:          
** Created by:              linguofeng 
** Created Date:            2015-04-22
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
INT8U GetEStopStat(void)
{
    INT8U u8Ret = NONE_ESTOP;
    
    if ((NULL != g_pEStopList->pNext)||(NULL != g_pLockList->pNext))
    {
        u8Ret = ESTOP_ACCURED;
    }

    return u8Ret;
}


/*********************************************************************************************************
** Function name:           SetEStopCmdType
** Descriptions:            设置急停闭锁状态命令码
** input parameters:        pu8CmdType 命令码指针
** output parameters:       EMERGENCY_STOP_E；
** Returned value:          none                          
** Created by:              
** Created date:            
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
*********************************************************************************************************/
INT32U SetEStopCmdType(INT8U *pu8CmdType)
{
    INT32U u32Ret = NONE_EMERGENCY;
    if (ESTOP_ACCURED == gpioGet(E_STOP))
    {
        u32Ret |= EMERGENCY_STOP;
    }
    if (ESTOP_ACCURED == gpioGet(SHIELD_LOCK))
    {
        u32Ret |= SHD_LOCK;
    }
    
    switch(u32Ret)
    {
        case EMERGENCY_STOP:
        case E_STOP_SHD_LOCK:   
            {
                *pu8CmdType = E_STOP_CMD_TYPE;
                break;
            }
        case SHD_LOCK:
            {
                *pu8CmdType = LOCK_CMD_TYPE;
                break;
            }            
        default:
            break;
    }    
    return u32Ret;
}

/*********************************************************************************************************
** Function name:           CheckLineStatus
** Descriptions:            检测链路状态
** input parameters:        
** output parameters:       none
** Returned value:          0 链路ok -1 链路异常
** Created by:              linguofeng 
** Created Date:            2015
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
INT32S CheckLineStatus(INT8U u8Comdir,INT8U u8CurrOffset, INT8U *pu8LastOffset)
{
    INT32S s32Ret = 0;
    INT16U u16Len = sizeof(INT8U);
    if (u8CurrOffset != *pu8LastOffset)
    {
        s32Ret = tmWrite(u8Comdir,0,RH_PORT_LINE_CHK,u16Len,(void*)&u8CurrOffset,NEED_ACK);        
        if (s32Ret != (INT32S)u16Len)
        {
           s32Ret = -1; 
        }  
        *pu8LastOffset = u8CurrOffset;
    }
    
    return s32Ret;
}



/*********************************************************************************************************
** Function name:           Task_CtrlPktSend
** Descriptions:            单控操作报文发送任务
** input parameters:       
** output parameters:       none
** Returned value:         
** Created by:              linguofeng 
** Created Date:            2015
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
void Task_CtrlPktSend(void *pdata)
{
    INT32S s32Ret = 0;
    INT8U u8Time = 0;
    CTRLPKT_SEND_S stSendPkt;
    CONTROL_PKT_S stCtrlPkt;
    INT8U u8LastOffset = 0xff;
	INT32U LastCmdCode = 0;	//gaocen 15/06/16  add   

    memset(&stSendPkt,0,sizeof(stSendPkt));
    memset(&stCtrlPkt,0,sizeof(stCtrlPkt));
    while(1)
    {
        if (SYS_OK == sysMsgAccept(gu32JogCtrlMsg,(INT8U *) &stSendPkt))
        {
            
            stCtrlPkt = *(CONTROL_PKT_S *)stSendPkt.pData;
            sysHeapFree(stSendPkt.pData);
            u8Time = stSendPkt.u8SendCnt;
        }
         
        if (CheckLineStatus(stCtrlPkt.u8CommDir,stCtrlPkt.u8Offset,&u8LastOffset) < 0)
        {
            /* 液晶屏提示线路断故障 */
            SCN_RFH_MSG_S stRfhMsg;
            INT8U u8Loop =0;
            stRfhMsg.eNextScn = INFO_SCREEN;
            
            for (u8Loop=0;u8Loop<THREE_LINE_SCN;u8Loop++)
            {
                sprintf((char*)stRfhMsg.au8Msg[u8Loop],NULL_INFO);
            }
            sysMsgFlush(gu32ScnRshMsg);
            sprintf((char*)stRfhMsg.au8Msg[1],(char*)CAN_DISCONNECT_MSG);
            s32Ret = sysMsgPost(gu32ScnRshMsg,(INT8U *) &stRfhMsg,0);
            if (OS_NO_ERR == s32Ret)
            {
                OSTaskDel(OS_PRIO_SELF);
            }            
        }
        if (0 != u8Time)
        {
            u8Time--;          
            s32Ret = tmWrite(stSendPkt.u8Dir,0,stSendPkt.eAddr,stSendPkt.u8Len,
                            (void*)&stCtrlPkt,NOT_NEED_ACK);            

			/* 本架单控动作记录      gaocen 15/06/16  add  */
			if (WARNING_CMD_TYPE == stCtrlPkt.u8CmdType)
			{
				LastCmdCode = NONE_CMD;
			}
			else if(stCtrlPkt.u32CmdCode != LastCmdCode)
			{
				WriteRecord(&stCtrlPkt, RH_PORT_JOG);
				LastCmdCode = stCtrlPkt.u32CmdCode;
			}

        }
        else
        {	
            OSTaskDel(OS_PRIO_SELF);
        }
        
        RESPOND_TASK_DEL_REQ();      
        OSTimeLag(TIME_DLY_80MS);
		ADD_COMM_ONCE();
    }
}
/*********************************************************************************************************
** Function name:           IsEndActShield
** Descriptions:            动作末架处理,回复控制架应答报文
** input parameters:        stRefreshPkt 发送数据
** output parameters:       none
** Returned value:          
** Created by:              linguofeng 
** Created Date:            2015-04-12
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
static void IsEndActShield(PKT_REFRESH_SCN_S *pstRfhPkt)
{
    // TODO: 待重构20150727
    if (AWAY_OPERATOR == pstRfhPkt->stPkt.bAwayOper)
    {
        if (pstRfhPkt->stPkt.u8Area > 0) 
        {
            //pstRfhPkt->stPkt.u8Area--;
        }
        else/* 动作末架*/
        {
            if (RH_PORT_BANK == pstRfhPkt->u32PortAddr)
            {
                //pstRfhPkt->stPkt.u8Offset = *g_pasu8Offset[pstRfhPkt->stPkt.u32CmdCode - BATCH_ASQ_CMD];
                //pstRfhPkt->stPkt.u8Area = *g_pasu8Area[pstRfhPkt->stPkt.u32CmdCode - BATCH_ASQ_CMD]; 
                //pstRfhPkt->stPkt.u8Area = pstRfhPkt->stPkt.u8SArea;
				pstRfhPkt->stPkt.u8Area = pstRfhPkt->stPkt.u8SArea - 1;
                pstRfhPkt->stPkt.u8Offset = pstRfhPkt->stPkt.u8NumOper;
                pstRfhPkt->u32PortAddr = RH_PORT_REP_BANK;
                NBRCAN_COMM_REP(pstRfhPkt->stPkt.u8CommDir);
            }
        }
    }

}
/*********************************************************************************************************
** Function name:           BankAutoAdvance
** Descriptions:            自动移架处理代码
** input parameters:        stRefreshPkt 发送数据
** output parameters:       none
** Returned value:          
** Created by:              linguofeng 
** Created Date:            2015-04-12
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
void BankAutoAdvance(PKT_REFRESH_SCN_S stRfhPkt)
{
	SingleASQCtrl();
	RST_VALVE();
	
    if (stRfhPkt.stPkt.u8Area > 0) 
    {
        tmWrite(stRfhPkt.stPkt.u8CommDir,0,stRfhPkt.u32PortAddr,sizeof(CONTROL_PKT_S),(void *) &stRfhPkt.stPkt,NOT_NEED_ACK);
    }
    
}
/*********************************************************************************************************
** Function name:           ConvCondInit
** Descriptions:            成组推溜、成组拉溜、成组拉后溜条件初始化
** input parameters:        pstCond 推溜条件 stPkt推溜报文
** output parameters:       none
** Returned value:          
** Created by:              linguofeng 
** Created Date:            2015-08-04
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
void ConvCondInit(struct tag_CONV_COND_SET_S *pstCond,CONTROL_PKT_S stPkt)
{
	INT32U u32GrpDly = 0;
	INT32U u32ConvTime = 0;
	
	if(NULL == pstCond){
		return;
	}
    if((stPkt.u32CmdCode != BANK_PUSH_CMD) && (stPkt.u32CmdCode != BANK_PULL_CMD) && 
		(stPkt.u32CmdCode != BANK_PULLBACK_CMD))
	{
		return;
	}

	//switch(pstCond->stPkt.u32CmdCode)
	switch(stPkt.u32CmdCode)
	{
		case BANK_PUSH_CMD:
			{
				u32GrpDly = GetBPGrpDelay();
				u32ConvTime = GetBPTime();	
				if (u32ConvTime < BP_ACT_TIME_DFT)
				{
					u32ConvTime = BP_ACT_TIME_DFT;
				}
				//if (u32GrpDly < BP_ACT_GRPDLY_DFT)
				//{
					//u32GrpDly = BP_ACT_GRPDLY_DFT;
				//}
				pstCond->u32Position = GetBPFinalStroke();				
				pstCond->u32GrpDly = SECOND2MILLI(u32GrpDly);
				pstCond->u32ConvTime = SECOND2MILLI(u32ConvTime);
				pstCond->f32Pressure = GetBPPressure();
				pstCond->u32StartTime = MS_TIMER;
				pstCond->stPkt = stPkt;
				pstCond->stPkt.u32CmdCode = PUSH_CONVEYOR_CMD;
				pstCond->pfSet = ConvCondSet;
				pstCond->stExec.pfunc = ConvPrsrNotReach; 				
				break;
			}
		case BANK_PULL_CMD:
			{
				u32GrpDly = GetCPGrpDelay();
				u32ConvTime = GetCPTime();
				if (u32ConvTime  < BP_ACT_TIME_DFT)   /*暂时先用推溜默认参数*/
				{
					u32ConvTime = BP_ACT_TIME_DFT;
				}
				if (u32GrpDly < BP_ACT_GRPDLY_DFT)
				{
					u32GrpDly = BP_ACT_GRPDLY_DFT;
				}				
				pstCond->u32Position = GetCPFinalStroke();
				pstCond->u32GrpDly = SECOND2MILLI(u32GrpDly);
				pstCond->u32ConvTime = SECOND2MILLI(u32ConvTime);
				pstCond->f32Pressure = GetBPPressure();		/*  拉溜菜单页无允许压力*/
				pstCond->u32StartPos = (INT32U)GetConveyorExtens();
				pstCond->u32StartTime = MS_TIMER;
				pstCond->stPkt = stPkt;
				pstCond->stPkt.u32CmdCode = ADVANCE_CMD;
				pstCond->pfSet = ConvCondSet;
				pstCond->stExec.pfunc = ConvPrsrNotReach; 

				break;				
			}
		case BANK_PULLBACK_CMD:
			{
				u32GrpDly = GetRCPGrpDelay();
				u32ConvTime = GetRCPTime();				

				if (u32ConvTime  < BP_ACT_TIME_DFT)   /*暂时先用推溜默认参数*/
				{
					u32ConvTime = BP_ACT_TIME_DFT;
				}
				if (u32GrpDly < BP_ACT_GRPDLY_DFT)
				{
					u32GrpDly = BP_ACT_GRPDLY_DFT;
				}
				pstCond->u32Position = GetCPFinalStroke();	/*拉后溜菜单页无目标行程*/
				pstCond->u32GrpDly = SECOND2MILLI(u32GrpDly);
				pstCond->u32ConvTime = SECOND2MILLI(u32ConvTime);
				pstCond->f32Pressure = GetBPPressure();		/*拉后溜菜单页无允许压力*/
				pstCond->u32StartPos = 1000;	// TODO:后溜行程传感器在哪里
				pstCond->u32StartTime = MS_TIMER;
				pstCond->stPkt = stPkt;
				//pstCond->stPkt.u32CmdCode = CONVEYOR_PULLREAR_CMD;
				pstCond->stPkt.u32CmdCode = CONVEYOR_PULLREAR_CMD; 
				pstCond->pfSet = ConvCondSet;
				pstCond->stExec.pfunc = ConvPrsrNotReach; 

				
				break;
			}
		default:
			break;
	}

	return;

}
/*********************************************************************************************************
** Function name:           ConvCondSet
** Descriptions:            成组推溜处理接口设置
** input parameters:        pstCond 推溜条件 pfunc 推溜处理接口
** output parameters:       none
** Returned value:          
** Created by:              linguofeng 
** Created Date:             2015-08-04
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
void ConvCondSet(struct tag_CONV_COND_SET_S *pstCond,PF_BP_COND pfunc)
{
    pstCond->stExec.pfunc = pfunc;
}

/*********************************************************************************************************
** Function name:           CheckPositionSensor
** Descriptions:            推溜动作位移传感器异常条件判断
** input parameters:        stCond 
** output parameters:       none
** Returned value:          true 异常 false 正常
** Created by:              linguofeng 
** Created Date:             2016-06-27
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
static BOOLEAN CheckPositionSensor(CONV_COND_SET_S **ppstCond)
{
    INT32U u32Valve = 0;
    SCN_RFH_MSG_S stRfhMsg;
    CONV_COND_SET_S *pstCond = *ppstCond;
    char *pDispStr = NULL;
    BOOLEAN bRet = FALSE;
    
    /* 参数检查，上层保证 */
    if (SENSOR_NOVALUE == GetConveyorExtens())
    {
        pDispStr = INVALID_D_INFO;
        bRet = TRUE;
    }
    else if (SENSOR_OVERRUN == GetConveyorExtens())
    {
        pDispStr = BPCP_UPPER_D_INFO;  
        bRet = TRUE;
    }
    else
    {
        return bRet;
    }

    VALVE_TBL(u32Valve,SHIELD_POS,pstCond->stPkt.u32CmdCode);
    CLR_VALVE(u32Valve);           
    POST_INFO2SCN(stRfhMsg,BANK_CTRL_SCREEN,BANK_CONV_PUSH_MSG,pDispStr);
    pstCond->pfSet(pstCond,ConvNull);  
    return bRet;

}
/*********************************************************************************************************
** Function name:           ConvPosReached
** Descriptions:            成组推溜位移条件处理
** input parameters:        pstCond 推溜条件
** output parameters:       none
** Returned value:          
** Created by:              linguofeng 
** Created Date:            2015-08-04
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
void ConvPosReached(void *pCond)
{
    SCN_RFH_MSG_S stRfhMsg;
    INT32U u32Valve = 0;
	//INT32S s32DistConv = 0;
	struct tag_CONV_COND_SET_S *pstCond = (struct tag_CONV_COND_SET_S *)pCond;
	
	if(NULL == pCond){
		return;
	}	
    if((pstCond->stPkt.u32CmdCode != PUSH_CONVEYOR_CMD) && (pstCond->stPkt.u32CmdCode != ADVANCE_CMD) && 
		(pstCond->stPkt.u32CmdCode != CONVEYOR_PULLREAR_CMD))
	{
		return;
	}  
	switch(pstCond->stPkt.u32CmdCode)
	{
		case PUSH_CONVEYOR_CMD:
			{
                if (SENSOR_OFF != GetConveyorExtens())
                {
                    if (!CheckPositionSensor(&pstCond))
                    {
                        if (GetConveyorExtens() >= pstCond->u32Position)
                        {
                            VALVE_TBL(u32Valve,SHIELD_POS,pstCond->stPkt.u32CmdCode);
                            CLR_VALVE(u32Valve);           
                            POST_INFO2SCN(stRfhMsg,BANK_CTRL_SCREEN,BANK_CONV_PUSH_MSG,BP_POS_REACH_INFO);
                            pstCond->pfSet(pstCond,ConvNull);  
                        }
                    }
                }
    			else
    			{
       				pstCond->pfSet(pstCond,ConvTimeOut);
        			pstCond->stExec.pfunc(pstCond);     
    			} 
				break;
			}
		case ADVANCE_CMD:  /*在这里为移架命令*/
			{
                if (SENSOR_OFF != GetConveyorExtens())
                {
                    if (!CheckPositionSensor(&pstCond))
                    {
                        if(GetConveyorExtens() <= pstCond->u32Position)
                        {
                            VALVE_TBL(u32Valve,SHIELD_POS,pstCond->stPkt.u32CmdCode);
                            CLR_VALVE(u32Valve);           
                            POST_INFO2SCN(stRfhMsg,BANK_CTRL_SCREEN,BANK_CONV_PULL_MSG,CP_POS_REACH_INFO);
                            pstCond->pfSet(pstCond,ConvNull);

                        }
                    }
                }
    			else
    			{
       				pstCond->pfSet(pstCond,ConvTimeOut);
        			pstCond->stExec.pfunc(pstCond);    
    			} 				
				break;
			}
		case CONVEYOR_PULLREAR_CMD:
			{
				// TODO:拉后溜动作行程暂不作判断
				if(CONVEYOR_PULLREAR_CMD == pstCond->stPkt.u32CmdCode)
				{
       				pstCond->pfSet(pstCond,ConvTimeOut);
        			pstCond->stExec.pfunc(pstCond);
					return;
				}				
				break;
			}
		default:
			{
				RST_VALVE();
				break;
			}			
	}
	#if 0
	// TODO:拉后溜动作行程暂不作判断
	if(CONVEYOR_PULLREAR_CMD == pstCond->stPkt.u32CmdCode)
	{
        pstCond->pfSet(pstCond,ConvTimeOut);
        pstCond->stExec.pfunc(pstCond);
        //SSCOM_Output(" convert to timeout",sizeof(" convert to timeout"));
		return;
	}
	s32DistConv = abs((INT32S)GetConveyorExtens()-(INT32S)pstCond->u32StartPos);
    if (pstCond->u32Position <= s32DistConv)
    {
        VALVE_TBL(u32Valve,SHIELD_POS,pstCond->stPkt.u32CmdCode);
        CLR_VALVE(u32Valve);           
		POST_INFO2SCN(stRfhMsg,BANK_CTRL_SCREEN,BANK_CONV_PUSH_MSG,BP_POS_REACH_INFO);
        pstCond->pfSet(pstCond,ConvNull);
        //SSCOM_Output(" position reached",sizeof(" position reached"));    
    }
    else
    {
        pstCond->pfSet(pstCond,ConvTimeOut);
        pstCond->stExec.pfunc(pstCond);
        //SSCOM_Output(" convert to timeout",sizeof(" convert to timeout"));       
    }  
	#endif
}
static BOOLEAN CheckPressureSensor(CONV_COND_SET_S stCond,char **ppDispStr)
{
    BOOLEAN bRet = TRUE;
    
    if (SENSOR_NOVALUE == GetFormerPropPressure())
    {
        *ppDispStr = INVALID_P_INFO; 
    }
    else if (SENSOR_OVERRUN == GetFormerPropPressure())
    {
        *ppDispStr = BPCP_UPPER_P_INFO;
    }
    else if (stCond.f32Pressure > GetFormerPropPressure())
    {
        *ppDispStr = BPCP_UNDER_P_INFO;
    }
    else
    {
        bRet = FALSE;
        return bRet;
    }    
    return bRet;
}
/*********************************************************************************************************
** Function name:           ConvPrsrNotReach
** Descriptions:            成组推溜压力条件处理
** input parameters:        pstCond 推溜条件
** output parameters:       none
** Returned value:          
** Created by:              linguofeng 
** Created Date:             2015-08-04
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
void ConvPrsrNotReach(void *pCond)
{
	SCN_RFH_MSG_S stRfhMsg;
    INT32U u32Valve = 0;
    char *pDispStr = NULL;
	struct tag_CONV_COND_SET_S *pstCond = (struct tag_CONV_COND_SET_S *)pCond;
	
	if(NULL == pCond){
		return;
	}
    if((pstCond->stPkt.u32CmdCode != PUSH_CONVEYOR_CMD) && (pstCond->stPkt.u32CmdCode != ADVANCE_CMD) && 
		(pstCond->stPkt.u32CmdCode != CONVEYOR_PULLREAR_CMD))
	{
		return;
	}
    
    if (SENSOR_OFF != GetFormerPropPressure())
    {
        if (CheckPressureSensor(*pstCond,&pDispStr))
        {
            VALVE_TBL(u32Valve,SHIELD_POS,pstCond->stPkt.u32CmdCode);
            CLR_VALVE(u32Valve);          
    		POST_INFO2SCN(stRfhMsg,BANK_CTRL_SCREEN,BANK_CONV_PUSH_MSG,pDispStr);
            pstCond->pfSet(pstCond,ConvNull);     
        }
    }
    else
    {            
        pstCond->pfSet(pstCond,ConvPosReached);
        pstCond->stExec.pfunc(pstCond);       
    }    
}
/*********************************************************************************************************
** Function name:           BankAutoPush
** Descriptions:            成组推溜时间条件处理
** input parameters:        pstCond 推溜条件
** output parameters:       none
** Returned value:          
** Created by:              linguofeng 
** Created Date:             2015-08-04
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
//void ConvTimeOut(struct tag_CONV_COND_SET_S *pstCond)
void ConvTimeOut(void *pCond)
{
    INT32U u32Valve = 0;
	INT8U u8ErrMsgType;
	struct tag_CONV_COND_SET_S *pstCond = (struct tag_CONV_COND_SET_S *)pCond;

	if(NULL == pCond){
		return;
	}	
    if((pstCond->stPkt.u32CmdCode != PUSH_CONVEYOR_CMD) && (pstCond->stPkt.u32CmdCode != ADVANCE_CMD) && 
		(pstCond->stPkt.u32CmdCode != CONVEYOR_PULLREAR_CMD))
	{
		return;
	}  
	
	if(mSecTimeCheck(pstCond->u32StartTime,pstCond->u32ConvTime))
    {
       // Jog_Ctrl_StopExecute(stPkt);
        VALVE_TBL(u32Valve,SHIELD_POS,pstCond->stPkt.u32CmdCode);
        CLR_VALVE(u32Valve); 
		DIST_ERR_MSG(u8ErrMsgType,pstCond->stPkt.u32CmdCode);
        SetErrMsg(u8ErrMsgType,TRUE,NO_ERRMSG_PARA);
        pstCond->pfSet(pstCond,ConvNull);   
        
        //SSCOM_Output(" Conv timeout",sizeof(" Conv timeout"));
    }
    else
    {
        pstCond->pfSet(pstCond,ConvAct);    
        pstCond->stExec.pfunc(pstCond);
        
        //SSCOM_Output(" convert to ConvAct",sizeof(" convert to ConvAct"));
    }
    
}
/*********************************************************************************************************
** Function name:           BankAutoPush
** Descriptions:            成组推溜动作执行
** input parameters:        pCond 推溜条件
** output parameters:       none
** Returned value:          
** Created by:              linguofeng 
** Created Date:             2015-08-04
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
void ConvAct(void *pCond)
{
    INT32U u32Valve = 0;
	struct tag_CONV_COND_SET_S *pstCond = (struct tag_CONV_COND_SET_S *)pCond;
	
	if(NULL == pstCond){
		return;
	}	
    if((pstCond->stPkt.u32CmdCode != PUSH_CONVEYOR_CMD) && (pstCond->stPkt.u32CmdCode != ADVANCE_CMD) && 
		(pstCond->stPkt.u32CmdCode != CONVEYOR_PULLREAR_CMD))
	{
		return;
	}  

    VALVE_TBL(u32Valve,SHIELD_POS,pstCond->stPkt.u32CmdCode);
    SET_VALVE(u32Valve);
    pstCond->pfSet(pstCond,ConvPrsrNotReach); 
    
    //SSCOM_Output("   ConvAct",sizeof("   ConvAct"));
}
void ConvNull(void *pCond)
{
    
}
/*********************************************************************************************************
** Function name:           ConvSendNextGrp
** Descriptions:            成组推溜动作发送下一动作小组
** input parameters:        stRfhPkt u32StartTime
** output parameters:       none
** Returned value:          true 已经发送过，false未发送过
** Created by:              linguofeng 
** Created Date:             2015-08-04
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
static BOOLEAN ConvSendNextGrp(PKT_REFRESH_SCN_S stRfhPkt,INT32U u32StartTime,INT32U u32GrpDly)
{    
    CONTROL_PKT_S stPkt = stRfhPkt.stPkt;
    INT8U u8GrpNum = GetBPGrpNum();
    INT8U u8SArea = stPkt.u8SArea;
    INT8U u8TeamNum = 0;
	
    if (0 == u8GrpNum)
    {
        u8GrpNum = BP_GRP_NUM_DFT;
    }

    u8TeamNum = u8SArea/u8GrpNum;

    if (u8SArea == 0)
    {
        ERR_MESSAGE("ConvSendNextGrp Area err");
        return TRUE;
    }    
    /* 动作首末架及动作小组中间架直接返回，动作小组内控制报文已在之前发送过 */
    if ((0 == stPkt.u8Area)||
        (((u8SArea - stPkt.u8Area)%u8TeamNum) != 0)||
        (u8SArea == stPkt.u8Area))
    {
        return TRUE;
    }
  	
    if (mSecTimeCheck(u32StartTime,u32GrpDly))
    {
        tmWrite(stPkt.u8CommDir,0,stRfhPkt.u32PortAddr,
            sizeof(CONTROL_PKT_S),(void *) &stPkt,NOT_NEED_ACK); 

        return TRUE;
    }     
    return FALSE;
}
/*********************************************************************************************************
** Function name:           CheckAutoSafeOper
** Descriptions:            检查跟机状态下是否发生安全操作
** input parameters:        
** output parameters:       none
** Returned value:          none
** Created by:              linguofeng 
** Created Date:            2016-03-23
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
static BOOLEAN CheckAutoSafeOper(SCREEN_INDEX_E eScnIndex)
{
    BOOLEAN bRet = FALSE;
    if (AUTO_SCREEN == eScnIndex)
    {
        if (ESTOP_ACCURED == GetEStopStat())
        {
            bRet = TRUE;
        }       
    }

    return bRet;
}

/*********************************************************************************************************
** Function name:           WaitASQ
** Descriptions:            ASQ动作等待时间
** input parameters:        u32STime 开始动作时间
** output parameters:       none
** Returned value:          none
** Created by:              linguofeng 
** Created Date:            2015-08-05
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
static BOOLEAN WaitASQ(SCREEN_INDEX_E eScnIndex,INT32U u32STime)
{
    INT32U u32Time = SEC_TIMER;
    BOOLEAN bRet = TRUE;
    while((SEC_TIMER - u32Time) < u32STime)
    {
        RESPOND_TASK_DEL_REQ();
        OSTimeDly(TIME_DLY_20MS);
    }
    return bRet;
}
static BOOLEAN WaitWarning(SCREEN_INDEX_E eScnIndex,INT32U u32WaitTime)
{    
    return WaitASQ(eScnIndex,u32WaitTime);
}

/*********************************************************************************************************
** Function name:           AutoMiningDly
** Descriptions:            跟机过程中延时函数，仅限于在跟机自动化任务中调用
** input parameters:        u32Dly 延时时间 单位 秒
** output parameters:       none
** Returned value:          false;未发生急停；true急停被按下
** Created by:              linguofeng 
** Created Date:            2016-05-19
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
static BOOLEAN AutoMiningDly(INT32U u32Dly)
{
    INT32U u32Time = SEC_TIMER;
    BOOLEAN bRet = FALSE;
    while((SEC_TIMER - u32Time) < u32Dly)
    {
        if (CheckAutoSafeOper(AUTO_SCREEN))
        {
            bRet = TRUE;
            break;
        }
        OSTimeDly(TIME_DLY_20MS);
    }
    return bRet;
}
/*********************************************************************************************************
** Function name:           WaitExpend
** Descriptions:            放顶煤放煤等待
** input parameters:        u32STime 开始动作时间
** output parameters:       none
** Returned value:          none
** Created by:               gaocen 
** Created Date:            2016-04-09
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
static BOOLEAN WaitExpend(PKT_REFRESH_SCN_S *pstRfhPkt,SHILD_LINKAGE_S *pstShdLkg,SCREEN_INDEX_E eScnIndex,INT32U u32STime)
{
    INT32U u32Time = SEC_TIMER;
    BOOLEAN bRet = TRUE;
    while((SEC_TIMER - u32Time) < u32STime)
    {
		/* 架间延迟发送 */
        pstShdLkg->pfLSendNext(*pstRfhPkt,pstShdLkg);
		if (CheckAutoSafeOper(eScnIndex))
        {
            bRet = FALSE;
            break;
        }
        OSTimeDly(TIME_DLY_10MS);
    }
    return bRet;
}

/*********************************************************************************************************
** Function name:           BankAutoPush
** Descriptions:            成组推溜动作处理代码
** input parameters:        stRefreshPkt 发送数据
** output parameters:       none
** Returned value:          
** Created by:              linguofeng 
** Created Date:            2015-04-12
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/

void BankAutoPush(PKT_REFRESH_SCN_S stRfhPkt)
{
    INT32U u32Time = GetASQWarnT(); 
    INT8U u8GrpNum = GetBPGrpNum();
    INT8U u8SArea = stRfhPkt.stPkt.u8SArea;
    INT8U u8TeamNum = 0;
    SCN_RFH_MSG_S stRfhMsg;
    CONV_COND_SET_S stCond;
    BOOLEAN bSentNextGrp = FALSE;/* 是否已经发送给下一动作小组 */
    INT32U u32Valve = 0;
	
	/* 成组推溜预警 */
	if(u8SArea == stRfhPkt.stPkt.u8Area + 1)	/*首架判断*/
	{
		if (GetASQWarn())
		{
			ASQ_WARN_TPARA_CHK(u32Time);
			
			WaitWarning(BANK_CTRL_SCREEN,u32Time);
		}
	}
    if (0 == u8GrpNum)
    {
        u8GrpNum = BP_GRP_NUM_DFT;
    }
    u8TeamNum = u8SArea/u8GrpNum;
    /*只在当前小组发送*/
    //if (((u8SArea-stRfhPkt.stPkt.u8Area)%u8TeamNum)||(u8SArea == stRfhPkt.stPkt.u8Area))
	if((u8SArea-stRfhPkt.stPkt.u8Area)%u8TeamNum)
    {    
        if(stRfhPkt.stPkt.u8Area > 0) 
        { 
            tmWrite(stRfhPkt.stPkt.u8CommDir,0,stRfhPkt.u32PortAddr,
                sizeof(CONTROL_PKT_S),(void *) &stRfhPkt.stPkt,NOT_NEED_ACK);
        }
    }

    /* 发送动作执行命令到人机界面 */
    POST_INFO2SCN(stRfhMsg,BANK_CTRL_SCREEN,BANK_CONV_PUSH_MSG,BANK_ACT_INFO);
    ConvCondInit(&stCond,stRfhPkt.stPkt);
	
    /* 循环条件 推溜时间控制，推溜压力控制，推溜行程控制 */
	//while (!mSecTimeCheck(stCond.u32StartTime,(stCond.u32ConvTime + stCond.u32GrpDly)))
	while (!mSecTimeCheck(stCond.u32StartTime,
			(stCond.u32ConvTime >= stCond.u32GrpDly) ? stCond.u32ConvTime+1 : stCond.u32GrpDly+1))
	{
        stCond.stExec.pfunc(&stCond);

        if(!bSentNextGrp)
        {
            bSentNextGrp = ConvSendNextGrp(stRfhPkt,stCond.u32StartTime,stCond.u32GrpDly);
        }
		
        RESPOND_TASK_DEL_REQ();
        OSTimeDly(TIME_DLY_20MS);
    }
    
    VALVE_TBL(u32Valve,SHIELD_POS,PUSH_CONVEYOR_CMD);
    CLR_VALVE(u32Valve);    

}


/*********************************************************************************************************
** Function name:           BankAutoPull
** Descriptions:            成组拉溜动作处理代码
** input parameters:        stRefreshPkt 发送数据
** output parameters:       none
** Returned value:          
** Created by:              linguofeng 
** Created Date:            2015-04-13
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
void BankAutoPull(PKT_REFRESH_SCN_S stRfhPkt)
{
	INT32U u32Time = GetASQWarnT(); 
	INT8U u8GrpNum = GetCPGrpNum();
	INT8U u8SArea = stRfhPkt.stPkt.u8SArea;
	INT8U u8TeamNum = 0;
	SCN_RFH_MSG_S stRfhMsg;
	CONV_COND_SET_S stCond;
	BOOLEAN bSentNextGrp = FALSE;/* 是否已经发送给下一动作小组 */
	INT32U u32Valve = 0;


	/* 成组拉溜预警 */
	if(u8SArea == stRfhPkt.stPkt.u8Area)	/*首架判断*/
	{	
    	if (GetASQWarn())
    	{
       		ASQ_WARN_TPARA_CHK(u32Time);
        	u32Time = SECOND2MILLI(u32Time);
        	WaitWarning(BANK_CTRL_SCREEN,u32Time);
    	}
	}
	
	if (0 == u8GrpNum)
	{
		u8GrpNum = BP_GRP_NUM_DFT;
	}
	u8TeamNum = u8SArea/u8GrpNum;   // TODO: 不能整除怎么办?  例:u8SArea == 49 , u8GrpNum == 10  
	/*只在当前小组发送*/
	if (((u8SArea-stRfhPkt.stPkt.u8Area)%u8TeamNum)||(u8SArea == stRfhPkt.stPkt.u8Area))
	{	  
		if (stRfhPkt.stPkt.u8Area > 0)
		{
			tmWrite(stRfhPkt.stPkt.u8CommDir,0,stRfhPkt.u32PortAddr,
				 sizeof(CONTROL_PKT_S),(void *) &stRfhPkt.stPkt,NOT_NEED_ACK); 			 
		}		 
	}
	/* 发送动作执行命令到人机界面 */
	POST_INFO2SCN(stRfhMsg,BANK_CTRL_SCREEN,BANK_CONV_PULL_MSG,BANK_ACT_INFO);	 
	ConvCondInit(&stCond,stRfhPkt.stPkt);
	/* 循环条件 拉溜时间控制，拉溜压力控制，拉溜行程控制 */
	//while (!mSecTimeCheck(stCond.u32StartTime,(stCond.u32ConvTime + stCond.u32GrpDly)))
	while (!mSecTimeCheck(stCond.u32StartTime,
			(stCond.u32ConvTime >= stCond.u32GrpDly) ? stCond.u32ConvTime+1 : stCond.u32GrpDly+1))		
	{
		stCond.stExec.pfunc(&stCond);
	 
		if(!bSentNextGrp)
		{
			bSentNextGrp = ConvSendNextGrp(stRfhPkt,stCond.u32StartTime,stCond.u32GrpDly);
		}
			
		RESPOND_TASK_DEL_REQ();	 
		OSTimeDly(TIME_DLY_20MS);
	}
		
	VALVE_TBL(u32Valve,SHIELD_POS,ADVANCE_CMD);
	CLR_VALVE(u32Valve);   

}


/*********************************************************************************************************
** Function name:           BankAuto1stFlipOut
** Descriptions:            成组1级护帮伸
** input parameters:        stRefreshPkt 发送数据
** output parameters:       none
** Returned value:          
** Created by:              linguofeng 
** Created Date:            2015-04-13
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
void BankAuto1stFlipOut(PKT_REFRESH_SCN_S stRfhPkt)
{
	SCN_RFH_MSG_S stRfhMsg;
    INT32U u32Valve = 0;
    INT32U u32DlyTime = GetBankFlpFSdly();	
    INT32U u32ExTime = GetASQ1stFlipExT();	
    SHILD_COMPONENT_S stComp;

    /* 动作参数检查 */    
    BANK_CTRL_TPARA_CHECK(u32ExTime,u32DlyTime,FLIP_ACT_TIME_DFT,FLIP_FS_DLY_DFT);    
    /* 发送动作执行命令到人机界面 */
    POST_INFO2SCN(stRfhMsg,BANK_CTRL_SCREEN, BANK_FLP_1ST_EX_MSG,BANK_ACT_INFO);

    VALVE_TBL(u32Valve,SHIELD_POS,FST_FLIP_OUT_CMD);
    SET_VALVE(u32Valve);
	
    stComp.u32ErrIndex = FLIP1_LMT_NOT_REACH;    
    stComp.u32StartTime = MS_TIMER;
    stComp.u32ShdExtTime = SECOND2MILLI(u32ExTime);		
    stComp.u32DlySendNext = SECOND2MILLI(u32DlyTime);	
    stComp.pfSendNext = SendNextNull;
    stComp.pfShdPCtrl = ShdPressureCtrl;
    stComp.pfShdTCtrl = ShdTimeCtrl;
    stComp.pfTimeCheck = mSecTimeCheck;
    stComp.pfPCheck = Check1stFlipLmtP;
    stComp.u32Stat = SHD_COMP_NULL;
	stComp.u8Type = FST_FLIP_OUT_CMD;
	
    while(1)
    {
        /* 架间延迟时间到 */
        stComp.pfSendNext(stRfhPkt,&stComp);
        stComp.pfShdPCtrl(&stComp);
        stComp.pfShdTCtrl(&stComp);
    
        if (stComp.u32Stat == SHD_COMP_OVER)
        {
            break;
        }
		RESPOND_TASK_DEL_REQ();
        OSTimeDly(TIME_DLY_10MS);
    }

}


/*********************************************************************************************************
** Function name:           BankAuto1stFlipIn
** Descriptions:            成组1级护帮收
** input parameters:        stRefreshPkt 发送数据
** output parameters:       none
** Returned value:          
** Created by:              linguofeng 
** Created Date:            2015-04-13
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
void BankAuto1stFlipIn(PKT_REFRESH_SCN_S stRfhPkt)
{	
	SCN_RFH_MSG_S stRfhMsg;
    INT32U u32Valve = 0;
    INT32U u32DlyTime = GetBankFlpFSdly();	
    INT32U u32InTime = GetASQ1stFlipInT();	
    SHILD_COMPONENT_S stComp;

    /* 动作参数检查 */    
    BANK_CTRL_TPARA_CHECK(u32InTime,u32DlyTime,FLIP_ACT_TIME_DFT,FLIP_FS_DLY_DFT);   
    /* 发送动作执行命令到人机界面 */
	POST_INFO2SCN(stRfhMsg,BANK_CTRL_SCREEN, BANK_FLP_1ST_IN_MSG,BANK_ACT_INFO);

    VALVE_TBL(u32Valve,SHIELD_POS,FST_FLIP_IN_CMD);
    SET_VALVE(u32Valve);
	
    stComp.u32ErrIndex = FLIP1_LMT_NOT_REACH;    
	stComp.u32StartTime = MS_TIMER;
    stComp.u32ShdExtTime = SECOND2MILLI(u32InTime);		
    stComp.u32DlySendNext = SECOND2MILLI(u32DlyTime);	
    stComp.pfSendNext = SendNextNull;
    stComp.pfShdPCtrl = ShdPressureCtrl;
    stComp.pfShdTCtrl = ShdTimeCtrl;
    stComp.pfTimeCheck = mSecTimeCheck;
    stComp.pfPCheck = Check1stFlipLmtP;
    stComp.u32Stat = SHD_COMP_NULL;
	stComp.u8Type = FST_FLIP_IN_CMD;
	
    while(1)
    {
        /* 架间延迟时间到 */
        stComp.pfSendNext(stRfhPkt,&stComp);
        stComp.pfShdPCtrl(&stComp);
        stComp.pfShdTCtrl(&stComp);
    
        if (stComp.u32Stat == SHD_COMP_OVER)
        {
            break;
        }
		RESPOND_TASK_DEL_REQ();
        OSTimeDly(TIME_DLY_10MS);
    }
}


/*********************************************************************************************************
** Function name:           BankAutoFntCantileverOut
** Descriptions:            成组伸前梁
** input parameters:        stRefreshPkt 发送数据
** output parameters:       none
** Returned value:          
** Created by:              linguofeng 
** Created Date:            2015-04-13
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
void BankAutoFCantileverOut(PKT_REFRESH_SCN_S stRfhPkt)
{
	SCN_RFH_MSG_S stRfhMsg;
    INT32U u32Valve = 0;
    INT32U u32DlyTime = GetBankFCShieldDly();	
    INT32U u32ExTime = GetBankFCExT();	
    SHILD_COMPONENT_S stComp;

    /* 动作参数检查 */    
    BANK_CTRL_TPARA_CHECK(u32ExTime,u32DlyTime,FLIP_ACT_TIME_DFT,FLIP_FS_DLY_DFT);     
    /* 发送动作执行命令到人机界面 */
	POST_INFO2SCN(stRfhMsg,BANK_CTRL_SCREEN, BANK_FNT_CNTLV_EX_MSG,BANK_ACT_INFO);

    VALVE_TBL(u32Valve,SHIELD_POS,FRONT_CANTILEVER_SET_CMD);// TODO: 注意，已经超范围了，会导致数组越界
    SET_VALVE(u32Valve);
	
    stComp.u32ErrIndex = SLIDBAR_LMT_NOT_REACH;    
    stComp.u32StartTime = MS_TIMER;
    stComp.u32ShdExtTime = SECOND2MILLI(u32ExTime);	
    stComp.u32DlySendNext = SECOND2MILLI(u32DlyTime);
    stComp.pfSendNext = SendNextNull;
    stComp.pfShdPCtrl = ShdPressureCtrl;
    stComp.pfShdTCtrl = ShdTimeCtrl;
    stComp.pfTimeCheck = mSecTimeCheck;
    stComp.pfPCheck = Check1stFlipLmtP;
    stComp.u32Stat = SHD_COMP_NULL;
	stComp.u8Type = FRONT_CANTILEVER_SET_CMD;
	
    while(1)
    {
        /* 架间延迟时间到 */
        stComp.pfSendNext(stRfhPkt,&stComp);
        stComp.pfShdPCtrl(&stComp);
        stComp.pfShdTCtrl(&stComp);
    
        if (stComp.u32Stat == SHD_COMP_OVER)
        {
            break;
        }
		RESPOND_TASK_DEL_REQ();
        OSTimeDly(TIME_DLY_10MS);
    }

}


/*********************************************************************************************************
** Function name:           BankAutoFCantileverIn
** Descriptions:            成组收前梁
** input parameters:        stRefreshPkt 发送数据
** output parameters:       none
** Returned value:          
** Created by:              linguofeng 
** Created Date:            2015-04-13
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
void BankAutoFCantileverIn(PKT_REFRESH_SCN_S stRfhPkt)
{
	SCN_RFH_MSG_S stRfhMsg;
    INT32U u32Valve = 0;
    INT32U u32DlyTime = GetBankFCShieldDly();	
    INT32U u32InTime = GetBankFCInT();	
    SHILD_COMPONENT_S stComp;

    /* 动作参数检查 */    
    BANK_CTRL_TPARA_CHECK(u32InTime,u32DlyTime,FLIP_ACT_TIME_DFT,FLIP_FS_DLY_DFT);    
    /* 发送动作执行命令到人机界面 */
	POST_INFO2SCN(stRfhMsg,BANK_CTRL_SCREEN, BANK_FNT_CNTLV_IN_MSG,BANK_ACT_INFO);

    VALVE_TBL(u32Valve,SHIELD_POS,FRONT_CANTILEVER_LOWER_CMD);// TODO: 注意，已经超范围了，会导致数组越界
    SET_VALVE(u32Valve);
	
    stComp.u32ErrIndex = SLIDBAR_LMT_NOT_REACH;    
    stComp.u32StartTime = MS_TIMER;
    stComp.u32ShdExtTime = SECOND2MILLI(u32InTime);	
    stComp.u32DlySendNext = SECOND2MILLI(u32DlyTime);
    stComp.pfSendNext = SendNextNull;
    stComp.pfShdPCtrl = ShdPressureCtrl;
    stComp.pfShdTCtrl = ShdTimeCtrl;
    stComp.pfTimeCheck = mSecTimeCheck;
    stComp.pfPCheck = Check1stFlipLmtP;
    stComp.u32Stat = SHD_COMP_NULL;
	stComp.u8Type = FRONT_CANTILEVER_LOWER_CMD;
	
    while(1)
    {
        /* 架间延迟时间到 */
        stComp.pfSendNext(stRfhPkt,&stComp);
        stComp.pfShdPCtrl(&stComp);
        stComp.pfShdTCtrl(&stComp);
    
        if (stComp.u32Stat == SHD_COMP_OVER)
        {
            break;
        }
		RESPOND_TASK_DEL_REQ();
        OSTimeDly(TIME_DLY_10MS);
    }

}


/*********************************************************************************************************
** Function name:           BankAutoPullRear
** Descriptions:            成组拉后溜
** input parameters:        stRefreshPkt 发送数据
** output parameters:       none
** Returned value:          
** Created by:              linguofeng 
** Created Date:            2015-04-13
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
void BankAutoPullRear(PKT_REFRESH_SCN_S stRfhPkt)
{
	INT32U u32Time = GetASQWarnT(); 
	INT8U u8GrpNum = GetRCPGrpNum();
	INT8U u8SArea = stRfhPkt.stPkt.u8SArea;
	INT8U u8TeamNum = 0;
	SCN_RFH_MSG_S stRfhMsg;
	CONV_COND_SET_S stCond;
	BOOLEAN bSentNextGrp = FALSE;/* 是否已经发送给下一动作小组 */
	INT32U u32Valve = 0;


	/* 成组拉后溜预警 */
	if(u8SArea == stRfhPkt.stPkt.u8Area)	/*首架判断*/
	{	
    	if (GetASQWarn())
    	{
       		ASQ_WARN_TPARA_CHK(u32Time);
        	u32Time = SECOND2MILLI(u32Time);	
        	WaitWarning(BANK_CTRL_SCREEN,u32Time);
    	}
	}

	if (0 == u8GrpNum)
	{
		u8GrpNum = BP_GRP_NUM_DFT;
	}
	u8TeamNum = u8SArea/u8GrpNum;   // TODO: 不能整除怎么办  例:u8SArea == 49 , u8GrpNum == 10  
	/*只在当前小组发送*/
	if (((u8SArea-stRfhPkt.stPkt.u8Area)%u8TeamNum)||(u8SArea == stRfhPkt.stPkt.u8Area))
	{	  
		if (stRfhPkt.stPkt.u8Area > 0)
		{
			tmWrite(stRfhPkt.stPkt.u8CommDir,0,stRfhPkt.u32PortAddr,
				 sizeof(CONTROL_PKT_S),(void *) &stRfhPkt.stPkt,NOT_NEED_ACK); 
		}
	}
	
	/* 发送动作执行命令到人机界面 */
	POST_INFO2SCN(stRfhMsg,BANK_CTRL_SCREEN,BANK_PULL_BACK_MSG,BANK_ACT_INFO);	
	ConvCondInit(&stCond,stRfhPkt.stPkt);
	
	/* 循环条件 拉溜时间控制，拉溜压力控制，拉溜行程控制 */
	//while (!mSecTimeCheck(stCond.u32StartTime,(stCond.u32ConvTime + stCond.u32GrpDly)))
	while (!mSecTimeCheck(stCond.u32StartTime,
			(stCond.u32ConvTime >= stCond.u32GrpDly) ? stCond.u32ConvTime+1 : stCond.u32GrpDly+1))		
	{
		stCond.stExec.pfunc(&stCond);
 
		if(!bSentNextGrp)
		{
			bSentNextGrp = ConvSendNextGrp(stRfhPkt,stCond.u32StartTime,stCond.u32GrpDly);
		}
		
		RESPOND_TASK_DEL_REQ(); 
		OSTimeDly(TIME_DLY_20MS);
	}
	
	VALVE_TBL(u32Valve,SHIELD_POS,ADVANCE_CMD); // TODO:拉后溜电磁阀在哪里
	CLR_VALVE(u32Valve);   

}

/*********************************************************************************************************
** Function name:           BankAutoSlidBarOut
** Descriptions:            成组伸伸缩梁
** input parameters:        stRefreshPkt 发送数据
** output parameters:       none
** Returned value:          
** Created by:              linguofeng 
** Created Date:            2015-04-13
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
void BankAutoSlidBarOut(PKT_REFRESH_SCN_S stRfhPkt)
{
	SCN_RFH_MSG_S stRfhMsg;
    INT32U u32Valve = 0;
    INT32U u32DlyTime = GetBankSBShieldDly();
    INT32U u32ExTime = GetBankSBExT();
    SHILD_COMPONENT_S stComp;

    /* 动作参数检查 */    
    BANK_CTRL_TPARA_CHECK(u32ExTime,u32DlyTime,FLIP_ACT_TIME_DFT,FLIP_FS_DLY_DFT);   
    /* 发送动作执行命令到人机界面 */
	POST_INFO2SCN(stRfhMsg,BANK_CTRL_SCREEN, BANK_SB_EX_MSG,BANK_ACT_INFO);

    VALVE_TBL(u32Valve,SHIELD_POS,SLIDEBAR_OUT_CMD);
    SET_VALVE(u32Valve);
	
    stComp.u32ErrIndex = SLIDBAR_LMT_NOT_REACH;    
    stComp.u32StartTime = MS_TIMER;
    stComp.u32ShdExtTime = SECOND2MILLI(u32ExTime);
    stComp.u32DlySendNext = SECOND2MILLI(u32DlyTime);
    stComp.pfSendNext = SendNextNull;
    stComp.pfShdPCtrl = ShdPressureCtrl;
    stComp.pfShdTCtrl = ShdTimeCtrl;
    stComp.pfTimeCheck = mSecTimeCheck;
    stComp.pfPCheck = CheckSlidBarLmtP;
    stComp.u32Stat = SHD_COMP_NULL;
	stComp.u8Type = SLIDEBAR_OUT_CMD;
	
    while(1)
    {
        /* 架间延迟时间到 */
        stComp.pfSendNext(stRfhPkt,&stComp);
        stComp.pfShdPCtrl(&stComp);
        stComp.pfShdTCtrl(&stComp);
    
        if (stComp.u32Stat == SHD_COMP_OVER)
        {
            break;
        }
		RESPOND_TASK_DEL_REQ();
        OSTimeDly(TIME_DLY_10MS);
    }

}


/*********************************************************************************************************
** Function name:           BankAutoSlidBarIn
** Descriptions:            成组收伸缩梁
** input parameters:        stRefreshPkt 发送数据
** output parameters:       none
** Returned value:          
** Created by:              linguofeng 
** Created Date:            2015-04-13
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
void BankAutoSlidBarIn(PKT_REFRESH_SCN_S stRfhPkt)
{
	SCN_RFH_MSG_S stRfhMsg;
    INT32U u32Valve = 0;
    INT32U u32DlyTime = GetBankSBShieldDly();	
    INT32U u32InTime = GetBankSBInT();	
    SHILD_COMPONENT_S stComp;

    /* 动作参数检查 */    
    BANK_CTRL_TPARA_CHECK(u32InTime,u32DlyTime,FLIP_ACT_TIME_DFT,FLIP_FS_DLY_DFT);    
    /* 发送动作执行命令到人机界面 */
	POST_INFO2SCN(stRfhMsg,BANK_CTRL_SCREEN, BANK_SB_IN_MSG,BANK_ACT_INFO);

    VALVE_TBL(u32Valve,SHIELD_POS,SLIDEBAR_IN_CMD);
    SET_VALVE(u32Valve);
	
    stComp.u32ErrIndex = SLIDBAR_LMT_NOT_REACH;    
    stComp.u32StartTime = MS_TIMER;
    stComp.u32ShdExtTime = SECOND2MILLI(u32InTime);
    stComp.u32DlySendNext = SECOND2MILLI(u32DlyTime);
    stComp.pfSendNext = SendNextNull;
    stComp.pfShdPCtrl = ShdPressureCtrl;
    stComp.pfShdTCtrl = ShdTimeCtrl;
    stComp.pfTimeCheck = mSecTimeCheck;
    stComp.pfPCheck = CheckSlidBarLmtP;
    stComp.u32Stat = SHD_COMP_NULL;
	stComp.u8Type = SLIDEBAR_IN_CMD;
	
    while(1)
    {
        /* 架间延迟时间到 */
        stComp.pfSendNext(stRfhPkt,&stComp);
        stComp.pfShdPCtrl(&stComp);
        stComp.pfShdTCtrl(&stComp);
    
        if (stComp.u32Stat == SHD_COMP_OVER)
        {
            break;
        }
		RESPOND_TASK_DEL_REQ();
        OSTimeDly(TIME_DLY_10MS);
    }

}



/*********************************************************************************************************
** Function name:           BankAuto2ndFlipOut
** Descriptions:            成组2级护帮伸
** input parameters:        stRefreshPkt 发送数据
** output parameters:       none
** Returned value:          
** Created by:              linguofeng 
** Created Date:            2015-04-13
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
void BankAuto2ndFlipOut(PKT_REFRESH_SCN_S stRfhPkt)
{
    SCN_RFH_MSG_S stRfhMsg;
    INT32U u32Valve = 0;
    INT32U u32DlyTime = GetBankFlpFSdly();
    INT32U u32ExTime = GetASQ2ndFlipExT();	
    SHILD_COMPONENT_S stComp;

    /* 动作参数检查 */    
    BANK_CTRL_TPARA_CHECK(u32ExTime,u32DlyTime,FLIP_ACT_TIME_DFT,FLIP_FS_DLY_DFT);   
    /* 发送动作执行命令到人机界面 */
    POST_INFO2SCN(stRfhMsg,BANK_CTRL_SCREEN, BANK_FLP_2ND_EX_MSG,BANK_ACT_INFO);

    VALVE_TBL(u32Valve,SHIELD_POS,SND_FLIP_OUT_CMD);
    SET_VALVE(u32Valve);
	
    stComp.u32ErrIndex = FLIP1_LMT_NOT_REACH;    
    stComp.u32StartTime = MS_TIMER;
    stComp.u32ShdExtTime = SECOND2MILLI(u32ExTime);
    stComp.u32DlySendNext = SECOND2MILLI(u32DlyTime);
    stComp.pfSendNext = SendNextNull;
    stComp.pfShdPCtrl = ShdPressureCtrl;
    stComp.pfShdTCtrl = ShdTimeCtrl;
    stComp.pfTimeCheck = mSecTimeCheck;
    stComp.pfPCheck = Check2ndFlipLmtP;
    stComp.u32Stat = SHD_COMP_NULL;
	stComp.u8Type = SND_FLIP_OUT_CMD;
	
    while(1)
    {
        /* 架间延迟时间到 */
        stComp.pfSendNext(stRfhPkt,&stComp);
        stComp.pfShdPCtrl(&stComp);
        stComp.pfShdTCtrl(&stComp);
    
        if (stComp.u32Stat == SHD_COMP_OVER)
        {
            break;
        }
		RESPOND_TASK_DEL_REQ();
        OSTimeDly(TIME_DLY_10MS);
    }

}



/*********************************************************************************************************
** Function name:           BankAuto2ndFlipIn
** Descriptions:            成组2级护帮收
** input parameters:        stRefreshPkt 发送数据
** output parameters:       none
** Returned value:          
** Created by:              linguofeng 
** Created Date:            2015-04-13
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
void BankAuto2ndFlipIn(PKT_REFRESH_SCN_S stRfhPkt)
{
    SCN_RFH_MSG_S stRfhMsg;
    INT32U u32Valve = 0;
    INT32U u32DlyTime = GetBankFlpFSdly();
    INT32U u32InTime = GetASQ2ndFlipInT();
    SHILD_COMPONENT_S stComp;

    /* 动作参数检查 */    
    BANK_CTRL_TPARA_CHECK(u32InTime,u32DlyTime,FLIP_ACT_TIME_DFT,FLIP_FS_DLY_DFT);     
    /* 发送动作执行命令到人机界面 */
    POST_INFO2SCN(stRfhMsg,BANK_CTRL_SCREEN, BANK_FLP_2ND_IN_MSG,BANK_ACT_INFO);

    VALVE_TBL(u32Valve,SHIELD_POS,SND_FLIP_IN_CMD);
    SET_VALVE(u32Valve);
	
    stComp.u32ErrIndex = FLIP1_LMT_NOT_REACH;    
    stComp.u32StartTime = MS_TIMER;
    stComp.u32ShdExtTime = SECOND2MILLI(u32InTime);
    stComp.u32DlySendNext = SECOND2MILLI(u32DlyTime);
    stComp.pfSendNext = SendNextNull;
    stComp.pfShdPCtrl = ShdPressureCtrl;
    stComp.pfShdTCtrl = ShdTimeCtrl;
    stComp.pfTimeCheck = mSecTimeCheck;
    stComp.pfPCheck = Check2ndFlipLmtP;
    stComp.u32Stat = SHD_COMP_NULL;
	stComp.u8Type = SND_FLIP_IN_CMD;
	
    while(1)
    {
        /* 架间延迟时间到 */
        stComp.pfSendNext(stRfhPkt,&stComp);
        stComp.pfShdPCtrl(&stComp);
        stComp.pfShdTCtrl(&stComp);
    
        if (stComp.u32Stat == SHD_COMP_OVER)
        {
            break;
        }
		RESPOND_TASK_DEL_REQ();
        OSTimeDly(TIME_DLY_10MS);
    }

}
/*********************************************************************************************************
** Function name:           FlipLinkageOutInit
** Descriptions:            成组联动参数初始化
** input parameters:        pstShdLkg  联动参数结构体
** output parameters:       none
** Returned value:          
** Created by:               gaocen
** Created Date:            2015-08-28
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
void FlipLinkageOutInit(PKT_REFRESH_SCN_S stRfhPkt, SHILD_LINKAGE_S *pstShdLkg)
{
    INT32U u32DlyTime = GetBankFlpFSdly();	
    INT32U u32ExSTime1 = GetASQ1stFlipExST();
	INT32U u32ExTime1 = GetASQ1stFlipExT();
	INT32U u32ExSTime2 = GetASQ2ndFlipExST();
	INT32U u32ExTime2 = GetASQ2ndFlipExT();
	INT32U u32ExSTime3 = GetASQ3rdFlipExST();
	INT32U u32ExTime3 = GetASQ3rdFlipExT();

	/*时间参数检查*/
	if(0 == u32ExTime1){
		u32ExTime1 = FLP1_EX_TIME_DEF;
	}
	if(0 == u32ExTime2){
		u32ExTime2 = FLP2_EX_TIME_DEF;
	}	
	if(0 ==u32ExTime3){
		u32ExTime3 = FLP3_EX_TIME_DEF;
	}					
	if((u32ExSTime1 >= u32ExSTime2)||(u32ExSTime2 >= u32ExSTime3))
	{
		u32ExSTime1 = FLP1_EX_STIME_DEF;  
		u32ExSTime2 = FLP2_EX_STIME_DEF;
		u32ExSTime3 = FLP3_EX_STIME_DEF;						
	}
	if((u32ExSTime3 + u32ExTime3) < u32DlyTime)
	{
		u32DlyTime = FLP2_EX_STIME_DEF;    // TODO:根据实际情况更改
	}	
	/*支架整机参数初始化*/
	pstShdLkg->u32LStartTime = MS_TIMER;
	pstShdLkg->u32LDlySendTime = SECOND2MILLI(u32DlyTime);
	pstShdLkg->u32LStat = LKG_NULL; 
	pstShdLkg->u8LType = stRfhPkt.stPkt.u32CmdCode;
	pstShdLkg->pfLSendNext = LinkSendNextNull;
	pstShdLkg->pfLTimeCheck = mSecTimeCheck;	
	/*动作成员一级护帮参数初始化*/
	pstShdLkg->stLComp[LKG_COMP_FLIP1].u32ErrIndex = FLIP1_LMT_NOT_REACH;
	pstShdLkg->stLComp[LKG_COMP_FLIP1].u32BaseTime = MS_TIMER;
	pstShdLkg->stLComp[LKG_COMP_FLIP1].u32StartTime = SECOND2MILLI(u32ExSTime1);	
	pstShdLkg->stLComp[LKG_COMP_FLIP1].u32ExtTime = SECOND2MILLI(u32ExTime1);
	pstShdLkg->stLComp[LKG_COMP_FLIP1].u32Stat = LKG_NULL;
	pstShdLkg->stLComp[LKG_COMP_FLIP1].u8Type = FST_FLIP_OUT_CMD;
	pstShdLkg->stLComp[LKG_COMP_FLIP1].pfCompPCheck = Check1stFlipLmtP;
	pstShdLkg->stLComp[LKG_COMP_FLIP1].pfCompTCheck = mSecTimeCheck;
	pstShdLkg->stLComp[LKG_COMP_FLIP1].pfCompPCtrl = ShdLinkPrsCtrl;
	pstShdLkg->stLComp[LKG_COMP_FLIP1].pfCompTCtrl = ShdLinkTimeCtrl;
	pstShdLkg->stLComp[LKG_COMP_FLIP1].pfCompSCtrl = ShdLinkStartCtrl;	
	/*动作成员二级护帮参数初始化*/
	pstShdLkg->stLComp[LKG_COMP_FLIP2].u32ErrIndex = FLIP2_LMT_NOT_REACH;
	pstShdLkg->stLComp[LKG_COMP_FLIP2].u32BaseTime = MS_TIMER;
	pstShdLkg->stLComp[LKG_COMP_FLIP2].u32StartTime = SECOND2MILLI(u32ExSTime2);
	pstShdLkg->stLComp[LKG_COMP_FLIP2].u32ExtTime = SECOND2MILLI(u32ExTime2);	
	pstShdLkg->stLComp[LKG_COMP_FLIP2].u32Stat = LKG_NULL; 
	pstShdLkg->stLComp[LKG_COMP_FLIP2].u8Type = SND_FLIP_OUT_CMD;
	pstShdLkg->stLComp[LKG_COMP_FLIP2].pfCompPCheck = Check2ndFlipLmtP;
	pstShdLkg->stLComp[LKG_COMP_FLIP2].pfCompTCheck = mSecTimeCheck;
	pstShdLkg->stLComp[LKG_COMP_FLIP2].pfCompPCtrl = ShdLinkPrsCtrl;
	pstShdLkg->stLComp[LKG_COMP_FLIP2].pfCompTCtrl = ShdLinkTimeCtrl;
	pstShdLkg->stLComp[LKG_COMP_FLIP2].pfCompSCtrl = ShdLinkStartCtrl;
	/*动作成员三级护帮参数初始化*/
	pstShdLkg->stLComp[LKG_COMP_FLIP3].u32ErrIndex = FLIP3_LMT_NOT_REACH;
	pstShdLkg->stLComp[LKG_COMP_FLIP3].u32BaseTime = MS_TIMER;
	pstShdLkg->stLComp[LKG_COMP_FLIP3].u32StartTime = SECOND2MILLI(u32ExSTime3);
	pstShdLkg->stLComp[LKG_COMP_FLIP3].u32ExtTime = SECOND2MILLI(u32ExTime3);	
	pstShdLkg->stLComp[LKG_COMP_FLIP3].u32Stat = LKG_NULL; 
	pstShdLkg->stLComp[LKG_COMP_FLIP3].u8Type = THD_FLIP_OUT_CMD;
	pstShdLkg->stLComp[LKG_COMP_FLIP3].pfCompPCheck = Check3rdFlipLmtP;
	pstShdLkg->stLComp[LKG_COMP_FLIP3].pfCompTCheck = mSecTimeCheck;
	pstShdLkg->stLComp[LKG_COMP_FLIP3].pfCompPCtrl = ShdLinkPrsCtrl;
	pstShdLkg->stLComp[LKG_COMP_FLIP3].pfCompTCtrl = ShdLinkTimeCtrl;
	pstShdLkg->stLComp[LKG_COMP_FLIP3].pfCompSCtrl = ShdLinkStartCtrl;
	return;
}
/*********************************************************************************************************
** Function name:           FlipLinkageInInit
** Descriptions:            成组联动参数初始化
** input parameters:        pstShdLkg  联动参数结构体
** output parameters:       none
** Returned value:          
** Created by:               gaocen
** Created Date:            2015-08-28
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
void FlipLinkageInInit(PKT_REFRESH_SCN_S stRfhPkt, SHILD_LINKAGE_S *pstShdLkg)
{
    INT32U u32DlyTime = GetBankFlpFSdly();	
    INT32U u32InSTime1 = GetASQ1stFlipInST();
	INT32U u32InTime1 = GetASQ1stFlipInT();
	INT32U u32InSTime2 = GetASQ2ndFlipInST();
	INT32U u32InTime2 = GetASQ2ndFlipInT();
	INT32U u32InSTime3 = GetASQ3rdFlipInST();
	INT32U u32InTime3 = GetASQ3rdFlipInT();

	/*时间参数检查*/
	if(0 == u32InTime1){
		u32InTime1 = FLP1_IN_TIME_DEF;
	}
	if(0 == u32InTime2){
		u32InTime2 = FLP2_IN_TIME_DEF;
	}	
	if(0 ==u32InTime3){
		u32InTime3 = FLP3_IN_TIME_DEF;
	}					
	if((u32InSTime3 >= u32InSTime2)||(u32InSTime2 >= u32InSTime1))
	{
		u32InSTime1 = FLP1_IN_STIME_DEF;  
		u32InSTime2 = FLP2_IN_STIME_DEF;
		u32InSTime3 = FLP3_IN_STIME_DEF;						
	}
	if((u32InSTime1 + u32InTime1) < u32DlyTime)
	{
		u32DlyTime = FLP2_IN_STIME_DEF;    // TODO:根据实际情况更改
	}	
	/*支架整机参数初始化*/
	pstShdLkg->u32LStartTime = MS_TIMER;
	pstShdLkg->u32LDlySendTime = SECOND2MILLI(u32DlyTime);
	pstShdLkg->u32LStat = LKG_NULL; 
	pstShdLkg->u8LType = stRfhPkt.stPkt.u32CmdCode;
	pstShdLkg->pfLSendNext = LinkSendNextNull;
	pstShdLkg->pfLTimeCheck = mSecTimeCheck;	
	/*动作成员一级护帮参数初始化*/
	pstShdLkg->stLComp[LKG_COMP_FLIP1].u32ErrIndex = FLIP1_LMT_NOT_REACH;
	pstShdLkg->stLComp[LKG_COMP_FLIP1].u32BaseTime = MS_TIMER;
	pstShdLkg->stLComp[LKG_COMP_FLIP1].u32StartTime = SECOND2MILLI(u32InSTime1);
	pstShdLkg->stLComp[LKG_COMP_FLIP1].u32ExtTime = SECOND2MILLI(u32InTime1);
	pstShdLkg->stLComp[LKG_COMP_FLIP1].u32Stat = LKG_NULL;
	pstShdLkg->stLComp[LKG_COMP_FLIP1].u8Type = FST_FLIP_IN_CMD;
	pstShdLkg->stLComp[LKG_COMP_FLIP1].pfCompPCheck = Check1stFlipLmtP;
	pstShdLkg->stLComp[LKG_COMP_FLIP1].pfCompTCheck = mSecTimeCheck;
	pstShdLkg->stLComp[LKG_COMP_FLIP1].pfCompPCtrl = ShdLinkPrsCtrl;
	pstShdLkg->stLComp[LKG_COMP_FLIP1].pfCompTCtrl = ShdLinkTimeCtrl;
	pstShdLkg->stLComp[LKG_COMP_FLIP1].pfCompSCtrl = ShdLinkStartCtrl;	
	/*动作成员二级护帮参数初始化*/
	pstShdLkg->stLComp[LKG_COMP_FLIP2].u32ErrIndex = FLIP2_LMT_NOT_REACH;
	pstShdLkg->stLComp[LKG_COMP_FLIP2].u32BaseTime = MS_TIMER;
	pstShdLkg->stLComp[LKG_COMP_FLIP2].u32StartTime = SECOND2MILLI(u32InSTime2);
	pstShdLkg->stLComp[LKG_COMP_FLIP2].u32ExtTime = SECOND2MILLI(u32InTime2);
	pstShdLkg->stLComp[LKG_COMP_FLIP2].u32Stat = LKG_NULL; 
	pstShdLkg->stLComp[LKG_COMP_FLIP2].u8Type = SND_FLIP_IN_CMD;
	pstShdLkg->stLComp[LKG_COMP_FLIP2].pfCompPCheck = Check2ndFlipLmtP;
	pstShdLkg->stLComp[LKG_COMP_FLIP2].pfCompTCheck = mSecTimeCheck;
	pstShdLkg->stLComp[LKG_COMP_FLIP2].pfCompPCtrl = ShdLinkPrsCtrl;
	pstShdLkg->stLComp[LKG_COMP_FLIP2].pfCompTCtrl = ShdLinkTimeCtrl;
	pstShdLkg->stLComp[LKG_COMP_FLIP2].pfCompSCtrl = ShdLinkStartCtrl;
	/*动作成员三级护帮参数初始化*/
	pstShdLkg->stLComp[LKG_COMP_FLIP3].u32ErrIndex = FLIP3_LMT_NOT_REACH;
	pstShdLkg->stLComp[LKG_COMP_FLIP3].u32BaseTime = MS_TIMER;
	pstShdLkg->stLComp[LKG_COMP_FLIP3].u32StartTime = SECOND2MILLI(u32InSTime3);
	pstShdLkg->stLComp[LKG_COMP_FLIP3].u32ExtTime = SECOND2MILLI(u32InTime3);	
	pstShdLkg->stLComp[LKG_COMP_FLIP3].u32Stat = LKG_NULL;	
	pstShdLkg->stLComp[LKG_COMP_FLIP3].u8Type = THD_FLIP_IN_CMD;
	pstShdLkg->stLComp[LKG_COMP_FLIP3].pfCompPCheck = Check3rdFlipLmtP;
	pstShdLkg->stLComp[LKG_COMP_FLIP3].pfCompTCheck = mSecTimeCheck;
	pstShdLkg->stLComp[LKG_COMP_FLIP3].pfCompPCtrl = ShdLinkPrsCtrl;
	pstShdLkg->stLComp[LKG_COMP_FLIP3].pfCompTCtrl = ShdLinkTimeCtrl;
	pstShdLkg->stLComp[LKG_COMP_FLIP3].pfCompSCtrl = ShdLinkStartCtrl;

	return;
}
/*********************************************************************************************************
** Function name:           SBLinkageOutInit
** Descriptions:            成组联动参数初始化
** input parameters:        pstShdLkg  联动参数结构体
** output parameters:       none
** Returned value:          
** Created by:               gaocen
** Created Date:            2015-08-28
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
void SBLinkageOutInit(PKT_REFRESH_SCN_S stRfhPkt, SHILD_LINKAGE_S *pstShdLkg)
{
    INT32U u32DlyTime = GetBankFlpFSdly();
    INT32U u32ExSTime0 = GetASQSBExST();
	INT32U u32ExTime0 = GetASQSBExT();	
    INT32U u32ExSTime1 = GetASQ1stFlipExST();
	INT32U u32ExTime1 = GetASQ1stFlipExT();
	INT32U u32ExSTime2 = GetASQ2ndFlipExST();
	INT32U u32ExTime2 = GetASQ2ndFlipExT();
	INT32U u32ExSTime3 = GetASQ3rdFlipExST();
	INT32U u32ExTime3 = GetASQ3rdFlipExT();

	/*时间参数检查*/
	if(0 == u32ExTime0){
		u32ExTime0 = SB_EX_TIME_DEF;
	}	
	if(0 == u32ExTime1){
		u32ExTime1 = FLP1_EX_TIME_DEF;
	}
	if(0 == u32ExTime2){
		u32ExTime2 = FLP2_EX_TIME_DEF;
	}	
	if(0 ==u32ExTime3){
		u32ExTime3 = FLP3_EX_TIME_DEF;
	}					
	if((u32ExSTime0 >= u32ExSTime1)||(u32ExSTime1 >= u32ExSTime2)||(u32ExSTime2 >= u32ExSTime3))
	{
		u32ExSTime0 = SB_EX_STIME_DEF;  
		u32ExSTime1 = FLP1_EX_STIME_DEF;  
		u32ExSTime2 = FLP2_EX_STIME_DEF;
		u32ExSTime3 = FLP3_EX_STIME_DEF;						
	}
	if((u32ExSTime3 + u32ExTime3) < u32DlyTime)
	{
		u32DlyTime = FLP2_EX_STIME_DEF;    // TODO:根据实际情况更改
	}	
	
	/*支架整机参数初始化*/
	pstShdLkg->u32LStartTime = MS_TIMER;
	pstShdLkg->u32LDlySendTime = SECOND2MILLI(u32DlyTime);
	pstShdLkg->u32LStat = LKG_NULL; 
	pstShdLkg->u8LType = stRfhPkt.stPkt.u32CmdCode;
	pstShdLkg->pfLSendNext = LinkSendNextNull;
	pstShdLkg->pfLTimeCheck = mSecTimeCheck;
	/*动作成员伸缩梁参数初始化*/
	pstShdLkg->stLComp[LKG_COMP_SB].u32ErrIndex = SLIDBAR_LMT_NOT_REACH;
	pstShdLkg->stLComp[LKG_COMP_SB].u32BaseTime = MS_TIMER;
	pstShdLkg->stLComp[LKG_COMP_SB].u32StartTime = SECOND2MILLI(u32ExSTime0);	
	pstShdLkg->stLComp[LKG_COMP_SB].u32ExtTime = SECOND2MILLI(u32ExTime0);	
	pstShdLkg->stLComp[LKG_COMP_SB].u32Stat = LKG_NULL;
	pstShdLkg->stLComp[LKG_COMP_SB].u8Type = SLIDEBAR_OUT_CMD;
	pstShdLkg->stLComp[LKG_COMP_SB].pfCompPCheck = Check1stFlipLmtP;
	pstShdLkg->stLComp[LKG_COMP_SB].pfCompTCheck = mSecTimeCheck;
	pstShdLkg->stLComp[LKG_COMP_SB].pfCompPCtrl = ShdLinkPrsCtrl;
	pstShdLkg->stLComp[LKG_COMP_SB].pfCompTCtrl = ShdLinkTimeCtrl;
	pstShdLkg->stLComp[LKG_COMP_SB].pfCompSCtrl = ShdLinkStartCtrl;	
	/*动作成员一级护帮参数初始化*/
	pstShdLkg->stLComp[LKG_COMP_FLIP1].u32ErrIndex = FLIP1_LMT_NOT_REACH;
	pstShdLkg->stLComp[LKG_COMP_FLIP1].u32BaseTime = MS_TIMER;
	pstShdLkg->stLComp[LKG_COMP_FLIP1].u32StartTime = SECOND2MILLI(u32ExSTime1);
	pstShdLkg->stLComp[LKG_COMP_FLIP1].u32ExtTime = SECOND2MILLI(u32ExTime1);
	pstShdLkg->stLComp[LKG_COMP_FLIP1].u32Stat = LKG_NULL;
	pstShdLkg->stLComp[LKG_COMP_FLIP1].u8Type = FST_FLIP_OUT_CMD;
	pstShdLkg->stLComp[LKG_COMP_FLIP1].pfCompPCheck = CheckSlidBarLmtP;
	pstShdLkg->stLComp[LKG_COMP_FLIP1].pfCompTCheck = mSecTimeCheck;
	pstShdLkg->stLComp[LKG_COMP_FLIP1].pfCompPCtrl = ShdLinkPrsCtrl;
	pstShdLkg->stLComp[LKG_COMP_FLIP1].pfCompTCtrl = ShdLinkTimeCtrl;
	pstShdLkg->stLComp[LKG_COMP_FLIP1].pfCompSCtrl = ShdLinkStartCtrl;	
	/*动作成员二级护帮参数初始化*/
	pstShdLkg->stLComp[LKG_COMP_FLIP2].u32ErrIndex = FLIP2_LMT_NOT_REACH; 
	pstShdLkg->stLComp[LKG_COMP_FLIP2].u32BaseTime = MS_TIMER;
	pstShdLkg->stLComp[LKG_COMP_FLIP2].u32StartTime = SECOND2MILLI(u32ExSTime2);
	pstShdLkg->stLComp[LKG_COMP_FLIP2].u32ExtTime = SECOND2MILLI(u32ExTime2);	
	pstShdLkg->stLComp[LKG_COMP_FLIP2].u32Stat = LKG_NULL; 
	pstShdLkg->stLComp[LKG_COMP_FLIP2].u8Type = SND_FLIP_OUT_CMD;
	pstShdLkg->stLComp[LKG_COMP_FLIP2].pfCompPCheck = Check2ndFlipLmtP;
	pstShdLkg->stLComp[LKG_COMP_FLIP2].pfCompTCheck = mSecTimeCheck;
	pstShdLkg->stLComp[LKG_COMP_FLIP2].pfCompPCtrl = ShdLinkPrsCtrl;
	pstShdLkg->stLComp[LKG_COMP_FLIP2].pfCompTCtrl = ShdLinkTimeCtrl;
	pstShdLkg->stLComp[LKG_COMP_FLIP2].pfCompSCtrl = ShdLinkStartCtrl;
	/*动作成员三级护帮参数初始化*/
	pstShdLkg->stLComp[LKG_COMP_FLIP3].u32ErrIndex = FLIP3_LMT_NOT_REACH; 
	pstShdLkg->stLComp[LKG_COMP_FLIP3].u32BaseTime = MS_TIMER;
	pstShdLkg->stLComp[LKG_COMP_FLIP3].u32StartTime = SECOND2MILLI(u32ExSTime3);
	pstShdLkg->stLComp[LKG_COMP_FLIP3].u32ExtTime = SECOND2MILLI(u32ExTime3);	
	pstShdLkg->stLComp[LKG_COMP_FLIP3].u32Stat = LKG_NULL;	
	pstShdLkg->stLComp[LKG_COMP_FLIP3].u8Type = THD_FLIP_OUT_CMD;
	pstShdLkg->stLComp[LKG_COMP_FLIP3].pfCompPCheck = Check3rdFlipLmtP;
	pstShdLkg->stLComp[LKG_COMP_FLIP3].pfCompTCheck = mSecTimeCheck;
	pstShdLkg->stLComp[LKG_COMP_FLIP3].pfCompPCtrl = ShdLinkPrsCtrl;
	pstShdLkg->stLComp[LKG_COMP_FLIP3].pfCompTCtrl = ShdLinkTimeCtrl;
	pstShdLkg->stLComp[LKG_COMP_FLIP3].pfCompSCtrl = ShdLinkStartCtrl;

	return;

}
/*********************************************************************************************************
** Function name:           SBLinkageInInit
** Descriptions:            成组联动参数初始化
** input parameters:        pstShdLkg  联动参数结构体
** output parameters:       none
** Returned value:          
** Created by:               gaocen
** Created Date:            2015-08-28
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
void SBLinkageInInit(PKT_REFRESH_SCN_S stRfhPkt, SHILD_LINKAGE_S *pstShdLkg)
{
    INT32U u32DlyTime = GetBankFlpFSdly();
    INT32U u32InSTime0 = GetASQSBInST();
	INT32U u32InTime0 = GetASQSBInT();	
    INT32U u32InSTime1 = GetASQ1stFlipInST();
	INT32U u32InTime1 = GetASQ1stFlipInT();
	INT32U u32InSTime2 = GetASQ2ndFlipInST();
	INT32U u32InTime2 = GetASQ2ndFlipInT();
	INT32U u32InSTime3 = GetASQ3rdFlipInST();
	INT32U u32InTime3 = GetASQ3rdFlipInT();

	/*时间参数检查*/
	if(0 == u32InTime0){
		u32InTime0 = SB_IN_TIME_DEF;
	}	
	if(0 == u32InTime1){
		u32InTime1 = FLP1_IN_TIME_DEF;
	}
	if(0 == u32InTime2){
		u32InTime2 = FLP2_IN_TIME_DEF;
	}	
	if(0 == u32InTime3){
		u32InTime3 = FLP3_IN_TIME_DEF;
	}					
	if((u32InSTime3 >= u32InSTime2)||(u32InSTime2 >= u32InSTime1)||(u32InSTime1 >= u32InSTime0))
	{
		u32InSTime0 = SB_IN_STIME_DEF;  
		u32InSTime1 = FLP1_IN_STIME_DEF;  
		u32InSTime2 = FLP2_IN_STIME_DEF;
		u32InSTime3 = FLP3_IN_STIME_DEF;						
	}
	if((u32InSTime3 + u32InTime3) < u32DlyTime)
	{
		u32DlyTime = FLP2_IN_STIME_DEF;    // TODO:根据实际情况更改
	}	
	
	/*支架整机参数初始化*/
	pstShdLkg->u32LStartTime = MS_TIMER;
	pstShdLkg->u32LDlySendTime = SECOND2MILLI(u32DlyTime);
	pstShdLkg->u32LStat = LKG_NULL; 
	pstShdLkg->u8LType = stRfhPkt.stPkt.u32CmdCode;
	pstShdLkg->pfLSendNext = LinkSendNextNull;
	pstShdLkg->pfLTimeCheck = mSecTimeCheck;	
	/*动作成员伸缩梁参数初始化*/
	pstShdLkg->stLComp[LKG_COMP_SB].u32ErrIndex = SLIDBAR_LMT_NOT_REACH;
	pstShdLkg->stLComp[LKG_COMP_SB].u32BaseTime = MS_TIMER;
	pstShdLkg->stLComp[LKG_COMP_SB].u32StartTime = SECOND2MILLI(u32InSTime0);
	pstShdLkg->stLComp[LKG_COMP_SB].u32ExtTime = SECOND2MILLI(u32InTime0);	
	pstShdLkg->stLComp[LKG_COMP_SB].u32Stat = LKG_NULL;
	pstShdLkg->stLComp[LKG_COMP_SB].u8Type = SLIDEBAR_IN_CMD;
	pstShdLkg->stLComp[LKG_COMP_SB].pfCompPCheck = Check1stFlipLmtP;
	pstShdLkg->stLComp[LKG_COMP_SB].pfCompTCheck = mSecTimeCheck;
	pstShdLkg->stLComp[LKG_COMP_SB].pfCompPCtrl = ShdLinkPrsCtrl;
	pstShdLkg->stLComp[LKG_COMP_SB].pfCompTCtrl = ShdLinkTimeCtrl;
	pstShdLkg->stLComp[LKG_COMP_SB].pfCompSCtrl = ShdLinkStartCtrl;	
	/*动作成员一级护帮参数初始化*/
	pstShdLkg->stLComp[LKG_COMP_FLIP1].u32ErrIndex = FLIP1_LMT_NOT_REACH;
	pstShdLkg->stLComp[LKG_COMP_FLIP1].u32BaseTime = MS_TIMER;
	pstShdLkg->stLComp[LKG_COMP_FLIP1].u32StartTime = SECOND2MILLI(u32InSTime1);
	pstShdLkg->stLComp[LKG_COMP_FLIP1].u32ExtTime = SECOND2MILLI(u32InTime1);	
	pstShdLkg->stLComp[LKG_COMP_FLIP1].u32Stat = LKG_NULL;
	pstShdLkg->stLComp[LKG_COMP_FLIP1].u8Type = FST_FLIP_IN_CMD;
	pstShdLkg->stLComp[LKG_COMP_FLIP1].pfCompPCheck = CheckSlidBarLmtP;
	pstShdLkg->stLComp[LKG_COMP_FLIP1].pfCompTCheck = mSecTimeCheck;
	pstShdLkg->stLComp[LKG_COMP_FLIP1].pfCompPCtrl = ShdLinkPrsCtrl;
	pstShdLkg->stLComp[LKG_COMP_FLIP1].pfCompTCtrl = ShdLinkTimeCtrl;
	pstShdLkg->stLComp[LKG_COMP_FLIP1].pfCompSCtrl = ShdLinkStartCtrl;	
	/*动作成员二级护帮参数初始化*/
	pstShdLkg->stLComp[LKG_COMP_FLIP2].u32ErrIndex = FLIP2_LMT_NOT_REACH; 
	pstShdLkg->stLComp[LKG_COMP_FLIP2].u32BaseTime = MS_TIMER;
	pstShdLkg->stLComp[LKG_COMP_FLIP2].u32StartTime = SECOND2MILLI(u32InSTime2);
	pstShdLkg->stLComp[LKG_COMP_FLIP2].u32ExtTime = SECOND2MILLI(u32InTime2);	
	pstShdLkg->stLComp[LKG_COMP_FLIP2].u32Stat = LKG_NULL; 
	pstShdLkg->stLComp[LKG_COMP_FLIP2].u8Type = SND_FLIP_IN_CMD;
	pstShdLkg->stLComp[LKG_COMP_FLIP2].pfCompPCheck = Check2ndFlipLmtP;
	pstShdLkg->stLComp[LKG_COMP_FLIP2].pfCompTCheck = mSecTimeCheck;
	pstShdLkg->stLComp[LKG_COMP_FLIP2].pfCompPCtrl = ShdLinkPrsCtrl;
	pstShdLkg->stLComp[LKG_COMP_FLIP2].pfCompTCtrl = ShdLinkTimeCtrl;
	pstShdLkg->stLComp[LKG_COMP_FLIP2].pfCompSCtrl = ShdLinkStartCtrl;
	/*动作成员三级护帮参数初始化*/
	pstShdLkg->stLComp[LKG_COMP_FLIP3].u32ErrIndex = FLIP3_LMT_NOT_REACH; 
	pstShdLkg->stLComp[LKG_COMP_FLIP3].u32BaseTime = MS_TIMER;
	pstShdLkg->stLComp[LKG_COMP_FLIP3].u32StartTime = SECOND2MILLI(u32InSTime3);
	pstShdLkg->stLComp[LKG_COMP_FLIP3].u32ExtTime = SECOND2MILLI(u32InTime3);	
	pstShdLkg->stLComp[LKG_COMP_FLIP3].u32Stat = LKG_NULL;	
	pstShdLkg->stLComp[LKG_COMP_FLIP3].u8Type = THD_FLIP_IN_CMD;
	pstShdLkg->stLComp[LKG_COMP_FLIP3].pfCompPCheck = Check3rdFlipLmtP;
	pstShdLkg->stLComp[LKG_COMP_FLIP3].pfCompTCheck = mSecTimeCheck;
	pstShdLkg->stLComp[LKG_COMP_FLIP3].pfCompPCtrl = ShdLinkPrsCtrl;
	pstShdLkg->stLComp[LKG_COMP_FLIP3].pfCompTCtrl = ShdLinkTimeCtrl;
	pstShdLkg->stLComp[LKG_COMP_FLIP3].pfCompSCtrl = ShdLinkStartCtrl;

	return;

}
/*********************************************************************************************************
** Function name:           RtnPerchLinkageInit
** Descriptions:            成组回高位联动参数初始化
** input parameters:        pstShdLkg  联动参数结构体
** output parameters:       none
** Returned value:          
** Created by:               gaocen
** Created Date:            2015-08-28
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
void RtnPerchLinkageInit(PKT_REFRESH_SCN_S stRfhPkt, SHILD_LINKAGE_S *pstShdLkg)
{
    INT32U u32DlyTime = GetBankRtnShldDly();	
    INT32U u32ExeSTime1 = 0;
	INT32U u32ExeTime1 = GetBankRtnTailUpT();
	INT32U u32ExeSTime2 = GetBankRtnShtOutST();
	INT32U u32ExeTime2 = GetBankRtnShtOutT();


	/*时间参数检查*/
	if(0 == u32ExeTime1){
		u32ExeTime1 = TAIL_UP_TIME_DEF;
	}
	if(0 == u32ExeTime2){
		u32ExeTime2 = SHT_OUT_TIME_DEF;
	}					
	if(u32ExeSTime2 == u32ExeSTime1)
	{
		u32ExeSTime2 = u32ExeSTime1+3;					
	}
	if((u32ExeSTime2 + u32ExeTime2) < u32DlyTime)
	{
		u32DlyTime = u32ExeSTime2;    // TODO:根据实际情况更改
	}
	
	/*支架整机参数初始化*/
	pstShdLkg->u32LStartTime = MS_TIMER;
	pstShdLkg->u32LDlySendTime = SECOND2MILLI(u32DlyTime);
	pstShdLkg->u32LStat = LKG_NULL; 
	pstShdLkg->u8LType = stRfhPkt.stPkt.u32CmdCode;
	pstShdLkg->pfLSendNext = LinkSendNextNull;
	pstShdLkg->pfLTimeCheck = mSecTimeCheck;	
	/*动作成员尾梁参数初始化*/
	pstShdLkg->stLComp[LKG_COMP_TLEVER].u32ErrIndex = TLEVER_LMT_NOT_REACH;
	pstShdLkg->stLComp[LKG_COMP_TLEVER].u32BaseTime = MS_TIMER;
	pstShdLkg->stLComp[LKG_COMP_TLEVER].u32StartTime = SECOND2MILLI(u32ExeSTime1);
	pstShdLkg->stLComp[LKG_COMP_TLEVER].u32ExtTime = SECOND2MILLI(u32ExeTime1);	
	pstShdLkg->stLComp[LKG_COMP_TLEVER].u32Stat = LKG_NULL;
	pstShdLkg->stLComp[LKG_COMP_TLEVER].u8Type = TAIL_OUT_CMD;
	pstShdLkg->stLComp[LKG_COMP_TLEVER].pfCompPCheck = CheckTailLeverLmtP;
	pstShdLkg->stLComp[LKG_COMP_TLEVER].pfCompTCheck = mSecTimeCheck;
	pstShdLkg->stLComp[LKG_COMP_TLEVER].pfCompPCtrl = ShdLinkPrsCtrl;
	pstShdLkg->stLComp[LKG_COMP_TLEVER].pfCompTCtrl = ShdLinkTimeCtrl;
	pstShdLkg->stLComp[LKG_COMP_TLEVER].pfCompSCtrl = ShdLinkStartCtrl;	
	/*动作成员插板参数初始化*/
	pstShdLkg->stLComp[LKG_COMP_SHUTTER].u32ErrIndex = SHUTTER_LMT_NOT_REACH;
	pstShdLkg->stLComp[LKG_COMP_SHUTTER].u32BaseTime = MS_TIMER;
	pstShdLkg->stLComp[LKG_COMP_SHUTTER].u32StartTime = SECOND2MILLI(u32ExeSTime2);
	pstShdLkg->stLComp[LKG_COMP_SHUTTER].u32ExtTime = SECOND2MILLI(u32ExeTime2);	
	pstShdLkg->stLComp[LKG_COMP_SHUTTER].u32Stat = LKG_NULL; 
	pstShdLkg->stLComp[LKG_COMP_SHUTTER].u8Type = SHUTTER_OUT_CMD;
	pstShdLkg->stLComp[LKG_COMP_SHUTTER].pfCompPCheck = CheckPlateLmtP;
	pstShdLkg->stLComp[LKG_COMP_SHUTTER].pfCompTCheck = mSecTimeCheck;
	pstShdLkg->stLComp[LKG_COMP_SHUTTER].pfCompPCtrl = ShdLinkPrsCtrl;
	pstShdLkg->stLComp[LKG_COMP_SHUTTER].pfCompTCtrl = ShdLinkTimeCtrl;
	pstShdLkg->stLComp[LKG_COMP_SHUTTER].pfCompSCtrl = ShdLinkStartCtrl;

	return;
}
/*********************************************************************************************************
** Function name:           BWashersLinkageInit
** Descriptions:            成组反冲洗联动参数初始化
** input parameters:        pstShdLkg  联动参数结构体
** output parameters:       none
** Returned value:          
** Created by:               gaocen
** Created Date:            2015-09-29
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
void BWashersLinkageInit(PKT_REFRESH_SCN_S stRfhPkt, SHILD_LINKAGE_S *pstShdLkg)
{
    INT32U u32DlyTime1 = GetBankBWashShdDly();	
	INT32U u32DlyTime2 = GetBankBWashUDIntv();
    INT32U u32ExeSTime1 = 0;
	INT32U u32ExeTime1 = GetBankBWashTime();
	INT32U u32ExeTime2 = GetBankBWashTime();
	INT32U u32ExeSTime2 = u32ExeSTime1+u32ExeTime1+u32DlyTime2;


	/*时间参数检查*/
    if((0 == u32ExeTime1) || (3 < u32ExeTime1))
    {
		u32ExeTime1 = 3;
	}
	if((0 == u32ExeTime2) || (3 < u32ExeTime2))
    {
		u32ExeTime2 = 3;
	}
	if(u32DlyTime1 > (u32ExeSTime2+u32ExeTime2))
	{
		u32DlyTime1 = u32ExeSTime2;    // TODO:根据实际情况更改
	}	 
	if(u32DlyTime2 < u32ExeSTime1+u32ExeTime1)
	{
		u32ExeSTime2 = u32ExeSTime1+u32ExeTime1+2;    // TODO:根据实际情况更改
	}
	/*支架整机参数初始化*/
	pstShdLkg->u32LStartTime = MS_TIMER;
	pstShdLkg->u32LDlySendTime = SECOND2MILLI(u32DlyTime1);
	pstShdLkg->u32LStat = LKG_NULL; 
	pstShdLkg->u8LType = stRfhPkt.stPkt.u32CmdCode;
	pstShdLkg->pfLSendNext = LinkSendNextNull;
	pstShdLkg->pfLTimeCheck = mSecTimeCheck;	
	/*动作成员过滤器1  参数初始化*/
	pstShdLkg->stLComp[LKG_COMP_BWASHER1].u32ErrIndex = VERSION_WRONG;  // TODO:反冲洗错误提示是什么
	pstShdLkg->stLComp[LKG_COMP_BWASHER1].u32BaseTime = MS_TIMER;
	pstShdLkg->stLComp[LKG_COMP_BWASHER1].u32StartTime = SECOND2MILLI(u32ExeSTime1);
	pstShdLkg->stLComp[LKG_COMP_BWASHER1].u32ExtTime = SECOND2MILLI(u32ExeTime1);	
	pstShdLkg->stLComp[LKG_COMP_BWASHER1].u32Stat = LKG_NULL;
	pstShdLkg->stLComp[LKG_COMP_BWASHER1].u8Type = BRASS_WASHERS1_CMD;
	pstShdLkg->stLComp[LKG_COMP_BWASHER1].pfCompTCheck = mSecTimeCheck;
	pstShdLkg->stLComp[LKG_COMP_BWASHER1].pfCompPCtrl = ShdLinkPrsCtrlNull;
	pstShdLkg->stLComp[LKG_COMP_BWASHER1].pfCompTCtrl = ShdLinkTimeCtrl;
	pstShdLkg->stLComp[LKG_COMP_BWASHER1].pfCompSCtrl = ShdLinkStartCtrl;
	/*动作成员过滤器2  参数初始化*/
	pstShdLkg->stLComp[LKG_COMP_BWASHER2].u32ErrIndex = VERSION_WRONG;  // TODO:反冲洗错误提示是什么
	pstShdLkg->stLComp[LKG_COMP_BWASHER2].u32BaseTime = MS_TIMER;
	pstShdLkg->stLComp[LKG_COMP_BWASHER2].u32StartTime = SECOND2MILLI(u32ExeSTime2);
	pstShdLkg->stLComp[LKG_COMP_BWASHER2].u32ExtTime = SECOND2MILLI(u32ExeTime2);
	pstShdLkg->stLComp[LKG_COMP_BWASHER2].u32Stat = LKG_NULL; 
	pstShdLkg->stLComp[LKG_COMP_BWASHER2].u8Type = BRASS_WASHERS2_CMD;
	pstShdLkg->stLComp[LKG_COMP_BWASHER2].pfCompTCheck = mSecTimeCheck;
	pstShdLkg->stLComp[LKG_COMP_BWASHER2].pfCompPCtrl = ShdLinkPrsCtrlNull;
	pstShdLkg->stLComp[LKG_COMP_BWASHER2].pfCompTCtrl = ShdLinkTimeCtrl;
	pstShdLkg->stLComp[LKG_COMP_BWASHER2].pfCompSCtrl = ShdLinkStartCtrl;

	return;
}

/*********************************************************************************************************
** Function name:           BankAutoFlpLinkageOut
** Descriptions:            成组护帮板联动伸
** input parameters:        stRefreshPkt 发送数据
** output parameters:       none
** Returned value:          
** Created by:              linguofeng 
** Created Date:            2015-04-13
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
void BankAutoFlpLinkageOut(PKT_REFRESH_SCN_S stRfhPkt)
{
	SCN_RFH_MSG_S stRfhMsg;
	SHILD_LINKAGE_S stShdLkg;

	 /* 发送动作执行命令到人机界面 */
    POST_INFO2SCN(stRfhMsg,BANK_CTRL_SCREEN, BANK_FLP_LINKAGE_EX_MSG,BANK_ACT_INFO);
	 /* 成组联动参数初始化 */
	FlipLinkageOutInit(stRfhPkt,&stShdLkg);
	
    while(1)
    {
        /* 架间延迟时间到 */
		stShdLkg.pfLSendNext(stRfhPkt, &stShdLkg);
		stShdLkg.stLComp[LKG_COMP_FLIP1].pfCompSCtrl(&stShdLkg.stLComp[LKG_COMP_FLIP1]);
		stShdLkg.stLComp[LKG_COMP_FLIP2].pfCompSCtrl(&stShdLkg.stLComp[LKG_COMP_FLIP2]);
		stShdLkg.stLComp[LKG_COMP_FLIP3].pfCompSCtrl(&stShdLkg.stLComp[LKG_COMP_FLIP3]);
		
		stShdLkg.u32LStat |= stShdLkg.stLComp[LKG_COMP_FLIP1].u32Stat | stShdLkg.stLComp[LKG_COMP_FLIP2].u32Stat | 
			                 stShdLkg.stLComp[LKG_COMP_FLIP3].u32Stat;
		
        if (LKG_FLIP_OVER == stShdLkg.u32LStat)
        {
            break;
        }
		RESPOND_TASK_DEL_REQ();
        OSTimeDly(TIME_DLY_10MS);
    }

	return;
}

/*********************************************************************************************************
** Function name:           BankAutoFlpLinkageIn
** Descriptions:            成组护帮板联动收
** input parameters:        stRefreshPkt 发送数据
** output parameters:       none
** Returned value:          
** Created by:              linguofeng 
** Created Date:            2015-04-13
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
void BankAutoFlpLinkageIn(PKT_REFRESH_SCN_S stRfhPkt)
{
	SCN_RFH_MSG_S stRfhMsg;
	SHILD_LINKAGE_S stShdLkg;

	 /* 发送动作执行命令到人机界面 */
    POST_INFO2SCN(stRfhMsg,BANK_CTRL_SCREEN, BANK_FLP_LINKAGE_IN_MSG,BANK_ACT_INFO);
	 /* 成组联动参数初始化 */
	FlipLinkageInInit(stRfhPkt,&stShdLkg);

    while(1)
    {
        /* 架间延迟时间到 */
		stShdLkg.pfLSendNext(stRfhPkt, &stShdLkg);
		stShdLkg.stLComp[LKG_COMP_FLIP1].pfCompSCtrl(&stShdLkg.stLComp[LKG_COMP_FLIP1]);
		stShdLkg.stLComp[LKG_COMP_FLIP2].pfCompSCtrl(&stShdLkg.stLComp[LKG_COMP_FLIP2]);
		stShdLkg.stLComp[LKG_COMP_FLIP3].pfCompSCtrl(&stShdLkg.stLComp[LKG_COMP_FLIP3]);
		
		stShdLkg.u32LStat |= stShdLkg.stLComp[LKG_COMP_FLIP1].u32Stat | stShdLkg.stLComp[LKG_COMP_FLIP2].u32Stat | 
			                 stShdLkg.stLComp[LKG_COMP_FLIP3].u32Stat;
		
        if (LKG_FLIP_OVER == stShdLkg.u32LStat)
        {
            break;
        }
		RESPOND_TASK_DEL_REQ();
        OSTimeDly(TIME_DLY_10MS);
    }
	
	return;
}

/*********************************************************************************************************
** Function name:           BankAutoSlidBarLinkageOut
** Descriptions:            成组伸缩梁联动伸
** input parameters:        stRefreshPkt 发送数据
** output parameters:       none
** Returned value:          
** Created by:              linguofeng 
** Created Date:            2015-04-13
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
void BankAutoSlidBarLinkageOut(PKT_REFRESH_SCN_S stRfhPkt)
{
	SCN_RFH_MSG_S stRfhMsg;
	SHILD_LINKAGE_S stShdLkg;

	 /* 发送动作执行命令到人机界面 */
    POST_INFO2SCN(stRfhMsg,BANK_CTRL_SCREEN, BANK_SB_LINKAGE_EX_MSG,BANK_ACT_INFO);
	 /* 成组联动参数初始化 */
	SBLinkageOutInit(stRfhPkt,&stShdLkg);
	
    while(1)
    {
        /* 架间延迟时间到 */
		stShdLkg.pfLSendNext(stRfhPkt, &stShdLkg);
		stShdLkg.stLComp[LKG_COMP_SB].pfCompSCtrl(&stShdLkg.stLComp[LKG_COMP_SB]);
		stShdLkg.stLComp[LKG_COMP_FLIP1].pfCompSCtrl(&stShdLkg.stLComp[LKG_COMP_FLIP1]);
		stShdLkg.stLComp[LKG_COMP_FLIP2].pfCompSCtrl(&stShdLkg.stLComp[LKG_COMP_FLIP2]);
		stShdLkg.stLComp[LKG_COMP_FLIP3].pfCompSCtrl(&stShdLkg.stLComp[LKG_COMP_FLIP3]);
		
		stShdLkg.u32LStat |= stShdLkg.stLComp[LKG_COMP_FLIP1].u32Stat | stShdLkg.stLComp[LKG_COMP_FLIP2].u32Stat | 
			                 stShdLkg.stLComp[LKG_COMP_FLIP3].u32Stat | stShdLkg.stLComp[LKG_COMP_SB].u32Stat;
		
        if (LKG_SB_OVER == stShdLkg.u32LStat)
        {
            break;
        }
		RESPOND_TASK_DEL_REQ();
        OSTimeDly(TIME_DLY_10MS);
    }

	return;

}


/*********************************************************************************************************
** Function name:           BankAutoSlidBarLinkageIn
** Descriptions:            成组伸缩梁联动收
** input parameters:        stRefreshPkt 发送数据
** output parameters:       none
** Returned value:          
** Created by:              linguofeng 
** Created Date:            2015-04-13
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
void BankAutoSlidBarLinkageIn(PKT_REFRESH_SCN_S stRfhPkt)
{
	SCN_RFH_MSG_S stRfhMsg;
	SHILD_LINKAGE_S stShdLkg;

	 /* 发送动作执行命令到人机界面 */
    POST_INFO2SCN(stRfhMsg,BANK_CTRL_SCREEN, BANK_SB_LINKAGE_IN_MSG,BANK_ACT_INFO);
	 /* 成组联动参数初始化 */
	SBLinkageInInit(stRfhPkt,&stShdLkg);
	
    while(1)
    {
        /* 架间延迟时间到 */
		stShdLkg.pfLSendNext(stRfhPkt, &stShdLkg);
		stShdLkg.stLComp[LKG_COMP_SB].pfCompSCtrl(&stShdLkg.stLComp[LKG_COMP_SB]);
		stShdLkg.stLComp[LKG_COMP_FLIP1].pfCompSCtrl(&stShdLkg.stLComp[LKG_COMP_FLIP1]);
		stShdLkg.stLComp[LKG_COMP_FLIP2].pfCompSCtrl(&stShdLkg.stLComp[LKG_COMP_FLIP2]);
		stShdLkg.stLComp[LKG_COMP_FLIP3].pfCompSCtrl(&stShdLkg.stLComp[LKG_COMP_FLIP3]);
		
		stShdLkg.u32LStat |= stShdLkg.stLComp[LKG_COMP_FLIP1].u32Stat | stShdLkg.stLComp[LKG_COMP_FLIP2].u32Stat | 
			                 stShdLkg.stLComp[LKG_COMP_FLIP3].u32Stat | stShdLkg.stLComp[LKG_COMP_SB].u32Stat;
		
        if (LKG_SB_OVER == stShdLkg.u32LStat)
        {
            break;
        }
		RESPOND_TASK_DEL_REQ();
        OSTimeDly(TIME_DLY_10MS);
    }

	return;

}


/*********************************************************************************************************
** Function name:           BankAutoSpray
** Descriptions:            成组喷雾
** input parameters:        stRefreshPkt 发送数据
** output parameters:       none
** Returned value:          
** Created by:              linguofeng 
** Created Date:            2015-04-13
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
void BankAutoSpray(PKT_REFRESH_SCN_S stRfhPkt)
{
	SCN_RFH_MSG_S stRfhMsg;
    INT32U u32Valve = 0;
    INT32U u32DlyTime = 0;	// TODO:喷雾菜单页无此参数
    INT32U u32SprayTime = GetBankSprayTime();
    SHILD_COMPONENT_S stComp;

    /* 动作参数检查 */    
    if((0 == u32SprayTime) || (u32SprayTime > SPRAY_ACT_TIME_DFT))
    {
		u32SprayTime = SPRAY_ACT_TIME_DFT;
	}	
    /* 发送动作执行命令到人机界面 */
    POST_INFO2SCN(stRfhMsg,BANK_CTRL_SCREEN, BANK_SPRAY_MSG,BANK_ACT_INFO);

    VALVE_TBL(u32Valve,SHIELD_POS,SPRAY_CMD);
    SET_VALVE(u32Valve);
	
    stComp.u32ErrIndex = ERR_MSG_NULL;	// TODO:喷雾错误提示应该是什么
    stComp.u32StartTime = MS_TIMER;
    stComp.u32ShdExtTime = SECOND2MILLI(u32SprayTime);
    stComp.u32DlySendNext = SECOND2MILLI(u32DlyTime);
    stComp.pfSendNext = SendNextNull;
    stComp.pfShdPCtrl = ShdPressureCtrl;
    stComp.pfShdTCtrl = ShdTimeCtrl;
    stComp.pfTimeCheck = mSecTimeCheck;
    stComp.pfPCheck = CheckSprayWaterP;
    stComp.u32Stat = SHD_COMP_NULL;
	stComp.u8Type = SPRAY_CMD;
	
    while(1)
    {
        /* 架间延迟时间到 */
        stComp.pfSendNext(stRfhPkt,&stComp);
        //stComp.pfShdPCtrl(&stComp);
        stComp.pfShdTCtrl(&stComp);
		
        if (stComp.u32Stat == SHD_COMP_OVER)
        {
            break;
        }
		RESPOND_TASK_DEL_REQ();
        OSTimeDly(TIME_DLY_10MS);
    }

}


/*********************************************************************************************************
** Function name:           BankAutoBSpray
** Descriptions:            成组放煤喷雾
** input parameters:        stRefreshPkt 发送数据
** output parameters:       none
** Returned value:          
** Created by:              linguofeng 
** Created Date:            2015-04-13
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
void BankAutoBSpray(PKT_REFRESH_SCN_S stRfhPkt)
{
	// TODO:成组放煤喷雾菜单在哪里
	SCN_RFH_MSG_S stRfhMsg;
    INT32U u32Valve = 0;
    INT32U u32DlyTime = 0;
    INT32U u32SprayTime = GetBankSprayTime();
    SHILD_COMPONENT_S stComp;

    /* 动作参数检查 */    
    if((0 == u32SprayTime) || (u32SprayTime > BSPRAY_ACT_TIME_DFT))
    {
		u32SprayTime = BSPRAY_ACT_TIME_DFT;
	}	
    /* 发送动作执行命令到人机界面 */
    POST_INFO2SCN(stRfhMsg,BANK_CTRL_SCREEN, BANK_BSPRAY_MSG,BANK_ACT_INFO);

    VALVE_TBL(u32Valve,SHIELD_POS,SPRAY_CMD);	// TODO:放煤喷雾对应阀在哪里
    SET_VALVE(u32Valve);
	
    stComp.u32ErrIndex = ERR_MSG_NULL;	// TODO:放煤喷雾错误提示应该是什么   
    stComp.u32StartTime = MS_TIMER;
    stComp.u32ShdExtTime = SECOND2MILLI(u32SprayTime);
    stComp.u32DlySendNext = SECOND2MILLI(u32DlyTime);
    stComp.pfSendNext = SendNextNull;
    stComp.pfShdPCtrl = ShdPressureCtrl;
    stComp.pfShdTCtrl = ShdTimeCtrl;
    stComp.pfTimeCheck = mSecTimeCheck;
    stComp.pfPCheck = CheckSprayWaterP;
    stComp.u32Stat = SHD_COMP_NULL;
	stComp.u8Type = SPRAY_CMD;
	
    while(1)
    {
        /* 架间延迟时间到 */
        stComp.pfSendNext(stRfhPkt,&stComp);
        //stComp.pfShdPCtrl(&stComp);
        stComp.pfShdTCtrl(&stComp);
		
        if (stComp.u32Stat == SHD_COMP_OVER)
        {
            break;
        }
		RESPOND_TASK_DEL_REQ();
        OSTimeDly(TIME_DLY_10MS);
    }

}


/*********************************************************************************************************
** Function name:           BankAutoESpray
** Descriptions:            成组顶梁喷雾
** input parameters:        stRefreshPkt 发送数据
** output parameters:       none
** Returned value:          
** Created by:              linguofeng 
** Created Date:            2015-04-13
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
void BankAutoESpray(PKT_REFRESH_SCN_S stRfhPkt)
{
	// TODO:成组顶梁喷雾菜单在哪里
	SCN_RFH_MSG_S stRfhMsg;
    INT32U u32Valve = 0;
    INT32U u32DlyTime = 0;	
    INT32U u32SprayTime = GetBankSprayTime();
    SHILD_COMPONENT_S stComp;

    /* 动作参数检查 */    
    if((0 == u32SprayTime) || (u32SprayTime > ESPRAY_ACT_TIME_DFT))
    {
		u32SprayTime = ESPRAY_ACT_TIME_DFT;
	}	
    /* 发送动作执行命令到人机界面 */
    POST_INFO2SCN(stRfhMsg,BANK_CTRL_SCREEN, BANK_ESPRAY_MSG,BANK_ACT_INFO);

    VALVE_TBL(u32Valve,SHIELD_POS,SPRAY_CMD);	// TODO:顶梁喷雾对应阀在哪里
    SET_VALVE(u32Valve);
	
    stComp.u32ErrIndex = ERR_MSG_NULL;	// TODO:顶梁喷雾错误提示应该是什么
    stComp.u32StartTime = MS_TIMER;
    stComp.u32ShdExtTime = SECOND2MILLI(u32SprayTime);
    stComp.u32DlySendNext = SECOND2MILLI(u32DlyTime);
    stComp.pfSendNext = SendNextNull;
    stComp.pfShdPCtrl = ShdPressureCtrl;
    stComp.pfShdTCtrl = ShdTimeCtrl;
    stComp.pfTimeCheck = mSecTimeCheck;
    stComp.pfPCheck = CheckSprayWaterP;
    stComp.u32Stat = SHD_COMP_NULL;
	stComp.u8Type = SPRAY_CMD;
	
    while(1)
    {
        /* 架间延迟时间到 */
        stComp.pfSendNext(stRfhPkt,&stComp);
        //stComp.pfShdPCtrl(&stComp);
        stComp.pfShdTCtrl(&stComp);
		
        if (stComp.u32Stat == SHD_COMP_OVER)
        {
            break;
        }
		RESPOND_TASK_DEL_REQ();
        OSTimeDly(TIME_DLY_10MS);
    }

}


/*********************************************************************************************************
** Function name:           BankAutoASpray
** Descriptions:            成组机道喷雾
** input parameters:        stRefreshPkt 发送数据
** output parameters:       none
** Returned value:          
** Created by:              linguofeng 
** Created Date:            2015-04-13
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
void BankAutoASpray(PKT_REFRESH_SCN_S stRfhPkt)
{
	// TODO:成组机道喷雾菜单在哪里
	SCN_RFH_MSG_S stRfhMsg;
    INT32U u32Valve = 0;
    INT32U u32DlyTime = 0;	
    INT32U u32SprayTime = GetBankSprayTime();
    SHILD_COMPONENT_S stComp;

    /* 动作参数检查 */    
    if((0 == u32SprayTime) || (u32SprayTime > ASPRAY_ACT_TIME_DFT))
    {
		u32SprayTime = ASPRAY_ACT_TIME_DFT;
	}	
    /* 发送动作执行命令到人机界面 */
    POST_INFO2SCN(stRfhMsg,BANK_CTRL_SCREEN, BANK_ASPRAY_MSG,BANK_ACT_INFO);

    VALVE_TBL(u32Valve,SHIELD_POS,SPRAY_CMD);	// TODO:机道喷雾对应阀在哪里
    SET_VALVE(u32Valve);
	
    stComp.u32ErrIndex = ERR_MSG_NULL;	// TODO:机道喷雾错误提示应该是什么    
    stComp.u32StartTime = MS_TIMER;
    stComp.u32ShdExtTime = SECOND2MILLI(u32SprayTime);
    stComp.u32DlySendNext = SECOND2MILLI(u32DlyTime);
    stComp.pfSendNext = SendNextNull;
    stComp.pfShdPCtrl = ShdPressureCtrl;
    stComp.pfShdTCtrl = ShdTimeCtrl;
    stComp.pfTimeCheck = mSecTimeCheck;
    stComp.pfPCheck = CheckSprayWaterP;
    stComp.u32Stat = SHD_COMP_NULL;
	stComp.u8Type = SPRAY_CMD;
	
    while(1)
    {
        /* 架间延迟时间到 */
        stComp.pfSendNext(stRfhPkt,&stComp);
        //stComp.pfShdPCtrl(&stComp);
        stComp.pfShdTCtrl(&stComp);
		
        if (stComp.u32Stat == SHD_COMP_OVER)
        {
            break;
        }
		RESPOND_TASK_DEL_REQ();
        OSTimeDly(TIME_DLY_10MS);
    }

}


/*********************************************************************************************************
** Function name:           BankAuto3rdFlipOut
** Descriptions:            成组3级护帮伸
** input parameters:        stRefreshPkt 发送数据
** output parameters:       none
** Returned value:          
** Created by:              linguofeng 
** Created Date:            2015-04-13
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
void BankAuto3rdFlipOut(PKT_REFRESH_SCN_S stRfhPkt)
{
    SCN_RFH_MSG_S stRfhMsg;
    INT32U u32Valve = 0;
    INT32U u32DlyTime = GetBankFlpFSdly();
    INT32U u32ExTime = GetASQ3rdFlipExT();
    SHILD_COMPONENT_S stComp;

    /* 动作参数检查 */    
    BANK_CTRL_TPARA_CHECK(u32ExTime,u32DlyTime,FLIP_ACT_TIME_DFT,FLIP_FS_DLY_DFT);    
    /* 发送动作执行命令到人机界面 */
	POST_INFO2SCN(stRfhMsg,BANK_CTRL_SCREEN, BANK_FLP_3RD_EX_MSG,BANK_ACT_INFO);

    VALVE_TBL(u32Valve,SHIELD_POS,THD_FLIP_OUT_CMD);
    SET_VALVE(u32Valve);
	
    stComp.u32ErrIndex = FLIP3_LMT_NOT_REACH;    
    stComp.u32StartTime = MS_TIMER;
    stComp.u32ShdExtTime = SECOND2MILLI(u32ExTime);
    stComp.u32DlySendNext = SECOND2MILLI(u32DlyTime);
    stComp.pfSendNext = SendNextNull;
    stComp.pfShdPCtrl = ShdPressureCtrl;
    stComp.pfShdTCtrl = ShdTimeCtrl;
    stComp.pfTimeCheck = mSecTimeCheck;
    stComp.pfPCheck = Check3rdFlipLmtP;
    stComp.u32Stat = SHD_COMP_NULL;
	stComp.u8Type = THD_FLIP_OUT_CMD;
	
    while(1)
    {
        /* 架间延迟时间到 */
        stComp.pfSendNext(stRfhPkt,&stComp);
        stComp.pfShdPCtrl(&stComp);
        stComp.pfShdTCtrl(&stComp);
    
        if (stComp.u32Stat == SHD_COMP_OVER)
        {
            break;
        }
		RESPOND_TASK_DEL_REQ();
        OSTimeDly(TIME_DLY_10MS);
    }
  
}
/*********************************************************************************************************
** Function name:           BankAuto3rdFlipIn
** Descriptions:            成组3级护帮收
** input parameters:        stRefreshPkt 发送数据
** output parameters:       none
** Returned value:          
** Created by:              linguofeng 
** Created Date:            2015-04-13
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
void BankAuto3rdFlipIn(PKT_REFRESH_SCN_S stRfhPkt)
{
    SCN_RFH_MSG_S stRfhMsg;
    INT32U u32Valve = 0;
    INT32U u32DlyTime = GetBankFlpFSdly();	
    INT32U u32InTime = GetASQ3rdFlipInT();	
    SHILD_COMPONENT_S stComp;

    /* 动作参数检查 */    
    BANK_CTRL_TPARA_CHECK(u32InTime,u32DlyTime,FLIP_ACT_TIME_DFT,FLIP_FS_DLY_DFT);    
    /* 发送动作执行命令到人机界面 */
	POST_INFO2SCN(stRfhMsg,BANK_CTRL_SCREEN, BANK_FLP_3RD_IN_MSG,BANK_ACT_INFO);

    VALVE_TBL(u32Valve,SHIELD_POS,THD_FLIP_IN_CMD);
    SET_VALVE(u32Valve);
	
    stComp.u32ErrIndex = FLIP3_LMT_NOT_REACH;    
    stComp.u32StartTime = MS_TIMER;
    stComp.u32ShdExtTime = SECOND2MILLI(u32InTime);
    stComp.u32DlySendNext = SECOND2MILLI(u32DlyTime);
    stComp.pfSendNext = SendNextNull;
    stComp.pfShdPCtrl = ShdPressureCtrl;
    stComp.pfShdTCtrl = ShdTimeCtrl;
    stComp.pfTimeCheck = mSecTimeCheck;
    stComp.pfPCheck = Check3rdFlipLmtP;
    stComp.u32Stat = SHD_COMP_NULL;
	stComp.u8Type = THD_FLIP_IN_CMD;
	
    while(1)
    {
        /* 架间延迟时间到 */
        stComp.pfSendNext(stRfhPkt,&stComp);
        stComp.pfShdPCtrl(&stComp);
        stComp.pfShdTCtrl(&stComp);
    
        if (stComp.u32Stat == SHD_COMP_OVER)
        {
            break;
        }
		RESPOND_TASK_DEL_REQ();
        OSTimeDly(TIME_DLY_10MS);
    }

}



/*********************************************************************************************************
** Function name:           BankAutoBWashers
** Descriptions:            成组反冲洗
** input parameters:        stRefreshPkt 发送数据
** output parameters:       none
** Returned value:          
** Created by:              linguofeng 
** Created Date:            2015-04-13
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
void BankAutoBWashers(PKT_REFRESH_SCN_S stRfhPkt)
{
	SCN_RFH_MSG_S stRfhMsg;
	SHILD_LINKAGE_S stShdLkg;

	/* 发送动作执行命令到人机界面 */
	POST_INFO2SCN(stRfhMsg,BANK_CTRL_SCREEN, BANK_WASHERS_MSG,BANK_ACT_INFO);
	/* 成组反冲洗参数初始化 */
	BWashersLinkageInit(stRfhPkt,&stShdLkg);
	
    while(1)
    {
        /* 架间延迟时间到 */
		stShdLkg.pfLSendNext(stRfhPkt, &stShdLkg);
		stShdLkg.stLComp[LKG_COMP_BWASHER1].pfCompSCtrl(&stShdLkg.stLComp[LKG_COMP_BWASHER1]);
		stShdLkg.stLComp[LKG_COMP_BWASHER2].pfCompSCtrl(&stShdLkg.stLComp[LKG_COMP_BWASHER2]);
		
		stShdLkg.u32LStat |= stShdLkg.stLComp[LKG_COMP_BWASHER1].u32Stat | stShdLkg.stLComp[LKG_COMP_BWASHER2].u32Stat;
		
        if (LKG_BWASHER_OVER == stShdLkg.u32LStat)
        {
            break;
        }
		RESPOND_TASK_DEL_REQ();
        OSTimeDly(TIME_DLY_10MS);
    }		
}
/*********************************************************************************************************
** Function name:           ExpendToBottom
** Descriptions:            放顶煤第一阶段:收插板、降尾梁
** input parameters:       pstShdLkg
** output parameters:       none
** Returned value:          
** Created by:              gaocen 
** Created Date:            2015-09-10
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
static void ExpendToBottom(PKT_REFRESH_SCN_S *pstRfhPkt,SHILD_LINKAGE_S *pstShdLkg)
{
	INT32U u32ShtInSTime = IMMEDI_START_TIME; 
	INT32U u32ShtInTime = GetBankEpdShtInT();    	
	INT32U u32TailDownSTime = GetBankEpdTailDownST();	
	INT32U u32TailDownTime = GetBankEpdTailDownT();	

	/*时间参数检查*/
	if(u32ShtInTime < SHT_IN_TIME_DEF){
		u32ShtInTime = SHT_IN_TIME_DEF;
	}
	if(u32TailDownTime < TAIL_DOWN_TIME_DEF){
		u32TailDownTime = TAIL_DOWN_TIME_DEF;
	}	
	if(u32TailDownSTime < u32ShtInTime)  //务必要保证插板完全收回再进行收尾梁动作，以免将插板别在后溜上造成相应结构损伤
	{
		u32TailDownSTime = u32ShtInTime;					
	}
	
	pstShdLkg->stLComp[LKG_COMP_TLEVER].u32ErrIndex = TLEVER_LMT_NOT_REACH;
	pstShdLkg->stLComp[LKG_COMP_TLEVER].u32BaseTime = MS_TIMER;
	pstShdLkg->stLComp[LKG_COMP_TLEVER].u32StartTime = SECOND2MILLI(u32TailDownSTime);
	pstShdLkg->stLComp[LKG_COMP_TLEVER].u32ExtTime = SECOND2MILLI(u32TailDownTime);	
	pstShdLkg->stLComp[LKG_COMP_TLEVER].u32Stat = LKG_NULL;
	pstShdLkg->stLComp[LKG_COMP_TLEVER].u8Type = TAIL_IN_CMD;    
	//pstShdLkg->stLComp[LKG_COMP_TLEVER].u8Type = LOWE_REAR_LEG_CMD;	// TODO:尾梁阀在哪里  暂代
	pstShdLkg->stLComp[LKG_COMP_TLEVER].pfCompPCheck = CheckTailLeverLmtP;
	pstShdLkg->stLComp[LKG_COMP_TLEVER].pfCompTCheck = mSecTimeCheck;
	pstShdLkg->stLComp[LKG_COMP_TLEVER].pfCompPCtrl = ShdLinkPrsCtrl;
	pstShdLkg->stLComp[LKG_COMP_TLEVER].pfCompTCtrl = ShdLinkTimeCtrl;
	pstShdLkg->stLComp[LKG_COMP_TLEVER].pfCompSCtrl = ShdLinkStartCtrl;	
	
	pstShdLkg->stLComp[LKG_COMP_SHUTTER].u32ErrIndex = SHUTTER_LMT_NOT_REACH;
	pstShdLkg->stLComp[LKG_COMP_SHUTTER].u32BaseTime = MS_TIMER;
	pstShdLkg->stLComp[LKG_COMP_SHUTTER].u32StartTime = SECOND2MILLI(u32ShtInSTime);
	pstShdLkg->stLComp[LKG_COMP_SHUTTER].u32ExtTime = SECOND2MILLI(u32ShtInTime);	
	pstShdLkg->stLComp[LKG_COMP_SHUTTER].u32Stat = LKG_NULL; 
	pstShdLkg->stLComp[LKG_COMP_SHUTTER].u8Type = SHUTTER_IN_CMD;
	//pstShdLkg->stLComp[LKG_COMP_SHUTTER].u8Type = SIDESEAL_IN_CMD;	// TODO:插板阀在哪里  暂代
	pstShdLkg->stLComp[LKG_COMP_SHUTTER].pfCompPCheck = CheckPlateLmtP;
	pstShdLkg->stLComp[LKG_COMP_SHUTTER].pfCompTCheck = mSecTimeCheck;
	pstShdLkg->stLComp[LKG_COMP_SHUTTER].pfCompPCtrl = ShdLinkPrsCtrl;
	pstShdLkg->stLComp[LKG_COMP_SHUTTER].pfCompTCtrl = ShdLinkTimeCtrl;
	pstShdLkg->stLComp[LKG_COMP_SHUTTER].pfCompSCtrl = ShdLinkStartCtrl;

	while(1)
	{	
		/* 架间延迟发送 */
        pstShdLkg->pfLSendNext(*pstRfhPkt,pstShdLkg);
		/* 降尾梁控制 */
		pstShdLkg->stLComp[LKG_COMP_TLEVER].pfCompSCtrl(&pstShdLkg->stLComp[LKG_COMP_TLEVER]);
		/* 收插板控制 */
		pstShdLkg->stLComp[LKG_COMP_SHUTTER].pfCompSCtrl(&pstShdLkg->stLComp[LKG_COMP_SHUTTER]);
						
		if (LKG_TLEVER_OVER == pstShdLkg->stLComp[LKG_COMP_TLEVER].u32Stat &&
			LKG_SHUTTER_OVER == pstShdLkg->stLComp[LKG_COMP_SHUTTER].u32Stat )
		{
			break;
		}
		OSTimeDly(TIME_DLY_10MS);
	}

}
/*********************************************************************************************************
** Function name:           ExpendToTop
** Descriptions:            放顶煤第二阶段:升尾梁、伸插板
** input parameters:        pstShdLkg 
** output parameters:       none
** Returned value:          
** Created by:              gaocen 
** Created Date:            2015-09-10
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
static void ExpendToTop(PKT_REFRESH_SCN_S *pstRfhPkt,SHILD_LINKAGE_S *pstShdLkg)
{
	INT32U u32TailUpSTime = IMMEDI_START_TIME;	
	INT32U u32TailUpTime = GetBankEpdTailUpT();		
	INT32U u32ShtOutSTime = GetBankEpdShtOutST();	
	INT32U u32ShtOutTime = GetBankEpdShtOutT();		

	/*时间参数检查*/
	if(u32TailUpTime < TAIL_UP_TIME_DEF){
		u32TailUpTime = TAIL_UP_TIME_DEF;
	}
	if(u32ShtOutTime < SHT_OUT_TIME_DEF){
		u32ShtOutTime = SHT_OUT_TIME_DEF;
	}
	if(u32ShtOutSTime < u32TailUpTime)  //以尾梁升为起始时间
	{
		u32ShtOutSTime = u32TailUpTime;					
	}

	pstShdLkg->u32LStat = LKG_NULL;
	pstShdLkg->stLComp[LKG_COMP_TLEVER].u32ErrIndex = TLEVER_LMT_NOT_REACH;
	pstShdLkg->stLComp[LKG_COMP_TLEVER].u32BaseTime = MS_TIMER;
	pstShdLkg->stLComp[LKG_COMP_TLEVER].u32StartTime = SECOND2MILLI(u32TailUpSTime);
	pstShdLkg->stLComp[LKG_COMP_TLEVER].u32ExtTime = SECOND2MILLI(u32TailUpTime);	
	pstShdLkg->stLComp[LKG_COMP_TLEVER].u32Stat = LKG_NULL;
	pstShdLkg->stLComp[LKG_COMP_TLEVER].u8Type = TAIL_OUT_CMD;
	//pstShdLkg->stLComp[LKG_COMP_TLEVER].u8Type = SET_REAR_LEG_CMD;	// TODO:尾梁阀在哪里  暂代
	pstShdLkg->stLComp[LKG_COMP_TLEVER].pfCompPCheck = CheckTailLeverLmtP;
	pstShdLkg->stLComp[LKG_COMP_TLEVER].pfCompTCheck = mSecTimeCheck;
	pstShdLkg->stLComp[LKG_COMP_TLEVER].pfCompPCtrl = ShdLinkPrsCtrl;
	pstShdLkg->stLComp[LKG_COMP_TLEVER].pfCompTCtrl = ShdLinkTimeCtrl;
	pstShdLkg->stLComp[LKG_COMP_TLEVER].pfCompSCtrl = ShdLinkStartCtrl;	
	
	pstShdLkg->stLComp[LKG_COMP_SHUTTER].u32ErrIndex = SHUTTER_LMT_NOT_REACH;
	pstShdLkg->stLComp[LKG_COMP_SHUTTER].u32BaseTime = MS_TIMER;
	pstShdLkg->stLComp[LKG_COMP_SHUTTER].u32StartTime = SECOND2MILLI(u32ShtOutSTime);
	pstShdLkg->stLComp[LKG_COMP_SHUTTER].u32ExtTime = SECOND2MILLI(u32ShtOutTime);	
	pstShdLkg->stLComp[LKG_COMP_SHUTTER].u32Stat = LKG_NULL; 
	pstShdLkg->stLComp[LKG_COMP_SHUTTER].u8Type = SHUTTER_OUT_CMD;
	//pstShdLkg->stLComp[LKG_COMP_SHUTTER].u8Type = SIDESEAL_OUT_CMD;	// TODO:插板阀在哪里  暂代	
	pstShdLkg->stLComp[LKG_COMP_SHUTTER].pfCompPCheck = CheckPlateLmtP;
	pstShdLkg->stLComp[LKG_COMP_SHUTTER].pfCompTCheck = mSecTimeCheck;
	pstShdLkg->stLComp[LKG_COMP_SHUTTER].pfCompPCtrl = ShdLinkPrsCtrl;
	pstShdLkg->stLComp[LKG_COMP_SHUTTER].pfCompTCtrl = ShdLinkTimeCtrl;
	pstShdLkg->stLComp[LKG_COMP_SHUTTER].pfCompSCtrl = ShdLinkStartCtrl;

	while(1)
	{	
		/* 架间延迟发送 */
        pstShdLkg->pfLSendNext(*pstRfhPkt,pstShdLkg);
		/* 升尾梁控制 */
		pstShdLkg->stLComp[LKG_COMP_TLEVER].pfCompSCtrl(&pstShdLkg->stLComp[LKG_COMP_TLEVER]);
		/* 伸插板控制 */
		pstShdLkg->stLComp[LKG_COMP_SHUTTER].pfCompSCtrl(&pstShdLkg->stLComp[LKG_COMP_SHUTTER]);
						
		if (LKG_TLEVER_OVER == pstShdLkg->stLComp[LKG_COMP_TLEVER].u32Stat &&
			LKG_SHUTTER_OVER == pstShdLkg->stLComp[LKG_COMP_SHUTTER].u32Stat )
		{
			break;
		}

		OSTimeDly(TIME_DLY_10MS);
	}

}
/*********************************************************************************************************
** Function name:           TailUpShake
** Descriptions:            尾梁向上抖
** input parameters:        pstShdLkg 
** output parameters:       none
** Returned value:          
** Created by:              gaocen 
** Created Date:            2015-09-10
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
static void TailUpShake(PKT_REFRESH_SCN_S *pstRfhPkt,SHILD_LINKAGE_S *pstShdLkg)
{ 	
	INT32U u32TailUpSTime = IMMEDI_START_TIME;
	INT32U u32ShakeTime = GetBankEpdShakeT();	

	
	if((u32ShakeTime < SHAKE_TIME_MIN_DEF) || (u32ShakeTime > SHAKE_TIME_MAX_DEF))
	{
		u32ShakeTime = SHAKE_TIME_DEF;
	}

	pstShdLkg->u32LStat = LKG_NULL;
	pstShdLkg->stLComp[LKG_COMP_TLEVER].u32ErrIndex = TLEVER_LMT_NOT_REACH;
	pstShdLkg->stLComp[LKG_COMP_TLEVER].u32BaseTime = MS_TIMER;
	pstShdLkg->stLComp[LKG_COMP_TLEVER].u32StartTime = SECOND2MILLI(u32TailUpSTime);
	pstShdLkg->stLComp[LKG_COMP_TLEVER].u32ExtTime = u32ShakeTime;	//本身单位即毫秒，不转换	
	pstShdLkg->stLComp[LKG_COMP_TLEVER].u32Stat = LKG_NULL;
	pstShdLkg->stLComp[LKG_COMP_TLEVER].u8Type = TAIL_OUT_CMD;
	//pstShdLkg->stLComp[LKG_COMP_TLEVER].u8Type = SET_REAR_LEG_CMD;	// TODO:尾梁阀在哪里  暂代	
	pstShdLkg->stLComp[LKG_COMP_TLEVER].pfCompTCheck = mSecTimeCheck;
	pstShdLkg->stLComp[LKG_COMP_TLEVER].pfCompPCtrl = ShdLinkPrsCtrlNull;
	pstShdLkg->stLComp[LKG_COMP_TLEVER].pfCompTCtrl = ShdLinkTimeCtrl;
	pstShdLkg->stLComp[LKG_COMP_TLEVER].pfCompSCtrl = ShdLinkStartCtrl;	
	
	while(1)
	{
		/* 架间延迟发送 */
        pstShdLkg->pfLSendNext(*pstRfhPkt,pstShdLkg);
		/* 尾梁升 */
		pstShdLkg->stLComp[LKG_COMP_TLEVER].pfCompSCtrl(&pstShdLkg->stLComp[LKG_COMP_TLEVER]);
			
		if(LKG_TLEVER_OVER == pstShdLkg->stLComp[LKG_COMP_TLEVER].u32Stat)
		{
			break;
		}
		OSTimeDly(TIME_DLY_10MS);
	}

}
/*********************************************************************************************************
** Function name:           EpdTopShake
** Descriptions:            放顶煤高位抖动
** input parameters:        pstShdLkg 
** output parameters:       none
** Returned value:          
** Created by:              gaocen 
** Created Date:            2015-09-10
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
static void TailDownShake(PKT_REFRESH_SCN_S *pstRfhPkt,SHILD_LINKAGE_S *pstShdLkg)
{ 
	INT32U u32TailDownSTime = IMMEDI_START_TIME;
	INT32U u32ShakeTime = GetBankEpdShakeT();	
	

	if((u32ShakeTime < SHAKE_TIME_MIN_DEF) || (u32ShakeTime > SHAKE_TIME_MAX_DEF))
	{
		u32ShakeTime = SHAKE_TIME_DEF;
	}

	
	pstShdLkg->stLComp[LKG_COMP_TLEVER].u32ErrIndex = TLEVER_LMT_NOT_REACH;
	pstShdLkg->stLComp[LKG_COMP_TLEVER].u32BaseTime = MS_TIMER;
	pstShdLkg->stLComp[LKG_COMP_TLEVER].u32StartTime = SECOND2MILLI(u32TailDownSTime);
	pstShdLkg->stLComp[LKG_COMP_TLEVER].u32ExtTime = u32ShakeTime;	//本身单位即毫秒，不转换
	pstShdLkg->stLComp[LKG_COMP_TLEVER].u32Stat = LKG_NULL;
	pstShdLkg->stLComp[LKG_COMP_TLEVER].u8Type = TAIL_IN_CMD;
	//pstShdLkg->stLComp[LKG_COMP_TLEVER].u8Type = LOWE_REAR_LEG_CMD;	// TODO:尾梁阀在哪里  暂代
	pstShdLkg->stLComp[LKG_COMP_TLEVER].pfCompTCheck = mSecTimeCheck;
	pstShdLkg->stLComp[LKG_COMP_TLEVER].pfCompPCtrl = ShdLinkPrsCtrlNull;
	pstShdLkg->stLComp[LKG_COMP_TLEVER].pfCompTCtrl = ShdLinkTimeCtrl;
	pstShdLkg->stLComp[LKG_COMP_TLEVER].pfCompSCtrl = ShdLinkStartCtrl;	
	
	while(1)
	{
		/* 架间延迟发送 */
        pstShdLkg->pfLSendNext(*pstRfhPkt,pstShdLkg);
		/* 尾梁降 */
		pstShdLkg->stLComp[LKG_COMP_TLEVER].pfCompSCtrl(&pstShdLkg->stLComp[LKG_COMP_TLEVER]);
			
		if(LKG_TLEVER_OVER == pstShdLkg->stLComp[LKG_COMP_TLEVER].u32Stat)
		{
			break;
		}
		OSTimeDly(TIME_DLY_10MS);
	}

}

/*********************************************************************************************************
** Function name:           BankAutoExpend
** Descriptions:            成组放顶煤
** input parameters:        stRefreshPkt 发送数据
** output parameters:       none
** Returned value:          
** Created by:              linguofeng 
** Created Date:            2015-04-13
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
void BankAutoExpend(PKT_REFRESH_SCN_S stRfhPkt)
{
    SCN_RFH_MSG_S stRfhMsg;
    INT32U u32Valve = 0;
    INT32U u32DlyTime = GetBankEpdShdDly();	
	INT32U u32CycleNum = GetBankEpdCycleNum(); 
	INT32U u32BtmShkNum,u32TopShkNum,u32ShakeNum = GetBankEpdShakeNum();
	INT32U u32BtmWaitTime = GetBankEpdDownWaitT();	
	INT32U u32TopWaitTime = GetBankEpdUpWaitT();	
    SHILD_LINKAGE_S stShdLkg;


    /* 参数合理性检查 */    
    if(u32CycleNum < CYCLE_NUM_DEF){
		u32CycleNum = CYCLE_NUM_DEF;
	}	
	if(u32ShakeNum < SHAKE_NUM_DEF){
		u32ShakeNum = SHAKE_NUM_DEF;
	}
	if(u32DlyTime < EPD_SHD_DLY_DEF){	// TODO:延时发送合理范围
		u32DlyTime = EPD_SHD_DLY_DEF;
	}
	if(u32BtmWaitTime < BOTTOM_WAIT_DEF){
		u32BtmWaitTime = BOTTOM_WAIT_DEF;
	}
	if(u32TopWaitTime < TOP_WAIT_DEF){
		u32TopWaitTime = TOP_WAIT_DEF;
	}	
	u32BtmShkNum = u32ShakeNum;
	u32TopShkNum = u32ShakeNum;
	
    /* 发送动作执行命令到人机界面 */
	POST_INFO2SCN(stRfhMsg,BANK_CTRL_SCREEN, BANK_EXPEND_MSG,BANK_ACT_INFO);
	
	/* 配置成组放顶煤整机特性参数*/
	stShdLkg.u32LStartTime = MS_TIMER;
	stShdLkg.u32LDlySendTime = SECOND2MILLI(u32DlyTime);
	//stShdLkg.u32LErrIndex = FLIP1_LMT_NOT_REACH;  // TODO:需要修改
	stShdLkg.u32LStat = LKG_NULL; 
	stShdLkg.u8LType = stRfhPkt.stPkt.u32CmdCode;
	stShdLkg.pfLSendNext = LinkSendNextNull;
	stShdLkg.pfLTimeCheck = mSecTimeCheck;	

	if(TRUE == GetBankEpdSprayEn())
	{
		VALVE_TBL(u32Valve,SHIELD_POS,SPRAY_CMD);	// TODO:应该用放煤喷雾指令
		SET_VALVE(u32Valve);
	}
	
	#if 0	// TODO:邻架喷雾，待重构
	if(TRUE == GetBankEpdNbrSprayEn())
	{
    	stCtrlPkt.u32CmdCode = BANK_SPRAY_CMD;
    	stCtrlPkt.u8Area = 1;
    	stCtrlPkt.u8CmdType = ACTION_CMD_TYPE;
    	stCtrlPkt.u8CommDir = CAN_RIGHT;
    	stCtrlPkt.u8NumOper = 0;
    	stCtrlPkt.u8Offset  = 0;
		stCtrlPkt.bAwayOper = AWAY_OPERATOR;
		s32Ret = tmWrite(stCtrlPkt.u8CommDir,RH_PORT_BANK,sizeof(CONTROL_PKT_S),
                     	(void*)&stCtrlPkt,NOT_NEED_ACK); 
		stCtrlPkt.u8CommDir = CAN_LEFT;
		s32Ret = tmWrite(stCtrlPkt.u8CommDir,RH_PORT_BANK,sizeof(CONTROL_PKT_S),
                     	(void*)&stCtrlPkt,NOT_NEED_ACK); 		
	}
	#endif
	
	while(u32CycleNum--)
    {
		/*放煤动作第一阶段:至低位*/
		ExpendToBottom(&stRfhPkt,&stShdLkg);	
		/*放煤等待*/
		WaitExpend(&stRfhPkt,&stShdLkg,BANK_CTRL_SCREEN,u32BtmWaitTime);	
		/*低位抖动*/
		while(u32BtmShkNum--)	
		{
			TailUpShake(&stRfhPkt,&stShdLkg);
			TailDownShake(&stRfhPkt,&stShdLkg);
		}
		u32BtmShkNum = u32ShakeNum;
		/*放煤动作第二阶段:回高位*/
		ExpendToTop(&stRfhPkt,&stShdLkg);	
		/*高位抖动*/
		while(u32TopShkNum--)	
		{			
			TailDownShake(&stRfhPkt,&stShdLkg);
			TailUpShake(&stRfhPkt,&stShdLkg);
		}
		u32TopShkNum = u32ShakeNum;
		/*上方等待*/
		WaitExpend(&stRfhPkt,&stShdLkg,BANK_CTRL_SCREEN,u32TopWaitTime);	
    }

	VALVE_TBL(u32Valve,SHIELD_POS,SPRAY_CMD);	// TODO:应该用放煤喷雾的指令
	CLR_VALVE(u32Valve);

	return;

}


/*********************************************************************************************************
** Function name:           BankAutoRtnPerch
** Descriptions:            成组回高位
** input parameters:        stRefreshPkt 发送数据
** output parameters:       none
** Returned value:          
** Created by:              linguofeng 
** Created Date:            2015-04-13
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
void BankAutoRtnPerch(PKT_REFRESH_SCN_S stRfhPkt)
{
	SCN_RFH_MSG_S stRfhMsg;
	SHILD_LINKAGE_S stShdLkg;

	 /* 发送动作执行命令到人机界面 */
    POST_INFO2SCN(stRfhMsg,BANK_CTRL_SCREEN, BANK_RETURN_MSG,BANK_ACT_INFO);
	 /* 成组回高位联动参数初始化 */
	RtnPerchLinkageInit(stRfhPkt,&stShdLkg);

    while(1)
    {
        /* 架间延迟时间到 */
		stShdLkg.pfLSendNext(stRfhPkt, &stShdLkg);
		stShdLkg.stLComp[LKG_COMP_TLEVER].pfCompSCtrl(&stShdLkg.stLComp[LKG_COMP_TLEVER]);
		stShdLkg.stLComp[LKG_COMP_SHUTTER].pfCompSCtrl(&stShdLkg.stLComp[LKG_COMP_SHUTTER]);
	
		stShdLkg.u32LStat |= stShdLkg.stLComp[LKG_COMP_TLEVER].u32Stat | stShdLkg.stLComp[LKG_COMP_SHUTTER].u32Stat;
		
        if (LKG_RTN_OVER == stShdLkg.u32LStat)
        {
            break;
        }
		RESPOND_TASK_DEL_REQ();
        OSTimeDly(TIME_DLY_10MS);
    }

	return;
}



void (*g_pfBankAuto[])(PKT_REFRESH_SCN_S ) = {
    BankAutoAdvance,
    BankAutoPush,
    BankAutoPull,
    BankAuto1stFlipOut,
    BankAuto1stFlipIn,
    BankAutoFCantileverOut,
    BankAutoFCantileverIn,
    BankAutoPullRear,
    BankAutoSlidBarOut,
    BankAutoSlidBarIn,
    BankAuto2ndFlipOut,
    BankAuto2ndFlipIn,
    BankAutoFlpLinkageOut,
    BankAutoFlpLinkageIn,
    BankAutoSlidBarLinkageOut,
    BankAutoSlidBarLinkageIn,
    BankAutoSpray,
    BankAutoBSpray,
    BankAutoESpray,
    BankAutoASpray,
    BankAuto3rdFlipOut,
    BankAuto3rdFlipIn,
    BankAutoBWashers,
    BankAutoExpend,
    BankAutoRtnPerch,
};

/*********************************************************************************************************
** Function name:           BankAutoFunc
** Descriptions:            成组自动功能
** input parameters:        
** output parameters:       none
** Returned value:          none
** Created by:              linguofeng 
** Created Date:            2015-04-10
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
void BankAutoFunc(PKT_REFRESH_SCN_S stPkt)
{
    SCN_RFH_MSG_S stRfhMsg;
    g_pfBankAuto[stPkt.stPkt.u32CmdCode - BATCH_ASQ_CMD](stPkt);	
    //OSTimeDly(2*OS_TICKS_PER_SEC);
	WaitASQ(BANK_CTRL_SCREEN,2);
    /* 动作执行完毕，退出当前界面 */
    stRfhMsg.eNextScn = IDLE_SCREEN;    
    sysMsgFlush(gu32ScnRshMsg);
    sysMsgPost(gu32ScnRshMsg,(INT8U *)&stRfhMsg,0);  
}

/*********************************************************************************************************
** Function name:           SlideBarAct
** Descriptions:            伸缩梁动作执行
** input parameters:        u8Type 动作类型，0伸or1收
** output parameters:       none
** Returned value:          none
** Created by:              linguofeng 
** Created Date:            2016-06-12
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
static void SlideBarAct(INT8U u8Type)
{
    INT32U u32Valve = 0;
    char *pDispInfo = NULL;
    SCN_RFH_MSG_S stRfhMsg;
    if (0 == HAS_SLIDE_BAR())
    {
        return;
    }

    /* 伸缩梁开始动作时间 */       
    pDispInfo = ((u8Type == 0) ? ASQ_EXSB_INFO : ASQ_INSB_INFO);
    POST_INFO2SCN(stRfhMsg,ASQ_SCREEN,ASQ_INFO,pDispInfo);
    WaitASQ(ASQ_SCREEN,GetASQSBExST());
    VALVE_TBL(u32Valve,SHIELD_POS,SLIDEBAR_OUT_CMD + u8Type);
    SET_VALVE(u32Valve);
    WaitASQ(ASQ_SCREEN,GetASQSBExT());
    VALVE_TBL(u32Valve,SHIELD_POS,SLIDEBAR_OUT_CMD + u8Type);
    CLR_VALVE(u32Valve);      
}

/*********************************************************************************************************
** Function name:           FirstFlipAct
** Descriptions:            一级护帮动作执行
** input parameters:        u8Type 动作类型，0伸or1收
** output parameters:       none
** Returned value:          none
** Created by:              linguofeng 
** Created Date:            2016-06-12
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
static void FirstFlipAct(INT8U u8Type)
{
    INT32U u32Valve = 0;
    char *pDispInfo = NULL;
    SCN_RFH_MSG_S stRfhMsg;
    INT32U u32Time = 0;
    ErrMsg_Index ErrMsg ;
    if (0 == HAS_FIRST_FLIP())
    {
        return;
    }

    pDispInfo = ((u8Type == FLIP_IN) ? ASQ_EXFLIP_INFO : ASQ_INFLIP_INFO);
    POST_INFO2SCN(stRfhMsg,ASQ_SCREEN,ASQ_INFO,pDispInfo);
    WaitASQ(ASQ_SCREEN,GetASQ1stFlipExST());
    VALVE_TBL(u32Valve,SHIELD_POS,FST_FLIP_OUT_CMD + u8Type);
    SET_VALVE(u32Valve);
    u32Time = SEC_TIMER ;
    while(1)
    {
        if (SecTimeCheck(u32Time,GetASQ1stFlipExT()))    
        {
            //ErrMsg = (u8Type == 0) ? FLIP1_PRS_NOT_REACH : FLIP1_LMT_NOT_REACH;
			ErrMsg = FLIP1_LMT_NOT_REACH;
            SetErrMsg(ErrMsg,TRUE,NO_ERRMSG_PARA);
            pDispInfo = ((u8Type == FLIP_IN) ? NULL_INFO : ASQ_1FLIP_UNLMT_INFO);
            POST_INFO2SCN(stRfhMsg,ASQ_SCREEN,ASQ_INFO,pDispInfo);
            break;
        }
        if (Check1stFlipLmtP(u8Type))
        {
            break;
        }
        RESPOND_TASK_DEL_REQ();
        OSTimeDly(TIME_DLY_20MS);            
    }
    VALVE_TBL(u32Valve,SHIELD_POS,FST_FLIP_OUT_CMD + u8Type);
    CLR_VALVE(u32Valve);


}
/*********************************************************************************************************
** Function name:           FirstFlipAct
** Descriptions:            一级护帮动作执行
** input parameters:        u8Type 动作类型，0伸or1收
** output parameters:       none
** Returned value:          none
** Created by:              linguofeng 
** Created Date:            2016-06-12
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
static void SecondFlipAct(INT8U u8Type)
{
    INT32U u32Valve = 0;
    char *pDispInfo = NULL;
    SCN_RFH_MSG_S stRfhMsg;
    INT32U u32Time = 0;

    if (0 == HAS_SECOND_FLIP())
    {
        return;
    }

    pDispInfo = ((u8Type == FLIP_IN) ? ASQ_EX2FLIP_INFO : ASQ_IN2FLIP_INFO);
    POST_INFO2SCN(stRfhMsg,ASQ_SCREEN,ASQ_INFO,pDispInfo);
    WaitASQ(ASQ_SCREEN,GetASQ2ndFlipExST());
    VALVE_TBL(u32Valve,SHIELD_POS,SND_FLIP_OUT_CMD + u8Type);
    SET_VALVE(u32Valve);
    u32Time = SEC_TIMER ;
    while(1)
    {
        if (SecTimeCheck(u32Time,GetASQ2ndFlipExT()))
        {
            pDispInfo = ((u8Type == FLIP_IN) ? NULL_INFO : ASQ_2FLIP_UNLMT_INFO);
            POST_INFO2SCN(stRfhMsg,ASQ_SCREEN,ASQ_INFO,pDispInfo);
            break;
        }
        if (Check2ndFlipLmtP(u8Type))
        {
            break;
        }
        RESPOND_TASK_DEL_REQ();
        OSTimeDly(TIME_DLY_20MS);
    }
    VALVE_TBL(u32Valve,SHIELD_POS,SND_FLIP_OUT_CMD + u8Type);
    CLR_VALVE(u32Valve);
    

}
/*********************************************************************************************************
** Function name:           FirstFlipAct
** Descriptions:            一级护帮动作执行
** input parameters:        u8Type 动作类型，0伸or1收
** output parameters:       none
** Returned value:          none
** Created by:              linguofeng 
** Created Date:            2016-06-12
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
static void ThirdFlipAct(INT8U u8Type)
{
    INT32U u32Valve = 0;
    char *pDispInfo = NULL;
    SCN_RFH_MSG_S stRfhMsg;
    INT32U u32Time = 0;

    if (0 == HAS_THIRD_FLIP())
    {
        return;
    }

    pDispInfo = ((u8Type == FLIP_IN) ? ASQ_EX3FLIP_INFO : ASQ_IN3FLIP_INFO);
    POST_INFO2SCN(stRfhMsg,ASQ_SCREEN,ASQ_INFO,pDispInfo);
    WaitASQ(ASQ_SCREEN,GetASQ3rdFlipExST());
    VALVE_TBL(u32Valve,SHIELD_POS,THD_FLIP_OUT_CMD + u8Type);
    SET_VALVE(u32Valve);
    u32Time = SEC_TIMER;
    while(1)
    {
        if (SecTimeCheck(u32Time,GetASQ3rdFlipExT()))
        {
            if (u8Type == FLIP_EX)
            {
                SetErrMsg(FLIP3_LMT_NOT_REACH,TRUE,NO_ERRMSG_PARA);    
            }
            pDispInfo = ((u8Type == 0) ? NULL_INFO : ASQ_3FLIP_UNLMT_INFO); 
            POST_INFO2SCN(stRfhMsg,ASQ_SCREEN,ASQ_INFO,pDispInfo);
            break;
        }
        if (Check3rdFlipLmtP(u8Type))
        {
            break;
        }
        RESPOND_TASK_DEL_REQ();
        OSTimeDly(TIME_DLY_20MS);
    }
    VALVE_TBL(u32Valve,SHIELD_POS,THD_FLIP_OUT_CMD + u8Type);
    CLR_VALVE(u32Valve);
}


/*********************************************************************************************************
** Function name:           SlideBarFlipCtrl
** Descriptions:            伸缩梁护帮联动控制
** input parameters:        u8Type 动作类型，0伸or1收
** output parameters:       none
** Returned value:          none
** Created by:              linguofeng 
** Created Date:            2015-05-22
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
void SlideBarFlipCtrl(INT8U u8Type)
{
        
    if (0 == GetASQSBlink())
    {
        return;
    }
    
    SlideBarAct(u8Type);
    if (FLIP_IN == u8Type)
    {
        FirstFlipAct(u8Type);
        SecondFlipAct(u8Type);
        ThirdFlipAct(u8Type);

    }
    else
    {    
        ThirdFlipAct(u8Type);
        SecondFlipAct(u8Type);
        FirstFlipAct(u8Type);    

    }

}

/*********************************************************************************************************
** Function name:           StabCtrl
** Descriptions:            平衡千斤顶联动控制
** input parameters:        u8Type 动作类型，伸or收
** output parameters:       none
** Returned value:          none
** Created by:              linguofeng 
** Created Date:            2015-05-22
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
void StabCtrl(INT8U u8Type)
{
    INT32U u32Valve = 0;
    SCN_RFH_MSG_S stRfhMsg;

    if (0 == GetBankAdvStab()||(0 == HAS_STAB_RAM()) )
    {
        return;
    }
    POST_INFO2SCN(stRfhMsg,ASQ_SCREEN,ASQ_INFO,ASQ_INSTAB_INFO);
    VALVE_TBL(u32Valve,SHIELD_POS,STAB_OUT_CMD + u8Type);
    SET_VALVE(u32Valve);
    // TODO: 啥时候停止呢
}
/*********************************************************************************************************
** Function name:           SideSealCtrl
** Descriptions:            侧护联动控制
** input parameters:        u8Type 动作类型，伸or收
** output parameters:       none
** Returned value:          none
** Created by:              linguofeng 
** Created Date:            2015-05-22
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
void SideSealCtrl(INT8U u8Type)
{
    INT32U u32Valve = 0;
    char *pDispInfo = NULL;
    SCN_RFH_MSG_S stRfhMsg;
    
    if ((0 == GetBankAdvSSAdv())||(0 == GetBankAdvSSLower())||(0 == HAS_SIDE_SEAL()))
    {
        return;
    }
    
    pDispInfo = ((u8Type==0) ? ASQ_EXSTAB_INFO : ASQ_INSS_INFO);   
    POST_INFO2SCN(stRfhMsg,ASQ_SCREEN,ASQ_INFO,pDispInfo);
    VALVE_TBL(u32Valve,SHIELD_POS,SIDESEAL_OUT_CMD + u8Type);
    SET_VALVE(u32Valve);
    // TODO:啥时候停止
}
/*********************************************************************************************************
** Function name:           StabDiffCtrl
** Descriptions:            平衡差动控制
** input parameters:        
** output parameters:       none
** Returned value:          none
** Created by:              linguofeng 
** Created Date:            2015-05-22
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
void StabDiffCtrl(INT8U u8Type)
{
    if (0 == HAS_STAB_RAM())
    {
        return;
    }
}
/*********************************************************************************************************
** Function name:           SprayCtrl
** Descriptions:            喷雾联动控制
** input parameters:        pu32CtrlTimer 软件定时器首地址
** output parameters:       none
** Returned value:          none
** Created by:              linguofeng 
** Created Date:            2015-05-22
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
void SprayCtrl(INT32U *pu32CtrlTimer)
{
    INT32U u32Valve = 0;
    SCN_RFH_MSG_S stRfhMsg;
    
    if (!GetASQSprayEn())
    {
        return;
    }
    
    WaitASQ(ASQ_SCREEN,GetASQSprayST());    
    POST_INFO2SCN(stRfhMsg,ASQ_SCREEN,ASQ_INFO,ASQ_SPRAY_INFO);
    VALVE_TBL(u32Valve,SHIELD_POS,SPRAY_CMD);
    SET_VALVE(u32Valve);
    pu32CtrlTimer[SPRAY_CMD] = SEC_TIMER + GetASQSprayT();
}

/*********************************************************************************************************
** Function name:           AdvanceCtrl
** Descriptions:            移架控制
** input parameters:        pcInfo显示信息，移架时间长度
** output parameters:       none
** Returned value:          none
** Created by:              linguofeng 
** Created Date:            2015-05-22
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
void AdvanceCtrlbak(char *pcInfo,INT8U u8Time)
{
    INT32U u32Valve = 0;
    INT32U u32Timer = 0;
    SCN_RFH_MSG_S stRfhMsg;
    
    /* 根据设置 发送邻架助推报文，邻架助推功能推溜时间200s */
    if (GetNbrAssisPushEn())
    {
        /* 向邻架发送助推报文 */
        // TODO: 创建邻架助推端口
    }    
    
    POST_INFO2SCN(stRfhMsg,ASQ_SCREEN,ASQ_INFO,pcInfo);
    
    /* 移架时间，行程控制*/
    VALVE_TBL(u32Valve,SHIELD_POS,ADVANCE_CMD);
    SET_VALVE(u32Valve);
    u32Timer = SEC_TIMER ;
    /* 检查移架时间到时，行程是否到位，没到位则根据设置执行再降柱移架过程，记录错误信息*/
    while(1)
    {
        if (SecTimeCheck(u32Timer,u8Time))                
        {
            if (!GetASQReAdvEn())
            {                
                SetErrMsg(ADV_TIMEOUT,TRUE,NO_ERRMSG_PARA);                
                POST_INFO2SCN(stRfhMsg,ASQ_SCREEN,ASQ_INFO,ASQ_ADVTOUT_INFO);
                OSTimeDly(OS_TICKS_PER_SEC);
            }
            break;
        }
        if ((INT32U)GetConveyorExtens() < GetASQEndStrk())
        {
            break;
        }
        RESPOND_TASK_DEL_REQ();
        OSTimeDly(TIME_DLY_20MS);
    }
    VALVE_TBL(u32Valve,SHIELD_POS,ADVANCE_CMD);
    CLR_VALVE(u32Valve);
    /* 移架完成后，发送邻架停止助推报文*/
    if (GetNbrAssisPushEn())
    {
        // TODO: 发送停止助推报文到邻架
    }
}
BOOLEAN AdvanceCtrl(SCREEN_INDEX_E eScnIndex,void *pDispStr0,void *pDispStr1,INT8U u8Time)
{
    INT32U u32Valve = 0;
    INT32U u32Timer = 0;
    SCN_RFH_MSG_S stRfhMsg;
    BOOLEAN bRet = TRUE;
    /* 根据设置 发送邻架助推报文，邻架助推功能推溜时间200s */
    if (GetNbrAssisPushEn())
    {
        /* 向邻架发送助推报文 */
        // TODO: 创建邻架助推端口
    }    
    
    POST_INFO2SCN(stRfhMsg,eScnIndex,pDispStr0,pDispStr1);
    
    /* 移架时间，行程控制*/
    VALVE_TBL(u32Valve,SHIELD_POS,ADVANCE_CMD);
    SET_VALVE(u32Valve);
    u32Timer = SEC_TIMER ;
    /* 检查移架时间到时，行程是否到位，没到位则根据设置执行再降柱移架过程，记录错误信息*/
    while(1)
    {
        if (SecTimeCheck(u32Timer,u8Time))                
        {
            if (!GetASQReAdvEn()&&GetConvSnrEn())
            {                
                SetErrMsg(ADV_TIMEOUT,TRUE,NO_ERRMSG_PARA);                
                POST_INFO2SCN(stRfhMsg,eScnIndex,pDispStr0,ASQ_ADVTOUT_INFO);
                //OSTimeDly(OS_TICKS_PER_SEC);
                WaitASQ(ASQ_SCREEN,OS_TICKS_PER_SEC);
            }
            break;
        }
        if (((INT32U)GetConveyorExtens() < GetASQEndStrk()) && GetConvSnrEn())
        {
            break;
        }
        if (CheckAutoSafeOper(eScnIndex))
        {
            bRet = FALSE;
            break;
        }
        RESPOND_TASK_DEL_REQ();
        OSTimeDly(TIME_DLY_20MS);
    }
    VALVE_TBL(u32Valve,SHIELD_POS,ADVANCE_CMD);
    CLR_VALVE(u32Valve);
    /* 移架完成后，发送邻架停止助推报文*/
    if (GetNbrAssisPushEn())
    {
        // TODO: 发送停止助推报文到邻架
    }
    return bRet;
}

/*********************************************************************************************************
** Function name:           ReAdvanceCtrl
** Descriptions:            再移架控制，第一次移架不到位，需要再次移架
** input parameters:        
** output parameters:       none
** Returned value:          false 发生急停闭锁 true 没有急停闭锁
** Created by:              linguofeng 
** Created Date:            2015-05-22
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
BOOLEAN ReAdvanceCtrl(SCREEN_INDEX_E eScnIndex,void* pDsipStr)
{
    INT32U u32Valve = 0;
    INT32U u32Time = 0;
    SCN_RFH_MSG_S stRfhMsg;
    BOOLEAN bRet = TRUE;
    /* 禁止再移架或移架已经到位*/
    if (!GetASQReAdvEn())
    {
        return bRet;
    }
    
    POST_INFO2SCN(stRfhMsg,eScnIndex,pDsipStr,ASQ_LOWADV_INFO);
    VALVE_TBL(u32Valve,SHIELD_POS,ADVANCE_CMD);
    SET_VALVE(u32Valve);

    SetShdLeg(LOWER_LEG_CMD,LOWE_REAR_LEG_CMD);
    u32Time = SEC_TIMER ;
    while(1)
    {
        if (SecTimeCheck(u32Time,GetASQReAdvCnt()*GetASQReAdvT()))                    
        {
            if (GetConvSnrEn())
            {
                POST_INFO2SCN(stRfhMsg,eScnIndex,pDsipStr,ASQ_ADVTOUT_INFO);
            }
            break;
        }
        if (SecTimeCheck(u32Time,GetASQReAdvLowT()))
        {
            ClrShdLeg(LOWER_LEG_CMD,LOWE_REAR_LEG_CMD);
        }
        if (((INT32U)GetConveyorExtens() < GetASQEndStrk())&&GetConvSnrEn())
        {
            break;
        }
        if (CheckAutoSafeOper(eScnIndex))
        {
            bRet = FALSE;
            break;
        }
        OSTimeDly(TIME_DLY_20MS);
    } 
    VALVE_TBL(u32Valve,SHIELD_POS,ADVANCE_CMD);
    CLR_VALVE(u32Valve);    
    ClrShdLeg(LOWER_LEG_CMD,LOWE_REAR_LEG_CMD);
    return bRet;
}
/*********************************************************************************************************
** Function name:           LowerCtrl
** Descriptions:            降柱控制
** input parameters:        cInfo 降柱提示信息；u8LowTimer降柱时间
** output parameters:       none
** Returned value:          none
** Created by:              linguofeng 
** Created Date:            2015-05-22
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
void LowerCtrlbak(char* pcInfo,INT8U u8LowTimer)
{
    INT32U u32Timer = 0;
    INT32U u32ValveFnt = 0;
    INT32U u32ValveRear = 0;
    INT32U u32Stop = 0;/* 到达降柱停止压力立柱 */
    SCN_RFH_MSG_S stRfhMsg;
    
    POST_INFO2SCN(stRfhMsg,ASQ_SCREEN,ASQ_INFO,pcInfo);

    u32Timer = SEC_TIMER ;
    SetShdLeg(LOWER_LEG_CMD,LOWE_REAR_LEG_CMD);
    while(1)
    {
        /* 前柱压力检测 */
        u32ValveFnt = PressureLessCheck(GetFormerPropPressure(),GetASQADVP0(),&u32Stop,LOWER_LEG_CMD);
        /* 后柱压力检测 */
        if (0 != HAS_REAR_LEG())
        {
            u32ValveRear = PressureLessCheck(GetRearPropPressure(),GetASQADVP0(),&u32Stop,LOWE_REAR_LEG_CMD);
            if (u32Stop  == (u32ValveFnt|u32ValveRear))
            {
                break;
            }
        }
        else if (u32Stop & u32ValveFnt)
        {
            break;
        }  
        
        if (SecTimeCheck(u32Timer,u8LowTimer))
        {
            SetErrMsg(ADV_DIST_ALREADY_INPLACE,TRUE,NO_ERRMSG_PARA);
            
            ClrShdLeg(LOWER_LEG_CMD,LOWE_REAR_LEG_CMD);                  
            POST_INFO2SCN(stRfhMsg,ASQ_SCREEN,ASQ_INFO,ASQ_LOWTOUT_INFO);
            OSTimeDly(OS_TICKS_PER_SEC);
            break;
        }
        RESPOND_TASK_DEL_REQ();
        OSTimeDly(TIME_DLY_20MS);
    }
}


BOOLEAN LowerCtrl(SCREEN_INDEX_E eScnIndex,void *pDispStr0,void* pDispStr1,INT8U u8LowTimer)
{
    INT32U u32Timer = 0;
    INT32U u32ValveFnt = 0;
    INT32U u32ValveRear = 0;
    INT32U u32Stop = 0;/* 到达降柱停止压力立柱 */
    SCN_RFH_MSG_S stRfhMsg;
    BOOLEAN bRet = TRUE;
    POST_INFO2SCN(stRfhMsg,eScnIndex,pDispStr0,pDispStr1);

    u32Timer = SEC_TIMER ;
    SetShdLeg(LOWER_LEG_CMD,LOWE_REAR_LEG_CMD);
    while(1)
    {
        /* 前柱压力检测 */
        if (GetLegSnrEn())
        {
            u32ValveFnt = PressureLessCheck(GetFormerPropPressure(),GetASQADVP0(),&u32Stop,LOWER_LEG_CMD);
        }
        /* 后柱压力检测 */
        if ((0 != HAS_REAR_LEG()) && GetRLegSnrEn())
        {
            u32ValveRear = PressureLessCheck(GetRearPropPressure(),GetASQADVP0(),&u32Stop,LOWE_REAR_LEG_CMD);
            if (u32Stop  == (u32ValveFnt|u32ValveRear))
            {
                break;
            }
        }
        else if (u32Stop & u32ValveFnt)
        {
            break;
        }  
        
        if (SecTimeCheck(u32Timer,u8LowTimer))
        {
            ClrShdLeg(LOWER_LEG_CMD,LOWE_REAR_LEG_CMD);
            if (GetLegSnrEn())
            {
                SetErrMsg(ADV_DIST_ALREADY_INPLACE,TRUE,NO_ERRMSG_PARA);                                         
                POST_INFO2SCN(stRfhMsg,eScnIndex,pDispStr0,ASQ_LOWTOUT_INFO);
               // OSTimeDly(OS_TICKS_PER_SEC);
                WaitASQ(ASQ_SCREEN,OS_TICKS_PER_SEC);
            }
            break;
        }
        if (CheckAutoSafeOper(eScnIndex))
        {
            bRet = FALSE;
            break;
        }
        RESPOND_TASK_DEL_REQ();
        OSTimeDly(TIME_DLY_20MS);
    }
    return bRet;
}

/*********************************************************************************************************
** Function name:           PreSetCtrl
** Descriptions:            预升柱控制
** input parameters:        
** output parameters:       none
** Returned value:          none
** Created by:              linguofeng 
** Created Date:            2015-05-22
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
BOOLEAN PreSetCtrl(SCREEN_INDEX_E eScnIndex,void *pDsipStr)
{
    INT32U u32Valve = 0;
    SCN_RFH_MSG_S stRfhMsg;
    INT32U u32Time = GetASQPreLowT();
    BOOLEAN bRet = FALSE;
    /* 非四柱支架 或 预降升柱禁止 */
    if ((0 == HAS_REAR_LEG())||( !GetASQPreLowEn()))
    {
        return bRet;
    }    
    
    POST_INFO2SCN(stRfhMsg,eScnIndex,pDsipStr,ASQ_PRESET_INFO);
    // TODO:  前柱or后柱预升柱也没有参数，预升柱后柱   
    VALVE_TBL(u32Valve,SHIELD_POS,SET_LEG_CMD);
    SET_VALVE(u32Valve);
    WaitASQ(eScnIndex,u32Time);
    
    return bRet;
}
/*********************************************************************************************************
** Function name:           SetP1Ctrl
** Descriptions:            升柱至P1控制
** input parameters:        pcInfo显示信息，u8Time动作时间
** output parameters:       none
** Returned value:          none
** Created by:              linguofeng 
** Created Date:            2015-05-22
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
void SetP1Ctrlbak(char *pcInfo,INT8U u8Time)
{
    INT32U u32Time = 0;
    INT32U u32Stop = 0;
    INT32U u32FntLeg = 0;
    INT32U u32RearLeg = 0;
    SCN_RFH_MSG_S stRfhMsg;
    
    POST_INFO2SCN(stRfhMsg,ASQ_SCREEN,ASQ_INFO,pcInfo);
    SetShdLeg(SET_LEG_CMD,SET_REAR_LEG_CMD);
    u32Time = SEC_TIMER ;
        
    while(1)
    {
        u32FntLeg = PressureNoLessCheck(GetFormerPropPressure(),GetASQADVP1(),&u32Stop,SET_LEG_CMD);
        if (0 != HAS_REAR_LEG())
        {
            u32RearLeg = PressureNoLessCheck(GetFormerPropPressure(),GetASQADVP1(),&u32Stop,SET_LEG_CMD);
            if (u32Stop == (u32FntLeg|u32RearLeg))
            {
                break;
            }
        }
        else if (u32Stop & u32FntLeg)
        {
            break;
        }
        if (SecTimeCheck(u32Time,u8Time))
        {            
            POST_INFO2SCN(stRfhMsg,ASQ_SCREEN,ASQ_INFO,ASQ_SETTOUT_INFO);
            break;
        }
        RESPOND_TASK_DEL_REQ();
        OSTimeDly(TIME_DLY_20MS);
    }    
    ClrShdLeg(SET_LEG_CMD,SET_REAR_LEG_CMD);
}
BOOLEAN SetP1Ctrl(SCREEN_INDEX_E eScnIndex,void* pDispStr0,void *pDispStr1,INT8U u8Time)
{
    INT32U u32Time = 0;
    INT32U u32Stop = 0;
    INT32U u32FntLeg = 0;
    INT32U u32RearLeg = 0;
    SCN_RFH_MSG_S stRfhMsg;
    BOOLEAN bRet = TRUE;
    POST_INFO2SCN(stRfhMsg,eScnIndex,pDispStr0,pDispStr1);
    SetShdLeg(SET_LEG_CMD,SET_REAR_LEG_CMD);
    u32Time = SEC_TIMER ;
        
    while(1)
    {
        if (GetLegSnrEn())
        {
            u32FntLeg = PressureNoLessCheck(GetFormerPropPressure(),GetASQADVP1(),&u32Stop,SET_LEG_CMD);
        }
        if ((0 != HAS_REAR_LEG()) && GetRLegSnrEn())
        {
            u32RearLeg = PressureNoLessCheck(GetFormerPropPressure(),GetASQADVP1(),&u32Stop,SET_LEG_CMD);
            if (u32Stop == (u32FntLeg|u32RearLeg))
            {
                break;
            }
        }
        else if (u32Stop & u32FntLeg)
        {
            break;
        }
        if (SecTimeCheck(u32Time,u8Time))
        {   if (GetLegSnrEn())
            {
                POST_INFO2SCN(stRfhMsg,eScnIndex,pDispStr0,ASQ_SETTOUT_INFO);
                SetErrMsg(ADV_SET_OVERTIME,TRUE,NO_ERRMSG_PARA); 
            }
            break;
        }
        RESPOND_TASK_DEL_REQ();
        if (CheckAutoSafeOper( eScnIndex))
        {
            bRet = FALSE;
            break;
        }
        OSTimeDly(TIME_DLY_20MS);
    }    
    ClrShdLeg(SET_LEG_CMD,SET_REAR_LEG_CMD);
    return bRet;
}

/*********************************************************************************************************
** Function name:           SetP2Ctrl
** Descriptions:            升柱至P2控制
** input parameters:        
** output parameters:       none
** Returned value:          none
** Created by:              linguofeng 
** Created Date:            2015-05-26
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
BOOLEAN SetP2Ctrl(SCREEN_INDEX_E eScnIndex, void*pDispStr0,void *pDispStr1,INT8U u8Time)
{
   return SetP1Ctrl(eScnIndex,pDispStr0,pDispStr1,u8Time);
}
/*********************************************************************************************************
** Function name:           LiftCtrl
** Descriptions:            抬底控制
** input parameters:        pu32CtrlTimer 软件定时器首地址
** output parameters:       none
** Returned value:          none
** Created by:              linguofeng 
** Created Date:            2015-05-22
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
void LiftCtrl(INT32U *pu32CtrlTimer)
{
    INT32U u32Valve = 0;
    SCN_RFH_MSG_S stRfhMsg;
    
    if (!GetASQLiftEn())
    {
        return;
    }
    
    POST_INFO2SCN(stRfhMsg,ASQ_SCREEN,ASQ_INFO,ASQ_LIFT_INFO);
    WaitASQ(ASQ_SCREEN,GetASQLiftST());
    VALVE_TBL(u32Valve,SHIELD_POS,LIFTING_CMD);
    SET_VALVE(u32Valve);
    pu32CtrlTimer[LIFTING_CMD] = SEC_TIMER + GetASQLiftT();
}
/*********************************************************************************************************
** Function name:           PreLowerCtrl
** Descriptions:            预降柱控制
** input parameters:        
** output parameters:       none
** Returned value:          none
** Created by:              linguofeng 
** Created Date:            2015-05-26
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
BOOLEAN PreLowerCtrl(SCREEN_INDEX_E eScnIndex,void * pDispStr)
{
    INT32U u32Valve = 0;
    SCN_RFH_MSG_S stRfhMsg;
    INT32U u32Time = GetASQPreLowT();        
    BOOLEAN bRet = TRUE;
    if ((0 == HAS_REAR_LEG())||(!GetASQPreLowEn()))
    {
        return bRet;
    }    
    POST_INFO2SCN(stRfhMsg,eScnIndex,pDispStr,ASQ_PRELOW_INFO);
    VALVE_TBL(u32Valve,SHIELD_POS,LOWER_LEG_CMD);
    SET_VALVE(u32Valve);

    bRet = WaitASQ(eScnIndex,u32Time);
   
    return bRet;
}
/*********************************************************************************************************
** Function name:           ReLowerCtrl
** Descriptions:            再降柱控制
** input parameters:        
** output parameters:       none
** Returned value:          none
** Created by:              linguofeng 
** Created Date:            2015-05-26
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
void ReLowerCtrl(SCREEN_INDEX_E eScnIndex,void *pDispStr0)
{
    LowerCtrl(eScnIndex,pDispStr0,ASQ_RELOW_INFO, GetASQReLowT());   
}

/*********************************************************************************************************
** Function name:           CheckNeighborsPressure
** Descriptions:            
** input parameters:        
** output parameters:       none
** Returned value:          0 邻架压力达到支撑压力 非0邻架压力不满足
** Created by:              linguofeng 
** Created Date:            2015-12-23
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
static INT8U CheckNeighborsPressure(void)
{
    NEIGHBOR_INFO_S stData ;
    stData.u8NbrPressure = 0;
    tmRead(CAN_LEFT,0,RH_PORT_NBRINFO,sizeof(stData),(void * )&stData);
    if (stData.u8NbrPressure != 0)
    {
        return stData.u8NbrPressure;
    }
    tmRead(CAN_RIGHT,0,RH_PORT_NBRINFO,sizeof(stData),(void * )&stData);
    return stData.u8NbrPressure;            
}
/*********************************************************************************************************
** Function name:           SingleASQCtrl
** Descriptions:            单架ASQ功能
** input parameters:        
** output parameters:       none
** Returned value:          none
** Created by:              linguofeng 
** Created Date:            2015-05-12
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
void SingleASQCtrl(void)
{
    INT32U u32Valve = 0;
    SCN_RFH_MSG_S stRfhMsg;
    INT32U u32Time = GetASQWarnT();
    
    /* 检查ASQ使能状态 */ 
    if (!GetAdvanceEnable())
    {
        /* 显示 ASQ功能禁止 */
        POST_INFO2SCN(stRfhMsg,ASQ_SCREEN,ASQ_INFO,ASQ_DISABLE_INFO);
        return;
    }
                                  
    /* 参数中设置邻架相关使能，获取邻架压力，不满足大于P1 退出ASQ */
    if (GetASQNbrRlt())
    {
        if ((CheckNeighborsPressure() != 0) && GetLegSnrEn())
        {            
            SetErrMsg(NBR_CANNOT_FULL_SUPPORT,TRUE,NO_ERRMSG_PARA);            
            POST_INFO2SCN(stRfhMsg,ASQ_SCREEN,ASQ_INFO,NBR_SET_INFO);
            return;
        }
    }

    /* 获取推移行程，到达目标值，退出 */
    if (((INT32U)GetConveyorExtens() < GetASQEndStrk()) && GetConvSnrEn())
    {
        POST_INFO2SCN(stRfhMsg,ASQ_SCREEN,ASQ_INFO,ADV_ENDSTRK_INFO);
        return;
    }

    /* 预警时间控制 */
    if (GetASQWarn())
    {
        WaitASQ(ASQ_SCREEN,u32Time);
    }
    /* 参数护帮联动使能，执行收伸缩梁，收1，3级护帮板 */
    SlideBarFlipCtrl(1);
  
    /* 开始喷雾 */
//    SprayCtrl(g_su32CtrlTimer);

    /* 伸缩梁护帮动作和降柱动作之间的延迟时间 */
    //OSTimeDly( GetASQLowerDly());
    WaitASQ(ASQ_SCREEN,GetASQLowerDly());
    /* 参数设置 执行收平衡 */
  //  StabCtrl(0);

    /* 参数设置 执行收侧护 */
//    SideSealCtrl(0);    
    /* 获取支架类型，4柱or2柱，执行预降柱*/
    PreLowerCtrl(ASQ_SCREEN,ASQ_INFO);        
   
    /* 开始降柱，降柱目标压力P0*/
    LowerCtrl(ASQ_SCREEN,ASQ_INFO,ASQ_LOWER_INFO,GetASQLowerT());
    
    /* 参数设置 执行抬底控制 */    
 //   LiftCtrl(g_su32CtrlTimer);
    
    /* 停止收平衡 */
    VALVE_TBL(u32Valve,SHIELD_POS,STAB_OUT_CMD);
    CLR_VALVE(u32Valve);
    
    /* 判断擦顶移架关闭，是否到达移架压力，未到达再次执行降柱*/
    if (!GetBankAdvRubRoof())
    {
        /* 再降柱控制*/
        ReLowerCtrl(ASQ_SCREEN,ASQ_INFO);
    }
    
    /* 参数设置 执行侧护动作 */    
    //SideSealCtrl(1);
    
    /* 开始移架 */
    AdvanceCtrl(ASQ_SCREEN,ASQ_INFO,ASQ_ADV_INFO,GetASQADVT());
    
    /* 再移架控制 */
    ReAdvanceCtrl(ASQ_SCREEN,ASQ_INFO);
    
    /* 获取支架类型，4柱or2柱，执行预升柱*/
    PreSetCtrl(ASQ_SCREEN,ASQ_INFO);

    /* 根据设置确定伸收侧护板 */
    SideSealCtrl(1); 
    
    /* 升柱控制 */
    SetP1Ctrl(ASQ_SCREEN,ASQ_INFO,ASQ_SETP1_INFO,GetASQSetP1T());           
   
    /* 有平衡千斤顶 开启差动平衡 */    
    StabDiffCtrl(0);
    
    /* 升柱至压力P2 */
    SetP2Ctrl(ASQ_SCREEN,ASQ_INFO,ASQ_SETP2_INFO,GetASQSetP2T());

    SlideBarFlipCtrl(0);      
}
/*********************************************************************************************************
** Function name:           CheckNbrASQStatus
** Descriptions:            获取邻架是否正在执行ASQ动作
** input parameters:        
** output parameters:       none
** Returned value:          true 是 false 否
** Created by:              linguofeng 
** Created Date:            2016-03-22
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
static BOOLEAN CheckNbrASQStatus(void)
{
    NEIGHBOR_INFO_S stData ;
    stData.bNbrASQStat = FALSE;
    tmRead(CAN_LEFT,0,RH_PORT_NBRINFO,sizeof(stData),(void *)&stData);
    if (stData.bNbrASQStat)
    {
        return stData.bNbrASQStat;
    }
    tmRead(CAN_RIGHT,0,RH_PORT_NBRINFO,sizeof(stData),(void *)&stData);
    return stData.bNbrASQStat;
}
/*********************************************************************************************************
** Function name:           WaitNbrASQEnd
** Descriptions:            等待邻架完成ASQ
** input parameters:        
** output parameters:       none
** Returned value:          false 发送安全操作 true 等待时间到
** Created by:              linguofeng 
** Created Date:            2016-03-23
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
static BOOLEAN WaitNbrASQEnd(void)
{
    BOOLEAN bRet = TRUE;
    SCN_RFH_MSG_S stRfhMsg;

    if (!CheckNbrASQStatus())
    {
        return bRet;
    }
    POST_INFO2SCN(stRfhMsg,AUTO_SCREEN,AUTO_ASQ_INFO,NBR_WAIT_INFO);
    while(CheckNbrASQStatus())
    {
        if (ESTOP_ACCURED == GetEStopStat())
        {
            bRet = FALSE;
            break;
        }
        OSTimeDly(TIME_DLY_100MS);
    }
    return bRet;
}
/*********************************************************************************************************
** Function name:           AutoASQCtrl
** Descriptions:            跟机移架
** input parameters:        
** output parameters:       none
** Returned value:          none
** Created by:              linguofeng 
** Created Date:            2016-03-22
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
void AutoASQCtrl(void)
{
    SCN_RFH_MSG_S stRfhMsg;
    BOOLEAN bEstopAccured = FALSE;
    /* 检查ASQ使能状态 */ 
    if (!GetAdvanceEnable())
    {
        POST_INFO2SCN(stRfhMsg,AUTO_SCREEN,AUTO_ASQ_INFO,ASQ_DISABLE_INFO);
        return;
    }     
    
    if (!WaitNbrASQEnd())
    {
        POST_INFO2SCN(stRfhMsg,IDLE_SCREEN,NULL_INFO,NULL_INFO);
        return;
    }
    SetAutoASQStat(TRUE);
    /* 参数中设置邻架相关使能，获取邻架压力，不满足大于P1 退出ASQ */
    if (GetASQNbrRlt())
    {
        if ((CheckNeighborsPressure() != 0) && GetLegSnrEn())
        {            
            SetErrMsg(NBR_CANNOT_FULL_SUPPORT,TRUE,NO_ERRMSG_PARA);            
            POST_INFO2SCN(stRfhMsg,AUTO_SCREEN,AUTO_ASQ_INFO,NBR_SET_INFO);
            SetAutoASQStat(FALSE);
            return;
        }
    }
    /* 获取推移行程，到达目标值，退出 */
    if (((INT32U)GetConveyorExtens() < GetASQEndStrk()) && GetConvSnrEn())
    {
        POST_INFO2SCN(stRfhMsg,AUTO_SCREEN,AUTO_ASQ_INFO,ADV_ENDSTRK_INFO);
        SetAutoASQStat(FALSE);
        return;
    }
    do{
        /* 获取支架类型，4柱or2柱，执行预降柱*/
        if (!PreLowerCtrl(AUTO_SCREEN,AUTO_ASQ_INFO))
        {
            bEstopAccured = TRUE;
            break;
        }
        /* 开始降柱，降柱目标压力P0*/
        if (!LowerCtrl(AUTO_SCREEN,AUTO_ASQ_INFO,ASQ_LOWER_INFO,GetASQLowerT()))
        {
            bEstopAccured = TRUE;
            break;
        }
        /* 开始移架 */
        
        if (!AdvanceCtrl(AUTO_SCREEN,AUTO_ASQ_INFO,ASQ_ADV_INFO,GetASQADVT()))
        {
            bEstopAccured = TRUE;
            break;
        }
        /* 再移架控制 */
        if (!ReAdvanceCtrl(AUTO_SCREEN,AUTO_ASQ_INFO))
        {
            bEstopAccured = TRUE;
            break;
        }
        /* 获取支架类型，4柱or2柱，执行预升柱*/
        if (!PreSetCtrl(AUTO_SCREEN,AUTO_ASQ_INFO))
        {
            break;
        }
        /* 升柱控制 */      
        if (!SetP1Ctrl(AUTO_SCREEN,AUTO_ASQ_INFO,ASQ_SETP1_INFO,GetASQSetP1T()))
        {
            bEstopAccured = TRUE;
            break;
        }
        /* 升柱至压力P2 */
        if (! SetP2Ctrl(AUTO_SCREEN,AUTO_ASQ_INFO,ASQ_SETP2_INFO,GetASQSetP2T()))
        {
            bEstopAccured = TRUE;
            break;
        }
    }while(0);
    SetAutoASQStat(FALSE);
    if (bEstopAccured)
    {
       /* 发生急停闭锁时，停止电磁阀动作，仅开立柱电磁阀让支架升起来 */ 
       SetP1Ctrl(AUTO_SCREEN,AUTO_ASQ_INFO,ASQ_SETP1_INFO,GetASQSetP1T()); 
    }
}


/*********************************************************************************************************
** Function name:           Task_ASQCtrl
** Descriptions:            自动移架控制
** input parameters:        pData，
** output parameters:       none
** Returned value:          none
** Created by:              linguofeng 
** Created Date:            2015-05-27
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
void Task_ASQCtrl(void *pData)
{
    
    SCN_RFH_MSG_S stRfhMsg;
    CONTROL_PKT_S stPkt;

    stRfhMsg.eNextScn = ASQ_SCREEN;
    sprintf((char*)stRfhMsg.au8Msg[0],ASQ_INFO);
    sprintf((char*)stRfhMsg.au8Msg[1],ASQ_WARN_INFO);
    sysMsgFlush(gu32ScnRshMsg);
    if (SYS_OK != sysMsgPost(gu32ScnRshMsg,(INT8U *) &stRfhMsg,0))
    {
        ERR_MESSAGE("warning msg post fail");
    }  
    while(1)
    {
        SingleASQCtrl();
        RST_VALVE();
        Jog_Ctrl_StopWarning(stPkt);
        OSTimeDly(OS_TICKS_PER_SEC);
         
        POST_INFO2SCN(stRfhMsg,IDLE_SCREEN,NULL_INFO,NULL_INFO);
        OSTaskDel(OS_PRIO_SELF);
    }
}

static const INT8S * g_cu8BankDisp[MAX_BANK_CTRL_ITEM] = {
    BANK_ADV_MSG,
    BANK_CONV_PUSH_MSG,
    BANK_CONV_PULL_MSG,
    BANK_FLP_1ST_EX_MSG,
    BANK_FLP_1ST_IN_MSG,
    BANK_FNT_CNTLV_EX_MSG,
    BANK_FNT_CNTLV_IN_MSG,
    BANK_PULL_BACK_MSG,
    BANK_SB_EX_MSG,
    BANK_SB_IN_MSG,
    BANK_FLP_2ND_EX_MSG,
    BANK_FLP_2ND_IN_MSG,
    BANK_FLP_LINKAGE_EX_MSG,
    BANK_FLP_LINKAGE_IN_MSG,
    BANK_SB_LINKAGE_EX_MSG,
    BANK_SB_LINKAGE_IN_MSG,
    BANK_SPRAY_MSG,
    BANK_BSPRAY_MSG,
    BANK_ESPRAY_MSG,
    BANK_ASPRAY_MSG,
    BANK_FLP_3RD_EX_MSG,
    BANK_FLP_3RD_IN_MSG,
    BANK_WASHERS_MSG,
    BANK_EXPEND_MSG,
    BANK_RETURN_MSG
};

void Task_BankCtrl(void *pData)
{
    PKT_REFRESH_SCN_S stRefreshPkt = *(PKT_REFRESH_SCN_S*)pData;
    SCN_RFH_MSG_S stRfhMsg;
    INT32S s32Ret = 0;
       
    sysHeapFree(pData);
    sysMsgFlush(gu32BankCtrlMsg);
    /* 执行预警动作，声光报警 */
    /* 人机界面提示执行预警动作的名称*/
    Jog_Ctrl_Warning(stRefreshPkt.stPkt);

    POST_INFO2SCN(stRfhMsg,BANK_CTRL_SCREEN,g_cu8BankDisp[stRefreshPkt.stPkt.u32CmdCode - BATCH_ASQ_CMD],BANK_WARNING_MSG);
    IsEndActShield(&stRefreshPkt);
    s32Ret = tmWrite(stRefreshPkt.stPkt.u8CommDir,0,stRefreshPkt.u32PortAddr,sizeof(CONTROL_PKT_S),(void *) &stRefreshPkt.stPkt,NOT_NEED_ACK);
	if ((s32Ret < 0)&&(RH_PORT_BANK == stRefreshPkt.u32PortAddr))
    {
        /* 物理层断处理 */
        /* 此架作为本次成组动作的末架*/
        stRefreshPkt.stPkt.u8Offset = stRefreshPkt.stPkt.u8NumOper;
        stRefreshPkt.stPkt.u8Area = stRefreshPkt.stPkt.u8SArea - stRefreshPkt.stPkt.u8Area;
        stRefreshPkt.stPkt.u8SArea = stRefreshPkt.stPkt.u8Area;
        NBRCAN_COMM_REP(stRefreshPkt.stPkt.u8CommDir);
        tmWrite(stRefreshPkt.stPkt.u8CommDir,0,RH_PORT_REP_BANK,sizeof(CONTROL_PKT_S),(void *) &stRefreshPkt.stPkt,NOT_NEED_ACK);
    }      
    while(1)
    {
    
		s32Ret = sysMsgPend(gu32BankCtrlMsg,(INT8U *)&stRefreshPkt,0);
		if (SYS_OK != s32Ret)
        {
            SCN_RFH_MSG_S stRfhMsg;
            Jog_Ctrl_StopWarning(stRefreshPkt.stPkt);
            stRfhMsg.eNextScn = IDLE_SCREEN;    
            sysMsgFlush(gu32ScnRshMsg);
            sysMsgPost(gu32ScnRshMsg,(INT8U *)&stRfhMsg,0);  
            OSTaskDel(OS_PRIO_SELF);
        }
        
        /* 执行相应动作 */
        stRefreshPkt.u8PushPop = PUSH_SCN;// linguofeng 15/5/30      
        BankAutoFunc(stRefreshPkt);
		/*动作末架动作指令闭环反馈*/
		if(0 == stRefreshPkt.stPkt.u8Area)
		{
			LastShdActBack(stRefreshPkt.stPkt);
		}        	
        /* 动作执行完毕，删除任务 */
        Jog_Ctrl_StopWarning(stRefreshPkt.stPkt);
        OSTaskDel(OS_PRIO_SELF);        
    }
}

void SetAutoStat(AUTO_CONTEXT_S *pstCtx,AUTO_STATE_S *pstStat)
{
    if ((NULL == pstCtx)||(NULL == pstStat))
    {
        return;
    }
    if (pstCtx->pstCurrStat != pstStat)
    {
        pstStat->pData->u8ASQStat = AUTO_NOTEXECUTE;
        SetPhase3PushStat(FALSE);
        if ((pstStat == &g_astAutoPhase[UP_P5_E])||
            (pstStat == &g_astAutoPhase[DOWN_P5_E]))
        {
            pstStat->pData->u8PushStat = AUTO_NOTEXECUTE;
            pstStat->pData->bP3TransStat = FALSE;
        }
        pstCtx->pstCurrStat = pstStat;                       
    }
}
AUTO_STATE_S * GetAutoStat(AUTO_CONTEXT_S *pstCtx)
{
    if (NULL == pstCtx)
    {
        return NULL;
    }
    return pstCtx->pstCurrStat;
}
#if 0
void UpdateAutoMiningData(AUTO_CONTEXT_S *pstCtx,SHEAR_DIR_E eDir,INT8U u8Pos)
{
    if (NULL == pstCtx)
    {
        return ;
    }
    pstCtx->pstShearData->eShearDir = eDir;
    pstCtx->pstShearData->u8ShearPos = u8Pos;
}
#endif



/*********************************************************************************************************
** Function name:           CheckUpPhase1AutoASQRange
** Descriptions:            检查当前架是否可以执行上行阶段1跟机移架
** input parameters:        pData，
** output parameters:       none
** Returned value:          none
** Created by:              linguofeng 
** Created Date:            2016-03-10
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
static BOOLEAN CheckUpPhase1ASQArea(AUTO_CONTEXT_S *pstCtx,AUTO_PHASE_DATA_S *pstData)
{
    INT8U u8CurrShield = GetCurrShieldNo();
    INT8U u8ShearLenOffset = GetShearLenOffset();
    BOOLEAN bRet = FALSE;
    INT8U u8Offset = GetAutoASQOffset();
    INT8U u8Area = GetAutoASQArea();
    INT8U u8ShearPos = *(pstCtx->pu8ShearPos);
    INT8U u8UpPh1Start = GetDnP4StartShield() + 1;     


    if (( u8CurrShield < u8UpPh1Start)||
        (u8CurrShield > (GetMaxShdNum()-2*u8ShearLenOffset-u8Offset-1))||
        (u8ShearPos == 0))
    {
        return bRet;
    }
        

    /*if ((u8CurrShield < (u8ShearPos-u8ShearLenOffset-u8Offset))&&
        (u8CurrShield >= (u8ShearPos-u8ShearLenOffset-u8Offset - u8Area)))*/
    if ((((INT16U)u8CurrShield + u8ShearLenOffset+ u8Offset) < u8ShearPos)&&
        (((INT16U)u8CurrShield + u8ShearLenOffset+u8Offset+u8Area ) >= u8ShearPos))    
    {
        bRet = TRUE;
    }
    return bRet;
}
/*********************************************************************************************************
** Function name:           CheckUpPhase1PushRange
** Descriptions:            检查当前架是否可以执行上行阶段1跟机推溜
** input parameters:        pData，
** output parameters:       none
** Returned value:          none
** Created by:              linguofeng 
** Created Date:            2016-03-10
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
static BOOLEAN CheckUpPhase1PushArea(AUTO_CONTEXT_S *pstCtx,AUTO_PHASE_DATA_S *pstData)
{
    INT8U u8CurrShield = GetCurrShieldNo();
    INT8U u8ShearLenOffset = GetShearLenOffset();
    BOOLEAN bRet = FALSE;
    INT8U u8Offset = GetAutoPushOffset();
    INT8U u8Area = GetAutoPushArea();
    INT8U u8ShearPos = *(pstCtx->pu8ShearPos);
    //INT8U u8UpP1Pos = GetMinShdNum()+3*u8ShearLenOffset+2*GetAutoASQOffset()+2;

    if (u8ShearPos == 0)
    {
        return bRet;
    }
    /*if ((u8CurrShield < (u8ShearPos - u8ShearLenOffset-u8Offset))&&
        (u8CurrShield > (u8ShearPos - u8ShearLenOffset-u8Offset-u8Area)))*/
    if ((((INT16U)u8CurrShield+u8ShearLenOffset+u8Offset) < u8ShearPos)&&
        (((INT16U)u8CurrShield+u8ShearLenOffset+u8Offset+u8Area) > u8ShearPos))    
    {
        bRet = TRUE;
    }
    return bRet;
}
static BOOLEAN CheckUpPhase2ASQArea(AUTO_CONTEXT_S *pstCtx,AUTO_PHASE_DATA_S *pstData)
{
    INT8U u8CurrShield = GetCurrShieldNo();
    INT8U u8MaxShield = GetMaxShdNum();
    INT8U u8ShearLenOffset = GetShearLenOffset();
    BOOLEAN bRet = FALSE;
    INT8U  u8Area= GetAutoASQArea();
    INT8U  u8Offset= GetAutoASQOffset();
    INT8U u8ShearPos = *(pstCtx->pu8ShearPos);

    if ((u8CurrShield < (u8MaxShield-u8ShearLenOffset-u8ShearLenOffset-u8Offset))
        ||(u8CurrShield > u8MaxShield)||(u8ShearPos == 0))
    {
        return bRet;
    }

    if (u8CurrShield > ((INT16U)u8ShearPos + u8ShearLenOffset+u8Offset)&&
        (u8CurrShield <= ((INT16U)u8ShearPos +u8ShearLenOffset +u8Offset +u8Area)))
    {
        bRet = TRUE;
    }
    return bRet;
}
/*********************************************************************************************************
** Function name:           GetPhase3StartShield
** Descriptions:            获取上下行阶段3首架推溜架号
** input parameters:        pData，
** output parameters:       none
** Returned value:          none
** Created by:              linguofeng 
** Created Date:            2016-03-10
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
static INT8U GetPhase3StartShield(void)
{
   INT8U u8AutoDir = GetAutoDir();
   INT8U u8Ret = 0;
   INT8U u8ShearLenOffset = GetShearLenOffset();
   if (u8AutoDir == AUTO_DIR_UP)
   {
        u8Ret = GetAutoUpSnakeMin()+u8ShearLenOffset+GetAutoPhase3Offset();
   }
   else if (u8AutoDir == AUTO_DIR_DOWN)
   {
        u8Ret = GetAutoDownSnakeMax()-u8ShearLenOffset-GetAutoPhase3Offset();
   }
   else
   {

   }
   return u8Ret;
}
static BOOLEAN CheckUpPhase3PushArea(AUTO_CONTEXT_S *pstCtx,AUTO_PHASE_DATA_S *pstData)
{
    INT8U u8CurrShield = GetCurrShieldNo();
    BOOLEAN bRet = FALSE;
    INT8U u8ShearPos = *(pstCtx->pu8ShearPos);
    
    if ((u8ShearPos == 0)||(u8ShearPos > GetAutoUpSnakeMin()))
    {
        return bRet;
    }
    /* 阶段三成组推溜的触发架 */
    if ((u8CurrShield == GetPhase3StartShield())||
        (GetPhase3PushStat()))       
    {
        bRet = TRUE;
    }

    return bRet;
}
static BOOLEAN CheckUpPhase4ASQArea(AUTO_CONTEXT_S *pstCtx,AUTO_PHASE_DATA_S *pstData)
{
    INT8U u8CurrShield = GetCurrShieldNo();
    INT8U u8Offset = GetAutoASQOffset();
    INT8U u8Area = GetAutoASQArea();
    INT8U u8ShearLenOffset = GetShearLenOffset();
    BOOLEAN bRet = FALSE;

    INT8U u8ShearPos = *(pstCtx->pu8ShearPos);
    INT8U u8UpP4Pos = GetAutoUpSnakeMin() - u8ShearLenOffset + GetAutoPhase4Offset();

    if ((u8CurrShield < u8UpP4Pos)||
        (u8CurrShield > (GetMaxShdNum()-2*u8ShearLenOffset-u8Offset-1))||
        (u8ShearPos == 0))
    {
        return bRet;
    }

    /*if ((u8CurrShield < (u8ShearPos-u8ShearLenOffset-u8Offset))&&
        (u8CurrShield >= (u8ShearPos-u8ShearLenOffset-u8Offset - u8Area)))*/
    if ((((INT16U)u8CurrShield+u8ShearLenOffset+u8Offset) < u8ShearPos)&&
        (((INT16U)u8CurrShield+u8ShearLenOffset+u8Offset+u8Area) >= u8ShearPos))
    {
        bRet = TRUE;
    }    
    return bRet;
}
static BOOLEAN CheckUpPhase5ASQArea(AUTO_CONTEXT_S *pstCtx,AUTO_PHASE_DATA_S *pstData)
{
    return CheckUpPhase2ASQArea(pstCtx,pstData);    
}
static BOOLEAN CheckUpPhase5PushArea(AUTO_CONTEXT_S *pstCtx,AUTO_PHASE_DATA_S *pstData)
{
    INT8U u8CurrShield = GetCurrShieldNo();
    INT8U u8Offset = GetAutoPushOffset();
    INT8U u8Area = GetAutoPushArea();
    INT8U u8ShearLenOffset = GetShearLenOffset();
    BOOLEAN bRet = FALSE;
    INT8U u8ShearPos = *(pstCtx->pu8ShearPos);
    //INT8U u8DnP1Pos = GetMaxShdNum()-3*u8ShearLenOffset-2*GetAutoASQOffset()-2;

    if (u8ShearPos == 0)
    {
        return bRet;
    }

    if ((u8CurrShield > ((INT16U)u8ShearPos + u8ShearLenOffset + u8Offset))&&
        (u8CurrShield <= ((INT16U)u8ShearPos + u8ShearLenOffset + u8Offset+u8Area)))
    {
        bRet = TRUE;
    }
    return bRet;
}
static BOOLEAN CheckDnPhase1ASQArea(AUTO_CONTEXT_S *pstCtx,AUTO_PHASE_DATA_S *pstData)
{
    INT8U u8CurrShield = GetCurrShieldNo();
    INT8U u8ShearLenOffset = GetShearLenOffset();
    BOOLEAN bRet = FALSE;
    INT8U u8Offset = GetAutoASQOffset();
    INT8U u8Area = GetAutoASQArea();
    INT8U u8ShearPos = *(pstCtx->pu8ShearPos);
    INT8U u8DnPh1Start = GetAutoUpSnakeMin() + GetAutoPhase4Offset()- GetShearLenOffset() -1;    


    if (( u8CurrShield > u8DnPh1Start)||
        (u8CurrShield < (GetMinShdNum()+2*u8ShearLenOffset+u8Offset+1))||
        (u8ShearPos == 0))
    {
        return bRet;
    }
        

    if ((u8CurrShield > ((INT16U)u8ShearPos+u8ShearLenOffset+u8Offset))&&
        (u8CurrShield <= ((INT16U)u8ShearPos+u8ShearLenOffset+u8Offset + u8Area)))
    {
        bRet = TRUE;
    }
    return bRet;
}

static BOOLEAN CheckDnPhase1PushArea(AUTO_CONTEXT_S *pstCtx,AUTO_PHASE_DATA_S *pstData)
{
    INT8U u8CurrShield = GetCurrShieldNo();
    INT8U u8ShearLenOffset = GetShearLenOffset();
    BOOLEAN bRet = FALSE;
    INT8U u8Offset = GetAutoPushOffset();
    INT8U u8Area = GetAutoPushArea();
    INT8U u8ShearPos = *(pstCtx->pu8ShearPos);
    //INT8U u8DnP1Pos = GetMaxShdNum()-3*u8ShearLenOffset-2*GetAutoASQOffset()-2;
    

    if (u8ShearPos == 0)
    {
        return bRet;
    }

    if ((u8CurrShield > ((INT16U)u8ShearPos + u8ShearLenOffset+u8Offset))&&
        (u8CurrShield <= ((INT16U)u8ShearPos + u8ShearLenOffset+u8Offset+u8Area)))
    {
        bRet = TRUE;
    }
    return bRet;
}

static BOOLEAN CheckDnPhase2ASQArea(AUTO_CONTEXT_S *pstCtx,AUTO_PHASE_DATA_S *pstData)
{
    INT8U u8CurrShield = GetCurrShieldNo();
    INT8U u8MinShield = GetMinShdNum();
    INT8U u8ShearLenOffset = GetShearLenOffset();
    BOOLEAN bRet = FALSE;
    INT8U u8Offset = GetAutoASQOffset();
    INT8U u8Area = GetAutoASQArea();
    INT8U u8ShearPos = *(pstCtx->pu8ShearPos);

    if ((u8CurrShield > ((INT16U)u8MinShield+u8ShearLenOffset+u8ShearLenOffset+u8Offset))||
        (u8CurrShield < GetMinShdNum())||
        (u8ShearPos == 0))
    {
        return bRet;
    }

    if ((((INT16U)u8CurrShield+u8ShearLenOffset+u8Offset ) < u8ShearPos)&&
        (((INT16U)u8CurrShield+u8ShearLenOffset+u8Offset+u8Area) >= u8ShearPos))
    {
        bRet = TRUE;
    }
    return bRet;
}

static BOOLEAN CheckDnPhase3PushArea(AUTO_CONTEXT_S *pstCtx,AUTO_PHASE_DATA_S *pstData)
{
    INT8U u8CurrShield = GetCurrShieldNo();
    BOOLEAN bRet = FALSE;
    
    INT8U u8ShearPos = *(pstCtx->pu8ShearPos);
    
    if ((u8ShearPos == 0)||(u8ShearPos < GetAutoDownSnakeMax()))
    {
        return bRet;
    }

    /* 阶段三成组推溜的触发架 */
    if ((u8CurrShield == GetPhase3StartShield())||
        (GetPhase3PushStat()))
    {
         bRet = TRUE;
    }
    return bRet;
}

static BOOLEAN CheckDnPhase4ASQArea(AUTO_CONTEXT_S *pstCtx,AUTO_PHASE_DATA_S *pstData)
{
    INT8U u8CurrShield = GetCurrShieldNo();
    INT8U u8Offset = GetAutoASQOffset();
    INT8U u8Area = GetAutoASQArea();
    INT8U u8ShearLenOffset = GetShearLenOffset();
    BOOLEAN bRet = FALSE;

    INT8U u8ShearPos = *(pstCtx->pu8ShearPos);
    INT8U u8DnP4Pos = GetAutoDownSnakeMax() +u8ShearLenOffset - GetAutoPhase4Offset();

    if ((u8CurrShield > u8DnP4Pos)||
        (u8CurrShield < (GetMinShdNum()+2*u8ShearLenOffset+u8Offset+1))||
        (u8ShearPos == 0))
    {
        return bRet;
    }

    if ((u8CurrShield > ((INT16U)u8ShearPos+u8ShearLenOffset+u8Offset))&&
        (u8CurrShield <= ((INT16U)u8ShearPos+u8ShearLenOffset+u8Offset + u8Area)))
    {
        bRet = TRUE;
    }    
    return bRet;
}

static BOOLEAN CheckDnPhase5ASQArea(AUTO_CONTEXT_S *pstCtx,AUTO_PHASE_DATA_S *pstData)
{
    return CheckDnPhase2ASQArea(pstCtx,pstData);    
}

static BOOLEAN CheckDnPhase5PushArea(AUTO_CONTEXT_S *pstCtx,AUTO_PHASE_DATA_S *pstData)
{
    INT8U u8CurrShield = GetCurrShieldNo();

    INT8U u8Offset = GetAutoPushOffset();
    INT8U u8Area = GetAutoPushArea();
    INT8U u8ShearLenOffset = GetShearLenOffset();
    BOOLEAN bRet = FALSE;
    INT8U u8ShearPos = *(pstCtx->pu8ShearPos);
    //INT8U u8UpP1Pos = GetMinShdNum()+3*u8ShearLenOffset+2*GetAutoASQOffset()+2;
    
    if (u8ShearPos == 0)
    {
        return bRet;
    }

    if ((((INT16U)u8CurrShield+u8ShearLenOffset+u8Offset) < u8ShearPos)&&
        (((INT16U)u8CurrShield+u8ShearLenOffset+u8Offset+u8Area) >= u8ShearPos))
    {
        bRet = TRUE;
    }
    return bRet;
}
static BOOLEAN CheckMoveUpFlipIn(AUTO_CONTEXT_S *pstCtx,AUTO_PHASE_DATA_S *pstData)
{
    INT8U u8ShearPos = *(pstCtx->pu8ShearPos);
    INT8U u8CurrShield = GetCurrShieldNo();
    INT8U u8ShearLenOffset = GetShearLenOffset();
    INT8U u8FlipOffset = GetAutoFlipInOffset();
    INT8U u8FlipArea = GetAutoFlipInArea();
    INT8U u8FlipExOffset = GetAutoFlipExOffset();
    INT8U u8PushArea = GetAutoPushArea();
    INT8U u8PushOffset = GetAutoPushOffset();
    INT8U u8ASQArea = GetAutoASQArea();
    INT8U u8ASQOffset = GetAutoASQOffset();
    INT16U u16MaxOffset = (INT16U)u8ShearLenOffset+(INT16U)u8FlipOffset+(INT16U)u8FlipArea;
    INT16U u16MinOffset = (INT16U)u8FlipExOffset+(INT16U)u8PushArea+(INT16U)u8PushOffset+ \
                          (INT16U)u8ASQArea+(INT16U)u8ASQOffset+(INT16U)u8ShearLenOffset;
    BOOLEAN bRet = FALSE;

    if ((u8CurrShield <= (u8ShearPos + u16MaxOffset))&&
        ((u8CurrShield + u16MinOffset) >= u8ShearPos))
    {
        bRet = TRUE;
    }
    return bRet;
}

static BOOLEAN CheckMoveUpFlipEx(AUTO_CONTEXT_S *pstCtx,AUTO_PHASE_DATA_S *pstData)
{
    INT8U u8ShearPos = *(pstCtx->pu8ShearPos);
    INT8U u8CurrShield = GetCurrShieldNo();
    INT8U u8ShearLenOffset = GetShearLenOffset();
    INT8U u8FlipExOffset = GetAutoFlipExOffset();
    INT8U u8FlipExArea = GetAutoFlipExArea();
    INT8U u8PushArea = GetAutoPushArea();
    INT8U u8PushOffset = GetAutoPushOffset();
    INT8U u8ASQArea = GetAutoASQArea();
    INT8U u8ASQOffset = GetAutoASQOffset();
    INT16U u16MinOffset = (INT16U)u8FlipExOffset+(INT16U)u8PushArea+(INT16U)u8PushOffset+ \
                          (INT16U)u8ASQArea+(INT16U)u8ASQOffset+(INT16U)u8ShearLenOffset;
    INT16U u16MaxOffset = u16MinOffset + u8FlipExArea;
    BOOLEAN bRet = FALSE;

    if (((u8CurrShield + u16MaxOffset) >= u8ShearPos)&&
        ((u8CurrShield + u16MinOffset) < u8ShearPos))
    {
        bRet = TRUE;
    }
    return bRet;
}

static BOOLEAN CheckMoveDnFlipIn(AUTO_CONTEXT_S *pstCtx,AUTO_PHASE_DATA_S *pstData)
{
    INT8U u8ShearPos = *(pstCtx->pu8ShearPos);
    INT8U u8CurrShield = GetCurrShieldNo();
    INT8U u8ShearLenOffset = GetShearLenOffset();
    INT8U u8FlipOffset = GetAutoFlipInOffset();
    INT8U u8FlipArea = GetAutoFlipInArea();
    INT8U u8FlipExOffset = GetAutoFlipExOffset();
    INT8U u8PushArea = GetAutoPushArea();
    INT8U u8PushOffset = GetAutoPushOffset();
    INT8U u8ASQArea = GetAutoASQArea();
    INT8U u8ASQOffset = GetAutoASQOffset();
    BOOLEAN bRet = FALSE;
    INT16U u16MinOffset = (INT16U)u8ShearLenOffset + (INT16U)u8FlipArea +(INT16U)u8FlipOffset;
    INT16U u16MaxOffset = (INT16U)u8ShearLenOffset + (INT16U)u8ASQArea + (INT16U)u8ASQOffset + \
                          (INT16U)u8PushArea + (INT16U)u8PushOffset+(INT16U)u8FlipExOffset;
    if (((u8CurrShield + u16MinOffset) >= u8ShearPos)&&
        (u8CurrShield <= (u8ShearPos + u16MaxOffset)))
    {
        bRet = TRUE;
    }
    
    return bRet;
}

static BOOLEAN CheckMoveDnFlipEx(AUTO_CONTEXT_S *pstCtx,AUTO_PHASE_DATA_S *pstData)
{
    INT8U u8ShearPos = *(pstCtx->pu8ShearPos);
    INT8U u8CurrShield = GetCurrShieldNo();
    INT8U u8ShearLenOffset = GetShearLenOffset();
    //INT8U u8FlipOffset = GetAutoFlipInOffset();
    //INT8U u8FlipArea = GetAutoFlipInArea();
    INT8U u8FlipExOffset = GetAutoFlipExOffset();
    INT8U u8FlipExArea = GetAutoFlipExArea();
    INT8U u8PushArea = GetAutoPushArea();
    INT8U u8PushOffset = GetAutoPushOffset();
    INT8U u8ASQArea = GetAutoASQArea();
    INT8U u8ASQOffset = GetAutoASQOffset();
    BOOLEAN bRet = FALSE;
    INT16U u16MinOffset = (INT16U)u8ShearLenOffset +(INT16U)u8ASQArea+(INT16U)u8ASQOffset+\
                          (INT16U)u8PushArea +(INT16U)u8PushOffset+(INT16U)u8FlipExOffset;
    INT16U u16MaxOffset = u16MinOffset + u8FlipExArea;
    if ((u8CurrShield > (u8ShearPos + u16MinOffset))&&
        (u8CurrShield <= (u8ShearPos +u16MaxOffset)))
    {
        bRet = TRUE;
    }
    return bRet;
}

/*********************************************************************************************************
** Function name:           CheckUpP1FlipEx
** Descriptions:            上行阶段1伸护帮范围检查，检查当前架是否在伸护帮范围内
** input parameters:       
** output parameters:       none
** Returned value:          
** Created by:              linguofeng 
** Created Date:            2016-5-20
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
static BOOLEAN CheckUpP1FlipEx(AUTO_CONTEXT_S *pstCtx,AUTO_PHASE_DATA_S *pstData)
{
    return CheckMoveUpFlipEx(pstCtx,pstData);
}
/*********************************************************************************************************
** Function name:           CheckUpP1FlipIn
** Descriptions:            上行阶段1收护帮范围检查，检查当前架是否在收护帮范围内
** input parameters:       
** output parameters:       none
** Returned value:          
** Created by:              linguofeng 
** Created Date:            2016-5-20
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
static BOOLEAN CheckUpP1FlipIn(AUTO_CONTEXT_S *pstCtx,AUTO_PHASE_DATA_S *pstData)
{
    return CheckMoveUpFlipIn(pstCtx,pstData);
}

static BOOLEAN CheckUpP2FlipEx(AUTO_CONTEXT_S *pstCtx,AUTO_PHASE_DATA_S *pstData)
{
    return CheckMoveDnFlipEx(pstCtx,pstData);
}
static BOOLEAN CheckUpP2FlipIn(AUTO_CONTEXT_S *pstCtx,AUTO_PHASE_DATA_S *pstData)
{
    return CheckMoveDnFlipIn(pstCtx, pstData);
}
static BOOLEAN CheckUpP3FlipEx(AUTO_CONTEXT_S *pstCtx,AUTO_PHASE_DATA_S *pstData)
{
    return CheckMoveDnFlipEx(pstCtx, pstData);
}
static BOOLEAN CheckUpP3FlipIn(AUTO_CONTEXT_S *pstCtx,AUTO_PHASE_DATA_S *pstData)
{
    return CheckMoveDnFlipIn(pstCtx,pstData);
}
static BOOLEAN CheckUpP4FlipEx(AUTO_CONTEXT_S *pstCtx,AUTO_PHASE_DATA_S *pstData)
{
    return CheckMoveUpFlipEx(pstCtx,pstData);
}
static BOOLEAN CheckUpP4FlipIn(AUTO_CONTEXT_S *pstCtx,AUTO_PHASE_DATA_S *pstData)
{
    return CheckMoveUpFlipIn(pstCtx, pstData);
}
static BOOLEAN CheckUpP5FlipEx(AUTO_CONTEXT_S *pstCtx,AUTO_PHASE_DATA_S *pstData)
{
    return CheckMoveDnFlipEx( pstCtx, pstData);
}
static BOOLEAN CheckUpP5FlipIn(AUTO_CONTEXT_S *pstCtx,AUTO_PHASE_DATA_S *pstData)
{
    return CheckMoveDnFlipIn(pstCtx, pstData);
}
static BOOLEAN CheckDnP1FlipEx(AUTO_CONTEXT_S *pstCtx,AUTO_PHASE_DATA_S *pstData)
{
    return CheckMoveDnFlipEx( pstCtx, pstData);
}
static BOOLEAN CheckDnP1FlipIn(AUTO_CONTEXT_S *pstCtx,AUTO_PHASE_DATA_S *pstData)
{
    return CheckMoveDnFlipIn(pstCtx, pstData);
}
static BOOLEAN CheckDnP2FlipEx(AUTO_CONTEXT_S *pstCtx,AUTO_PHASE_DATA_S *pstData)
{
    return CheckMoveUpFlipEx( pstCtx, pstData);
}
static BOOLEAN CheckDnP2FlipIn(AUTO_CONTEXT_S *pstCtx,AUTO_PHASE_DATA_S *pstData)
{
    return CheckMoveUpFlipIn( pstCtx, pstData);
}
static BOOLEAN CheckDnP3FlipEx(AUTO_CONTEXT_S *pstCtx,AUTO_PHASE_DATA_S *pstData)
{
    return CheckMoveUpFlipEx(pstCtx, pstData);
}
static BOOLEAN CheckDnP3FlipIn(AUTO_CONTEXT_S *pstCtx,AUTO_PHASE_DATA_S *pstData)
{
    return CheckMoveUpFlipIn( pstCtx, pstData);
}

static BOOLEAN CheckDnP4FlipEx(AUTO_CONTEXT_S *pstCtx,AUTO_PHASE_DATA_S *pstData)
{
    return CheckMoveDnFlipEx( pstCtx, pstData);
}
static BOOLEAN CheckDnP4FlipIn(AUTO_CONTEXT_S *pstCtx,AUTO_PHASE_DATA_S *pstData)
{
    return CheckMoveDnFlipIn( pstCtx, pstData);
}
static BOOLEAN CheckDnP5FlipEx(AUTO_CONTEXT_S *pstCtx,AUTO_PHASE_DATA_S *pstData)
{
    return CheckMoveUpFlipEx( pstCtx, pstData);
}
static BOOLEAN CheckDnP5FlipIn(AUTO_CONTEXT_S *pstCtx,AUTO_PHASE_DATA_S *pstData)
{
    return CheckMoveUpFlipIn( pstCtx, pstData);
}

static void ASQBehindShearerCtrl(AUTO_CONTEXT_S *pstCtx,AUTO_PHASE_DATA_S *pstData)
{
    SCN_RFH_MSG_S stRfhMsg;
    CONTROL_PKT_S stPkt;

    if (AUTO_EXECUTED == pstData->u8ASQStat)
    {
        return;
    }
    if (!pstCtx->pstCurrStat->pfASQCheck(pstCtx,pstData))
    {
        return;
    }
    pstData->u8ASQStat = AUTO_EXECUTED;

    POST_INFO2SCN(stRfhMsg,AUTO_SCREEN,AUTOMINING_INFO,pstData->pAsqDispStr); 

    Jog_Ctrl_Warning( stPkt);
    AutoASQCtrl();
    RST_VALVE();
    Jog_Ctrl_StopWarning(stPkt);
     
    POST_INFO2SCN(stRfhMsg,IDLE_SCREEN,NULL_INFO,NULL_INFO);    
}


static void BankPushBehindShearerCtrl(AUTO_CONTEXT_S *pstCtx,AUTO_PHASE_DATA_S *pstData)
{
    CONTROL_PKT_S stPkt;
    INT32U u32Valve = 0;
    SCN_RFH_MSG_S stRfhMsg;
    
    if (AUTO_EXECUTED == pstData->u8PushStat)
    {
        return;
    }
    
    if (!pstCtx->pstCurrStat->pfPushCheck(pstCtx,pstData))
    {
        return;
    }  
    pstData->u8PushStat = AUTO_EXECUTED;
    
    POST_INFO2SCN(stRfhMsg,AUTO_SCREEN,AUTOMINING_INFO,pstData->pPushDispStr); 
    
    VALVE_TBL(u32Valve,SHIELD_POS,PUSH_CONVEYOR_CMD);
    SET_VALVE(u32Valve);
    Jog_Ctrl_Warning( stPkt);
    
    SetLPushCtrlTime(SEC_TIMER);
    
}
#if 0
/*********************************************************************************************************
** Function name:           CheckAutoFlipInArea
** Descriptions:            判断当前架是否在收侧护范围内
** input parameters:       
** output parameters:       none
** Returned value:          
** Created by:              linguofeng 
** Created Date:            2016-3-24
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
static BOOLEAN CheckAutoFlipInArea(INT8U u8ShearPos)
{
    INT8U u8CurrShield = GetShieldNum();
    INT8U u8InArea = GetAutoFlipInArea();
    INT8U u8ShearlenOffset = GetShearLenOffset();
    BOOLEAN bRet = FALSE;
    if (0 == u8ShearPos)
    {
        return bRet;
    }
    if ((u8CurrShield <= ((INT32U)u8ShearPos + u8ShearlenOffset + u8InArea))&&
        (((INT32U)u8CurrShield + u8ShearlenOffset + u8InArea) >= u8ShearPos)) 
    {
        bRet = TRUE;
    }
    return bRet;
}
/*********************************************************************************************************
** Function name:           CheckAutoFlipExArea
** Descriptions:            判断当前架是否在伸侧护范围内
** input parameters:       
** output parameters:       none
** Returned value:          
** Created by:              linguofeng 
** Created Date:            2016-03-24
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
static BOOLEAN CheckAutoFlipExArea(INT8U u8ShearPos)
{
    INT8U u8CurrShield = GetShieldNum();
    INT8U u8InArea = GetAutoFlipInArea();
    INT8U u8ExArea = GetAutoFlipExArea();
    INT8U u8ShearlenOffset = GetShearLenOffset();
    BOOLEAN bRet = FALSE;
    if (0 == u8ShearPos)
    {
        return bRet;
    }

    if ((u8CurrShield <= ((INT32U)u8ShearPos + u8ShearlenOffset + u8InArea + u8ExArea))&&
        (((INT32U)u8CurrShield + u8ShearlenOffset + u8InArea + u8ExArea) >= u8ShearPos))
    {
        if (!CheckAutoFlipInArea(u8ShearPos))
        {
            bRet = TRUE;
        }
    }
    return bRet;
}
#endif
static void AuxiFlipInCtrl(AUTO_CONTEXT_S *pstCtx,AUTO_PHASE_DATA_S *pstData)
{
    CONTROL_PKT_S stPkt;
    SCN_RFH_MSG_S stRfhMsg;
    INT32U u32Valve = 0;
    /* 收护帮 */
    if (AUTO_EXECUTED == pstData->u8FlipInStat)
    {
        return;
    }
    if (!pstCtx->pstCurrStat->pfFlipInCheck(pstCtx,pstData))
    {
        return;
    }
    pstData->u8FlipInStat = AUTO_EXECUTED;
    pstData->u8FlipExStat = AUTO_NOTEXECUTE;
    
    POST_INFO2SCN(stRfhMsg,AUTO_SCREEN,AUTOFLIP_INFO,AUTOFLIPIN_INFO); 

    Jog_Ctrl_Warning( stPkt);    
    VALVE_TBL(u32Valve,SHIELD_POS,FST_FLIP_IN_CMD);
    SET_VALVE(u32Valve);    
    AutoMiningDly(GetAutoFlipInT());
    CLR_VALVE(u32Valve);
    Jog_Ctrl_StopWarning(stPkt);
     
    POST_INFO2SCN(stRfhMsg,IDLE_SCREEN,NULL_INFO,NULL_INFO);     
}

static void AuxiFlipExCtrl(AUTO_CONTEXT_S *pstCtx,AUTO_PHASE_DATA_S *pstData)
{
    //INT8U u8ShearPos = *(pstCtx->pu8ShearPos);
    CONTROL_PKT_S stPkt;
    SCN_RFH_MSG_S stRfhMsg;
    INT32U u32Valve = 0;

    /* 伸护帮 */
    if (AUTO_EXECUTED == pstData->u8FlipExStat)
    {
        return;
    }
    if (!pstCtx->pstCurrStat->pfFlipExCheck(pstCtx,pstData))
    {
        return;
    }
    pstData->u8FlipExStat = AUTO_EXECUTED;
    pstData->u8FlipInStat = AUTO_NOTEXECUTE;

    POST_INFO2SCN(stRfhMsg,AUTO_SCREEN,AUTOFLIP_INFO,AUTOFLIPEX_INFO); 

    Jog_Ctrl_Warning( stPkt);    
    VALVE_TBL(u32Valve,SHIELD_POS,FST_FLIP_OUT_CMD);
    SET_VALVE(u32Valve);    
    AutoMiningDly(GetAutoFlipExT());
    CLR_VALVE(u32Valve);
    Jog_Ctrl_StopWarning(stPkt);
     
    POST_INFO2SCN(stRfhMsg,IDLE_SCREEN,NULL_INFO,NULL_INFO);    
}

static void AutoFlipDataInit(AUTO_CONTEXT_S *pstCtx,AUTO_PHASE_DATA_S *pstData)
{
    //INT8U u8ShieldPos = *(pstCtx->pu8ShearPos);
    
    if (pstCtx->pstCurrStat->pfFlipInCheck(pstCtx,pstData))
    {
        pstData->u8FlipInStat = AUTO_EXECUTED;
        pstData->u8FlipExStat = AUTO_NOTEXECUTE;
    }
    else
    {
        pstData->u8FlipExStat = AUTO_EXECUTED;
        pstData->u8FlipInStat = AUTO_NOTEXECUTE;
    }
}



/*
上行正常跟机移架
*/
void AutoPhase1Dispense(AUTO_CONTEXT_S *pstCtx,AUTO_PHASE_DATA_S *pstData)
{   
       
    INT8U u8AutoDir = GetAutoDir();   
    if (GetAutoAdvEn())
    {
        pstData->pAsqDispStr = (u8AutoDir == AUTO_DIR_UP) ?  UPPHASE1_INFO : DNPHASE1_INFO;
        ASQBehindShearerCtrl(pstCtx,pstData);
    }
    if(GetAutoConvEn())
    {
        pstData->pPushDispStr = (u8AutoDir == AUTO_DIR_UP) ?  UPPHASE1PUSH_INFO : DNPHASE1PUSH_INFO;
        BankPushBehindShearerCtrl(pstCtx,pstData);
    }
}



/* 
上下行折返端头跟机移架
*/
 
void AutoPhase2Dispense(AUTO_CONTEXT_S *pstCtx,AUTO_PHASE_DATA_S *pstData)
{
    
    INT8U u8AutoDir = GetAutoDir();
    if (GetAutoAdvEn())
    {
        pstData->pAsqDispStr = (u8AutoDir == AUTO_DIR_UP) ?  UPPHASE2_INFO : DNPHASE2_INFO;
        ASQBehindShearerCtrl(pstCtx,pstData);
    }
}
/*
上下行跟机转换为邻架通信方向
上行定义:采煤机中部正常割煤时向架号增大方向运行为上行
此接口在上行取值是1，下行取值是2；左向地址增向是1，右向地址增向是0的前提下使用
*/
static INT8U ConvertWorkDir2CommDir(INT32S s32WorkDir)
{
    INT8U u8Ret = 0xff;
    BOOLEAN bAddrDir = GetShieldAddrDir();
    INT8U u8Xor = 0;
    u8Xor = (INT8U)(bAddrDir^(s32WorkDir-AUTO_DIR_UP));
    
    if ((s32WorkDir>2)||(s32WorkDir==0))
    {
        ERR_MESSAGE("ConvertWorkDir err");
        return u8Ret;
    }
    if (u8Xor == 0)
    {
        u8Ret = CAN_RIGHT;
    }
    else
    {
        u8Ret = CAN_LEFT;
    }
   
    
    return u8Ret;
}
/*********************************************************************************************************
** Function name:           AutoP3TransPushCmd
** Descriptions:            跟机阶段3传递推溜命令到下一支架
** input parameters:        u8Dir,传递方向，pstData 控制信息
** output parameters:       none
** Returned value:          
** Created by:              linguofeng 
** Created Date:            2016-03-23
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
static void AutoP3TransPushCmd(INT8U u8Dir,AUTO_PHASE_DATA_S *pstData)
{
    if (pstData->bP3TransStat)
    {
        return;
    }
    if ((GetShieldNum() == GetMaxShdNum())||
        (GetShieldNum() == GetMinShdNum()))
    {
        return;
    }
    if (((AUTO_DIR_UP == GetAutoDir())&&(GetShieldNum() < GetPhase3StartShield()))||
        ((AUTO_DIR_DOWN == GetAutoDir()&&(GetShieldNum() > GetPhase3StartShield()))))
    {
        return;
    }
    tmWrite(u8Dir,0, RH_PORT_AUTOP3, sizeof(INT8U),(void*)&u8Dir, NOT_NEED_ACK);  
    pstData->bP3TransStat = TRUE;
         
    
}

void AutoPhase3Dispense(AUTO_CONTEXT_S *pstCtx,AUTO_PHASE_DATA_S *pstData)
{
    CONTROL_PKT_S stPkt;
    SCN_RFH_MSG_S stRfhMsg;
    char *pmsg= NULL;
    INT8U u8Dir = 0;
    INT32U u32Valve = 0;
    if(!GetAutoConvEn())
    {
        //ERR_MESSAGE("跟机推溜禁止");
        return;
    }
    u8Dir = ConvertWorkDir2CommDir(GetAutoDir());
    
    if (pstData->u8PushStat == AUTO_EXECUTED)
    {
        AutoP3TransPushCmd(u8Dir,pstData);  
        //ERR_MESSAGE("执行过阶3推溜");
        return ;
    }    
    if (!pstCtx->pstCurrStat->pfPushCheck(pstCtx,pstData))
    {
       // ERR_MESSAGE("非阶3推溜首架");
        return;
    }
    

    pstData->u8PushStat = AUTO_EXECUTED;
    SetPhase3PushStat(FALSE);
    pmsg = (GetAutoDir() == AUTO_DIR_UP) ?  UPPHASE3_INFO : DNPHASE3_INFO;
    POST_INFO2SCN(stRfhMsg,AUTO_SCREEN,pmsg,AUTOMINING_INFO);
    Jog_Ctrl_Warning( stPkt);
    
    VALVE_TBL(u32Valve,SHIELD_POS,PUSH_CONVEYOR_CMD);
    SET_VALVE(u32Valve);   
    SetLPushCtrlTime(SEC_TIMER);
    
    if (AutoMiningDly(GetAutoBackup3()))
    {
        //ERR_MESSAGE("急停闭锁被按下");
        return;
    }
    AutoP3TransPushCmd(u8Dir,pstData); 


}



/*
上行折返后再次折返到达端头的跟机移架
*/
void AutoPhase4Dispense(AUTO_CONTEXT_S *pstCtx,AUTO_PHASE_DATA_S *pstData)
{
    
    INT8U u8AutoDir = GetAutoDir();

    if (GetAutoAdvEn())
    {
        pstData->pAsqDispStr = (u8AutoDir == AUTO_DIR_UP) ?  UPPHASE4_INFO : DNPHASE4_INFO;
        ASQBehindShearerCtrl(pstCtx,pstData);
    }
}
/*
最大架号到阶段4未移架的支架的 跟机移架
*/
void AutoPhase5Dispense(AUTO_CONTEXT_S *pstCtx,AUTO_PHASE_DATA_S *pstData)
{
    INT8U u8AutoDir = GetAutoDir();

    if (GetAutoAdvEn())
    {
        pstData->pAsqDispStr = (u8AutoDir == AUTO_DIR_UP) ?  UPPHASE5_INFO : DNPHASE5_INFO;
        ASQBehindShearerCtrl(pstCtx,pstData);
    }
    if(GetAutoConvEn())
    {
        pstData->pPushDispStr = (u8AutoDir == AUTO_DIR_UP) ?  UPPHASE5PUSH_INFO : DNPHASE5PUSH_INFO;
        BankPushBehindShearerCtrl(pstCtx,pstData);
    }
}
/*********************************************************************************************************
** Function name:           AutoAuxiCtrl
** Descriptions:            跟机自动化辅助动作控制
** input parameters:        
** output parameters:       none
** Returned value:          
** Created by:              linguofeng 
** Created Date:            2016-05-20
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
void AutoAuxiCtrl(AUTO_CONTEXT_S *pstCtx,AUTO_PHASE_DATA_S *pstData)
{    
    
    if (GetAutoFlipEn())
    {
        if (!pstData->bInitFlipData)
        {
            AutoFlipDataInit(pstCtx,pstData);
            pstData->bInitFlipData = TRUE;
        }
        AuxiFlipInCtrl(pstCtx,pstData);
        AuxiFlipExCtrl(pstCtx,pstData);
    }
    else
    {
        pstData->bInitFlipData = FALSE;
    }
}


static void UpPhase1DataInit(AUTO_PHASE_DATA_S *pstData,INT8U u8ShearPos)
{
    INT8U u8AsqOffset = GetAutoASQOffset();
    INT8U u8PushOffset = GetAutoPushOffset();
    INT8U u8ShearLenOffset = GetShearLenOffset();
    INT8U u8CurrShear = GetShieldNum();
    
    if (u8ShearPos > ((INT32U)u8CurrShear+(INT32U)u8ShearLenOffset+(INT32U)u8AsqOffset))
    {
        pstData->u8ASQStat = AUTO_EXECUTED;
    }
    if (u8ShearPos > ((INT32U)u8CurrShear+(INT32U)u8ShearLenOffset+(INT32U)u8PushOffset))
    {
        pstData->u8PushStat = AUTO_EXECUTED;
    }
}
static void UpPhase2DataInit(AUTO_PHASE_DATA_S *pstData,INT8U u8ShearPos)
{
    INT8U u8AsqOffset = GetAutoASQOffset();
    INT8U u8ShearLenOffset = GetShearLenOffset();
    INT8U u8CurrShear = GetShieldNum();

    if (((INT32U)u8ShearPos + (INT32U)u8ShearLenOffset + (INT32U)u8AsqOffset) < u8CurrShear)
    {
        pstData->u8ASQStat = AUTO_EXECUTED;
    }    
}
static void UpPhase3DataInit(AUTO_PHASE_DATA_S *pstData,INT8U u8ShearPos)
{
    INT8U u8CurrShear = GetShieldNum();

    if (u8CurrShear >= GetPhase3StartShield())
    {
        pstData->u8PushStat = AUTO_EXECUTED;
    }
}
static void UpPhase4DataInit(AUTO_PHASE_DATA_S *pstData,INT8U u8ShearPos)
{
    INT8U u8AsqOffset = GetAutoASQOffset();
    INT8U u8ShearLenOffset = GetShearLenOffset();
    INT8U u8CurrShear = GetShieldNum();

    if (u8ShearPos > ((INT32U)u8CurrShear+(INT32U)u8ShearLenOffset+(INT32U)u8AsqOffset))
    {
        pstData->u8ASQStat = AUTO_EXECUTED;
    }

}
static void UpPhase5DataInit(AUTO_PHASE_DATA_S *pstData,INT8U u8ShearPos)
{
    INT8U u8AsqOffset = GetAutoASQOffset();
    INT8U u8PushOffset = GetAutoPushOffset();
    INT8U u8ShearLenOffset = GetShearLenOffset();
    INT8U u8CurrShear = GetShieldNum();

    if (((INT32U)u8ShearPos + (INT32U)u8ShearLenOffset + (INT32U)u8AsqOffset) < u8CurrShear)
    {
        pstData->u8ASQStat = AUTO_EXECUTED;
    } 

    if (((INT32U)u8ShearPos + (INT32U)u8ShearLenOffset + (INT32U)u8PushOffset) < u8CurrShear)
    {
        pstData->u8PushStat = AUTO_EXECUTED;
    }
}
static void DnPhase1DataInit(AUTO_PHASE_DATA_S *pstData,INT8U u8ShearPos)
{
    UpPhase5DataInit(pstData,u8ShearPos);
}
static void DnPhase2DataInit(AUTO_PHASE_DATA_S *pstData,INT8U u8ShearPos)
{
    UpPhase4DataInit(pstData,u8ShearPos);  
}
static void DnPhase3DataInit(AUTO_PHASE_DATA_S *pstData,INT8U u8ShearPos)
{
    INT8U u8CurrShear = GetShieldNum();

    if (u8CurrShear <= GetPhase3StartShield())
    {
        pstData->u8PushStat = AUTO_EXECUTED;
    }
}
static void DnPhase4DataInit(AUTO_PHASE_DATA_S *pstData,INT8U u8ShearPos)
{
    UpPhase2DataInit(pstData,u8ShearPos);
}
static void DnPhase5DataInit(AUTO_PHASE_DATA_S *pstData,INT8U u8ShearPos)
{
    UpPhase1DataInit(pstData,u8ShearPos);
}

static void UpgoingPhase1Init(AUTO_STATE_S *pstState,AUTO_PHASE_DATA_S *pstAutoData)
{
    pstState[UP_P1_E].pData = pstAutoData; 
    pstState[UP_P1_E].pfASQCheck = CheckUpPhase1ASQArea;
    pstState[UP_P1_E].pfPushCheck = CheckUpPhase1PushArea;
    pstState[UP_P1_E].pfFlipExCheck = CheckUpP1FlipEx;
    pstState[UP_P1_E].pfFlipInCheck = CheckUpP1FlipIn;
    pstState[UP_P1_E].pfunc = AutoPhase1Dispense;
    pstState[UP_P1_E].pfAuxifunc = AutoAuxiCtrl;
    pstState[UP_P1_E].pfPhaseDataInit = UpPhase1DataInit;
}
static void UpgoingPhase2Init(AUTO_STATE_S *pstState,AUTO_PHASE_DATA_S *pstAutoData)
{
    pstState[UP_P2_E].pData = pstAutoData;
    pstState[UP_P2_E].pfASQCheck = CheckUpPhase2ASQArea;
    pstState[UP_P2_E].pfFlipExCheck = CheckUpP2FlipEx;
    pstState[UP_P2_E].pfFlipInCheck = CheckUpP2FlipIn;
    pstState[UP_P2_E].pfunc = AutoPhase2Dispense;
    pstState[UP_P2_E].pfAuxifunc = AutoAuxiCtrl;
    pstState[UP_P2_E].pfPhaseDataInit = UpPhase2DataInit;
}

static void UpgoingPhase3Init(AUTO_STATE_S *pstState,AUTO_PHASE_DATA_S *pstAutoData)
{
    pstState[UP_P3_E].pData = pstAutoData;
    pstState[UP_P3_E].pfPushCheck = CheckUpPhase3PushArea;
    pstState[UP_P3_E].pfFlipExCheck = CheckUpP3FlipEx;
    pstState[UP_P3_E].pfFlipInCheck = CheckUpP3FlipIn;
    pstState[UP_P3_E].pfunc = AutoPhase3Dispense;
    pstState[UP_P3_E].pfAuxifunc = AutoAuxiCtrl;
    pstState[UP_P3_E].pfPhaseDataInit = UpPhase3DataInit;
}

static void UpgoingPhase4Init(AUTO_STATE_S *pstState,AUTO_PHASE_DATA_S *pstAutoData)
{
    pstState[UP_P4_E].pData = pstAutoData;
    pstState[UP_P4_E].pfASQCheck = CheckUpPhase4ASQArea;
    pstState[UP_P4_E].pfFlipExCheck = CheckUpP4FlipEx;
    pstState[UP_P4_E].pfFlipInCheck = CheckUpP4FlipIn;
    pstState[UP_P4_E].pfunc = AutoPhase4Dispense;
    pstState[UP_P4_E].pfAuxifunc = AutoAuxiCtrl;
    pstState[UP_P4_E].pfPhaseDataInit = UpPhase4DataInit;
}

static void UpgoingPhase5Init(AUTO_STATE_S *pstState,AUTO_PHASE_DATA_S *pstAutoData)
{
    pstState[UP_P5_E].pData = pstAutoData;
    pstState[UP_P5_E].pfASQCheck = CheckUpPhase5ASQArea;
    pstState[UP_P5_E].pfPushCheck = CheckUpPhase5PushArea;
    pstState[UP_P5_E].pfFlipExCheck = CheckUpP5FlipEx;
    pstState[UP_P5_E].pfFlipInCheck = CheckUpP5FlipIn;
    pstState[UP_P5_E].pfunc = AutoPhase5Dispense;   
    pstState[UP_P5_E].pfAuxifunc = AutoAuxiCtrl; 
    pstState[UP_P5_E].pfPhaseDataInit = UpPhase5DataInit;
}

static void DowngoingPhase1Init(AUTO_STATE_S *pstState,AUTO_PHASE_DATA_S *pstAutoData)
{
    pstState[DOWN_P1_E].pData = pstAutoData;
    pstState[DOWN_P1_E].pfASQCheck = CheckDnPhase1ASQArea;
    pstState[DOWN_P1_E].pfPushCheck = CheckDnPhase1PushArea;
    pstState[DOWN_P1_E].pfFlipExCheck = CheckDnP1FlipEx;
    pstState[DOWN_P1_E].pfFlipInCheck = CheckDnP1FlipIn;
    pstState[DOWN_P1_E].pfunc = AutoPhase1Dispense;
    pstState[DOWN_P1_E].pfAuxifunc = AutoAuxiCtrl;
    pstState[DOWN_P1_E].pfPhaseDataInit = DnPhase1DataInit;
    
}

static void DowngoingPhase2Init(AUTO_STATE_S *pstState,AUTO_PHASE_DATA_S *pstAutoData)
{
    pstState[DOWN_P2_E].pData = pstAutoData;
    pstState[DOWN_P2_E].pfASQCheck = CheckDnPhase2ASQArea;
    pstState[DOWN_P2_E].pfFlipExCheck = CheckDnP2FlipEx;
    pstState[DOWN_P2_E].pfFlipInCheck = CheckDnP2FlipIn;
    pstState[DOWN_P2_E].pfunc = AutoPhase2Dispense;
    pstState[DOWN_P2_E].pfAuxifunc = AutoAuxiCtrl; 
    pstState[DOWN_P2_E].pfPhaseDataInit = DnPhase2DataInit;
    
}

static void DowngoingPhase3Init(AUTO_STATE_S *pstState,AUTO_PHASE_DATA_S *pstAutoData)
{
    pstState[DOWN_P3_E].pData = pstAutoData;
    pstState[DOWN_P3_E].pfPushCheck = CheckDnPhase3PushArea;
    pstState[DOWN_P3_E].pfFlipExCheck = CheckDnP3FlipEx;
    pstState[DOWN_P3_E].pfFlipInCheck = CheckDnP3FlipIn;    
    pstState[DOWN_P3_E].pfunc = AutoPhase3Dispense;        
    pstState[DOWN_P3_E].pfAuxifunc = AutoAuxiCtrl; 
    pstState[DOWN_P3_E].pfPhaseDataInit = DnPhase3DataInit;
}

static void DowngoingPhase4Init(AUTO_STATE_S *pstState,AUTO_PHASE_DATA_S *pstAutoData)
{
    pstState[DOWN_P4_E].pData = pstAutoData;
    pstState[DOWN_P4_E].pfASQCheck = CheckDnPhase4ASQArea;
    pstState[DOWN_P4_E].pfunc = AutoPhase4Dispense;  
    pstState[DOWN_P4_E].pfFlipExCheck = CheckDnP4FlipEx;
    pstState[DOWN_P4_E].pfFlipInCheck = CheckDnP4FlipIn;
    pstState[DOWN_P4_E].pfAuxifunc = AutoAuxiCtrl; 
    pstState[DOWN_P4_E].pfPhaseDataInit = DnPhase4DataInit;
}

static void DowngoingPhase5Init(AUTO_STATE_S *pstState,AUTO_PHASE_DATA_S *pstAutoData)
{
    pstState[DOWN_P5_E].pData = pstAutoData;
    pstState[DOWN_P5_E].pfASQCheck = CheckDnPhase5ASQArea;
    pstState[DOWN_P5_E].pfPushCheck = CheckDnPhase5PushArea;
    pstState[DOWN_P5_E].pfunc = AutoPhase5Dispense; 
    pstState[DOWN_P5_E].pfFlipExCheck = CheckDnP5FlipEx;
    pstState[DOWN_P5_E].pfFlipInCheck = CheckDnP5FlipIn;
    pstState[DOWN_P5_E].pfAuxifunc = AutoAuxiCtrl; 
    pstState[DOWN_P5_E].pfPhaseDataInit = DnPhase5DataInit;
}
static INT8U ConvertPhase2Index()
{
    INT8U u8Phase = (INT8U)GetAutoPhase();
    INT8U u8AutoDir = GetAutoDir();
    INT8U u8Index = 0;
    OSSchedLock();
    u8Index = (u8Phase-1)+(u8AutoDir-AUTO_DIR_UP)*MAX_AUTO_PHASE;
    OSSchedUnlock();
    return u8Index;
}
BOOLEAN AutoCtxInit(AUTO_CONTEXT_S *pstCtx,INT8U *pu8Position,AUTO_PHASE_DATA_S *pstAutoData)
{
    INT8U u8Index = 0;
    /*  参数检查，上层保证 */
    u8Index = ConvertPhase2Index();
    if (u8Index >= MAX_AUTO_INDEX)
    {
        ERR_MESSAGE("AutoCtxInit fail");
        return FALSE;
    }
    pstCtx->pfGetState = GetAutoStat;
    pstCtx->pfSetState = SetAutoStat;
    pstCtx->pstCurrStat = &g_astAutoPhase[u8Index];
    pstCtx->pu8ShearPos = pu8Position;
    
    UpgoingPhase1Init(g_astAutoPhase,pstAutoData);
    UpgoingPhase2Init(g_astAutoPhase,pstAutoData);
    UpgoingPhase3Init(g_astAutoPhase,pstAutoData);
    UpgoingPhase4Init(g_astAutoPhase,pstAutoData);
    UpgoingPhase5Init(g_astAutoPhase,pstAutoData);
    DowngoingPhase1Init(g_astAutoPhase,pstAutoData);
    DowngoingPhase2Init(g_astAutoPhase,pstAutoData);
    DowngoingPhase3Init(g_astAutoPhase,pstAutoData);
    DowngoingPhase4Init(g_astAutoPhase,pstAutoData);
    DowngoingPhase5Init(g_astAutoPhase,pstAutoData);
    return TRUE;
}

/*
跟机参数合理性检查
*/
static BOOLEAN AutoParaCheck()
{
    INT8U u8ASQArea = GetAutoASQArea();
    INT8U u8ASQOffset = GetAutoASQOffset();
    INT8U u8PushOffset = GetAutoPushOffset();
    INT16U u16Sum = 0;
    BOOLEAN bRet = TRUE;
    
    u16Sum = (INT16U)u8ASQArea + (INT16U)u8ASQOffset;  
    
    if (INT8U_MAX_VAL <= u16Sum)
    {
        GUI_Printf(0,SECOND_ROW,1,"移架参数太大    ");
        bRet = FALSE;
    }
    if (u8PushOffset <= (u8ASQOffset+u8ASQArea))
    {
        GUI_Printf(0,SECOND_ROW,1,"推溜偏移参数过小");
        bRet = FALSE;
    }
    // TODO:/* 移架，推溜，护帮动作范围重叠判断，移架和推溜不能重叠，移架和护帮也不能重叠 */
    return bRet;
}



static void AutoDataInit(AUTO_CONTEXT_S *pstCtx,SHEAR_DATA_S *pstShearData,AUTO_PHASE_DATA_S *pstData)
{
    INT8U u8Index = 0;
    while(0 == pstShearData->u8ShearPos)
    {
        sysMsgPend(gu32AutoMsg,(INT8U*)pstShearData,0); 
        if(OS_TASK_DEL_REQ == OSTaskDelReq(OS_PRIO_SELF))
        {
            OSTaskDel(OS_PRIO_SELF);
        }        
    }
    
    u8Index = ConvertPhase2Index();
    pstCtx->pfSetState(pstCtx,&g_astAutoPhase[u8Index]); 
    pstCtx->pstCurrStat->pfPhaseDataInit(pstData,pstShearData->u8ShearPos);
    AutoFlipDataInit(pstCtx,pstData);
}
/*********************************************************************************************************
** Function name:           Task_AutoMining
** Descriptions:            跟机自动化采煤任务
** input parameters:       
** output parameters:       none
** Returned value:          
** Created by:              linguofeng 
** Created Date:            2015-09-25
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
void Task_AutoMining(void *pData)
{
    SHEAR_DATA_S stShearData;
    AUTO_CONTEXT_S stAutoCtx;
    INT8U u8Index = 0;
    
    memset(&stShearData,0,sizeof(stShearData));
    memset(&stAutoCtx,0,sizeof(stAutoCtx));
    
    if (!AutoCtxInit(&stAutoCtx,&(stShearData.u8ShearPos),&g_stAutoData))
    {
        OSTaskDel(OS_PRIO_SELF);
    }
    AutoDataInit(&stAutoCtx,&stShearData,&g_stAutoData);
    
    while(1)
    {
        stShearData.u8ShearPos = 0;
        sysMsgPend(gu32AutoMsg,(INT8U*)&stShearData,200);
        
        if(OS_TASK_DEL_REQ == OSTaskDelReq(OS_PRIO_SELF))
        {
            OSTaskDel(OS_PRIO_SELF);
        }
        if (0 == stShearData.u8ShearPos)
        {
            continue;
        }
        /* 检查急停闭锁状态 ，有急停闭锁 continue */
        if (ESTOP_ACCURED == GetEStopStat())
        {
            OSTimeDly(OS_TICKS_PER_SEC);
            continue;
        }
        if (!AutoParaCheck())
        {
            /* 记录跟机参数错误 */
            ERR_MESSAGE("AutoMining Para Err");
            OSTimeDly(OS_TICKS_PER_SEC);  
            continue;
        }        
        
        u8Index = ConvertPhase2Index();
        stAutoCtx.pfSetState(&stAutoCtx,&g_astAutoPhase[u8Index]);
        stAutoCtx.pstCurrStat->pfunc(&stAutoCtx,&g_stAutoData);
        stAutoCtx.pstCurrStat->pfAuxifunc(&stAutoCtx,&g_stAutoData);
        OSTimeDly(OS_TICKS_PER_SEC/2);
    }
}
