/******************** (C) COPYRIGHT 2016 DammStanger *****************************************
**--------------文件信息----------------------------------------------------------
 * 文件名	：Menu.H
 * 描	述	：菜单设计
 *                    
 * 实验平台	：AutoPumpV2.0
 * 硬件连接	：
 * 版 	本	：V0.0.160220
 * 从属关系	：PoolAuto
 * 库版本	：无
 * 创建时间	：2016.2.20
 * 最后编辑	：2016.2.20
 **-------------------------------------------------------------------------------

 * 作	者	：Damm Stanger
 * 邮	箱	：dammstanger@qq.com
**********************************************************************************************/
#ifndef __MENU_H
#define __MENU_H
/****************************包含头文件*******************************************/
#include "globaldefine.h"

/****************************宏定义***********************************************/
//用一个字变量g_menumark定义菜单，每4位为1菜单级别
//0级
//1级
#define MENU_OPERATE			0x1000
#define MENU_KEYINPUT			0x2000
#define MENU_HISTORY			0x3000
//2级
#define MENU_SET				0x2100
//3级
#define MENU_MODE				0x2110
#define MENU_STARTL				0x2120
#define MENU_STOPL				0x2130
#define MENU_DATETIME			0x2140
#define MENU_KEYSET				0x2150
#define MENU_BACKLIT			0x2160


/****************************类型定义*********************************************/

/****************************变量声明*********************************************/
extern uint g_menumark;
/****************************变量定义*********************************************/

/****************************函数声明*********************************************/

#endif



/******************* (C) COPYRIGHT 2016 DammStanger *****END OF FILE************/


