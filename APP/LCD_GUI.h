/******************** (C) COPYRIGHT 2015 DammStanger *****************************************
**--------------文件信息----------------------------------------------------------
 * 文件名	：LCD_GUI.h
 * 描	述	：GUI设计
 *                    
 * 实验平台	：51开发板
 * 硬件连接	：
 * 版 	本	：V0.0.150714
 * 从属关系	：PoolAuto
 * 库版本	：无
 * 创建时间	：2015.7.14
 * 最后编辑	：2015.7.14
 **-------------------------------------------------------------------------------

 * 作	者	：Damm Stanger
 * 邮	箱	：dammstanger@qq.com
**********************************************************************************************/

#ifndef __LCD_GUI_H_
#define __LCD_GUI_H_

/****************************包含头文件*******************************************/
#include "globaldefine.h"
/****************************宏定义***********************************************/

/****************************类型定义*********************************************/
/****************************变量声明*********************************************/
extern uchar code Pic_arrow[];
extern uchar code Pic_xuejie[];
/****************************变量定义*********************************************/

/****************************函数声明*********************************************/
void LCD_FlashArrows(bool enable);
void GUI_CaseData_Dis(char percent);
void GUI_HomePage(void);


#endif

/******************** (C) COPYRIGHT 2015 DammStanger *****************************************/
