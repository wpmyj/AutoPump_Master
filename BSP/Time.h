/******************** (C) COPYRIGHT 2016 DammStanger *****************************************
**--------------文件信息----------------------------------------------------------
 * 文件名	：Time.h
 * 描	述	：STC 60S2 延时，定时，等时间函数	11.0592MHz
 *            
 * 实验平台	：自控水泵V2.0	
 * 硬件连接	：
 * 版 	本	：V0.1.160217
 * 从属关系	：PoolAuto
 * 库版本	：无
 * 创建时间	：2016.2.17
 * 最后编辑	：2016.2.17
 **-------------------------------------------------------------------------------

 * 作	者	：Damm Stanger
 * 邮	箱	：dammstanger@qq.com
**********************************************************************************************/
#ifndef __TIME_H
#define __TIME_H
/****************************包含头文件*******************************************/
#include "globaldefine.h"
/****************************宏定义***********************************************/
//计时器宏


//定时器宏
#define	TIMEUP_1		0x01
#define	TIMEUP_2		0x02
#define	TIMEUP_3		0x04
#define	TIMEUP_4		0x08

#define	TIMER_1		1
#define	TIMER_2		2
#define	TIMER_3		3
#define	TIMER_4		4

/****************************类型定义*********************************************/
typedef struct {
	uchar sec;
	uchar min;
	uchar working;
}STR_TIM_M_S;
/****************************变量声明*********************************************/
extern uchar Timer_reg;
extern uchar Timer1_cnt;			//最小单位1s,最大定时255秒
extern uchar Timer2_cnt;
extern uchar Timer3_cnt;

//计时器
extern STR_TIM_M_S UpTimer1;
/****************************变量定义*********************************************/

/****************************函数声明*********************************************/
void delay1s(void);   		////11.0592 STC1T 误差 -0.000000000099us
void delay200ms(void);   	//误差 -0.000000000028us
void delay100ms(void);	    //

void SetSoftTimer(uchar timerx,long val);
uchar ReadSoftTimer(uchar timerx);
void SoftTimer();

//计时器函数
void SoftUpTimer_Reset(STR_TIM_M_S *timer);
void SoftUpTimer_Stop(STR_TIM_M_S *timer);
void SoftUpTimer_Start(STR_TIM_M_S *timer);
uchar SoftTimer_ReadMin(STR_TIM_M_S timer);
uint SoftTimer_ReadSec(STR_TIM_M_S timer);
void SoftUpTimer(STR_TIM_M_S *timer);
#endif



/******************* (C) COPYRIGHT 2016 DammStanger *****END OF FILE************/


