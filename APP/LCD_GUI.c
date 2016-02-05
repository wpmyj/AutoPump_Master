/******************** (C) COPYRIGHT 2015 DammStanger *****************************************
**--------------文件信息----------------------------------------------------------
 * 文件名	：LCD_GUI.c
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
#include "LCD_GUI.h"
#include "lcd_YXD19264D_51.h"


/********************************************************************************
 * 函数名：LCD_FlashArrows()
 * 描述  ：箭头闪烁
 * 输入  ：-		    	
 * 返回  ：- 
 * 调用  ：外部调用
 ********************************************************************************/
void LCD_FlashArrows(bool enable)
{
	static bit flash = 0;
	uchar buf[26][5]={0};
	if(enable)
	{
		flash =~flash;
		if(flash) 	LCD_Dis_Pict(17,55,24,5,Pic_arrow);	
		else		LCD_Clear_Region(17,55,24,5);
	}
	else
	{
		if(flash)
		{
			LCD_Clear_Region(17,55,24,5);
			flash = 0;
		}
	}
	
}

/********************************************************************************
 * 函数名：GUI_HomePage()
 * 描述  ：显示主界面常量
 * 输入  ：-		    	
 * 返回  ：- 
 * 调用  ：外部调用
 ********************************************************************************/
void GUI_HomePage()
{
	LCD_Dis_Pict(1,1,45,62,Pic_Case);
	LCD_Dis_Char_16_16(1,5,&WordLib_CN[4][0],FALSE);		//水位自动控制系统
	LCD_Dis_Char_16_16(1,6,&WordLib_CN[5][0],FALSE);		//
	LCD_Dis_Char_16_16(1,7,&WordLib_CN[13][0],FALSE);		//
	LCD_Dis_Char_16_16(1,8,&WordLib_CN[14][0],FALSE);		//
	LCD_Dis_Char_16_16(1,9,&WordLib_CN[15][0],FALSE);		//
	LCD_Dis_Char_16_16(1,10,&WordLib_CN[16][0],FALSE);		//
	LCD_Dis_Char_16_16(1,11,&WordLib_CN[17][0],FALSE);		//
	LCD_Dis_Char_16_16(1,12,&WordLib_CN[18][0],FALSE);		//
	
	LCD_Dis_Char_16_16(2,5,&WordLib_CN[0][0],FALSE);		//实时温度
	LCD_Dis_Char_16_16(2,6,&WordLib_CN[1][0],FALSE);		//
	LCD_Dis_Char_16_16(2,7,&WordLib_CN[2][0],FALSE);		//
	LCD_Dis_Char_16_16(2,8,&WordLib_CN[3][0],FALSE);		//	
	LCD_Dis_ASCIIStr(2,17,":",FALSE);
	LCD_Dis_Digital_float(2,22,3225);
	LCD_Dis_Char_8_16(2,23,&CharLib_SplLabel[0][0],FALSE);
	LCD_Dis_ASCIIStr(2,24,"C",FALSE);
	
	LCD_Dis_Char_16_16(3,5,&WordLib_CN[19][0],FALSE);		//状态
	LCD_Dis_Char_16_16(3,6,&WordLib_CN[20][0],FALSE);
	LCD_Dis_ASCIIStr(3,17,":",FALSE);
	LCD_Dis_Char_16_16(3,10,&WordLib_CN[21][0],FALSE);		//空闲
	LCD_Dis_Char_16_16(3,11,&WordLib_CN[22][0],FALSE);
	
	LCD_Dis_Char_16_16(4,2,&WordLib_CN[23][0],TRUE);		//历史
	LCD_Dis_Char_16_16(4,3,&WordLib_CN[24][0],TRUE);		//
	
	LCD_Dis_Char_16_16(4,6,&WordLib_CN[27][0],TRUE);		//设置
	LCD_Dis_Char_16_16(4,7,&WordLib_CN[28][0],TRUE);		//
	
	LCD_Dis_ASCIIStr(4,18,"HOME",TRUE);		//HOME
	
	GUI_CaseData_Dis(50);
}


/********************************************************************************
 * 函数名：LCD_FlashArrows()
 * 描述  ：箭头闪烁
 * 输入  ：-		    	
 * 返回  ：- 
 * 调用  ：外部调用
 ********************************************************************************/
void GUI_CaseData_Dis(char percent)
{
	char filevel;
	static signed char filevel_smooth=0,filevel_last = 0;
	static char percent_last=0;
	uchar fallflag = 0;
	uchar i;
	
	filevel = (signed char)(percent/2.44+1);
	filevel_smooth = filevel - filevel_last;
	if(filevel_smooth<0)
	{
		fallflag = 1;
		filevel_smooth = 0-filevel_smooth;
	}
	for(i=0;i<filevel_smooth;i++)
	{		
		if(fallflag)	filevel_last -= 1;
		else 			filevel_last += 1;
		//filevel_last = (fallflag?(filevel_last-i):(fallflag+i));			//为什么不行？
		switch(filevel_last)
		{
			case 1 : 
			{	if(fallflag)							//往下降
					LCD_Clear_Region(42,5,1,43);		//清理上一条水平线
				else
				{
					LCD_fill_Region(43,6,1,41);
				}
			}break;
			case 2 : 
			{	if(fallflag)							//往下降
					LCD_Clear_Region(41,4,1,45);		//清理上一条水平线
				else
				{
					LCD_fill_Region(42,5,1,43);
				}
			}break;			
			case 3 : 
			{	if(fallflag)							//往下降
					LCD_Clear_Region(40,4,1,45);		//清理上一条水平线
				else
				{
					LCD_fill_Region(41,4,1,45);
				}
			}break;
			case 4 :
			{	if(fallflag)							//往下降
					LCD_Clear_Region(39,3,1,47);		//清理上一条水平线
				else
				{
					LCD_fill_Region(40,4,1,45);
				}
			}break;
			case 38 :
			{	if(fallflag)							
					LCD_Clear_Region(5,4,1,45);		
				else
				{
					LCD_fill_Region(6,4,1,45);
				}
			}break;
			case 39 :
			{	if(fallflag)							
					LCD_Clear_Region(4,5,1,43);		
				else
				{
					LCD_fill_Region(5,4,1,45);
				}
			}break;
			case 40 :
			{	if(fallflag)							//往下降
					LCD_Clear_Region(3,6,1,41);		//清理上一条水平线
				else
				{
					LCD_fill_Region(4,5,1,43);
				}
			}break;
			case 41 :
			{	
					LCD_fill_Region(3,6,1,41);
			}break;	
			default :
			{	
				if(fallflag)							//往下降
					LCD_Clear_Region(43-filevel_last,3,1,47);		//清理上一条水平线
				else
				{
					LCD_fill_Region(44-filevel_last,3,1,47);
				}				
			}break;
		}
	}
	LCD_Dis_Digital_int(2,4,percent);
	LCD_Dis_ASCIIStr(2,5,"%",FALSE);
	if(percent==99&&percent - percent_last<0)
	{
		LCD_fill_Region(17,9,16,8);
	}
	percent_last = percent;
}


uchar code Pic_arrow[]={
	0x00,0xF0,0xFF,0xF0,0x00,
	0x1C,0xFF,0xFF,0xFF,0x1C,
	0x00,0xFF,0xFF,0xFF,0x00,
};

uchar code Pic_xuejie[]={
0xFF,0x7F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x7F,0xFF,0xFF,
0x3F,0x1F,0x1F,0x1F,0x1F,0x1F,0x7F,0xFF,0xFF,0xFF,0xFF,0x7F,0x7F,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x7F,0x7F,0x3F,0x7F,0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x3F,0x1F,0x1F,0x1F,0x1F,0x1F,0x3F,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x3F,0x1F,0x1F,0x1F,0x1F,0x1F,
0x3F,0xFF,0xFF,0xFF,0xFF,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,
0x3F,0x3F,0x3F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0x7F,0x3F,0x3F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x3F,0x3F,0x7F,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0x3F,0x1F,0x1F,0x1F,0x1F,0x1F,0xBF,0x7F,0x3F,0x1F,0x1F,0x1F,0x1F,0x3F,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF8,
0xF0,0x70,0x70,0x70,0x70,0x70,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x0F,0x03,0x01,0x00,0x00,0x00,0x80,0xE0,0xFB,0xFF,0xFF,
0xFF,0xFF,0xFF,0xF9,0xF0,0xE0,0xE0,0xC0,0x80,0x80,0x00,0x81,0xC3,0xFF,0x99,0x81,
0x81,0x81,0x81,0x81,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x81,0x81,0x81,0x81,
0x81,0x81,0x81,0xE3,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xC1,0xC0,0x80,0x00,0x00,0x00,0x00,0x00,0xC0,0x20,0x30,0x10,0x10,
0x20,0x61,0xC1,0x7E,0x00,0x00,0x00,0x00,0x8C,0x8C,0x8C,0x8C,0x00,0x00,0x00,0x00,
0x00,0x00,0xFF,0xFF,0xFF,0x7F,0x1F,0x0F,0x0F,0x07,0x07,0x03,0x01,0x01,0x00,0x00,
0x00,0xE0,0x10,0x08,0x08,0x08,0x08,0x18,0x30,0xC0,0x00,0x00,0x00,0x00,0x01,0x03,
0x03,0x07,0x07,0x0F,0x0F,0x1F,0xFF,0xFF,0xFF,0xFF,0xFF,0x3F,0x0F,0x01,0x00,0x00,
0x00,0xC0,0x30,0x0C,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x01,0x01,
0x81,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x83,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,
0x00,0x00,0x00,0x00,0x10,0x10,0x10,0x10,0x7E,0x83,0x81,0x81,0x00,0x00,0x00,0x00,
0x80,0x40,0x60,0x60,0x20,0x60,0x40,0x80,0x81,0x81,0x81,0x81,0x81,0xE7,0xFF,0xFF,
0xFF,0xE1,0xC0,0xC0,0x80,0x00,0x00,0x01,0x03,0x07,0xCF,0xFF,0xC1,0x81,0x81,0x81,
0x81,0x81,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x81,0x81,0x81,0x81,0x81,0x81,
0xC1,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xF7,0xC3,0x81,0x00,0x00,0x80,0x00,0x00,0x01,0x07,0x0C,0x18,0x30,0xE0,0xC0,0xE0,
0xE0,0x9B,0x0C,0x00,0x00,0x00,0x31,0x31,0x31,0x31,0x00,0x00,0x00,0x00,0x00,0x00,
0xFF,0xFF,0xFF,0xFF,0xFC,0xF8,0xF8,0xC4,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x83,
0x82,0x80,0x80,0x80,0x80,0x80,0xC0,0x01,0x03,0x02,0x02,0x02,0x02,0x02,0x02,0xC6,
0xFC,0xF8,0xF8,0xFC,0xFF,0xFF,0xFF,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,
0x06,0xC4,0x38,0x08,0x08,0x0C,0x06,0x03,0x07,0x8C,0x70,0x00,0x00,0x18,0xFF,0x06,
0x04,0x0C,0x0C,0x0C,0x0C,0x3E,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFC,0x7C,0x7C,0x7C,
0xFC,0x7C,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x0F,0x30,
0x20,0x20,0x20,0x40,0x80,0x01,0x03,0x0F,0x1F,0x3F,0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,
0x7F,0x3F,0x1F,0x0F,0x03,0x01,0x01,0x01,0x03,0x83,0xE7,0x39,0x00,0x00,0x00,0x00,
0x00,0x00,0xE0,0xE0,0xE0,0xE0,0xE0,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0xFF,0xFF,
0xFF,0xFF,0xEF,0x83,0x01,0x01,0x01,0x01,0x01,0x03,0xCF,0xFF,0xFF,0xFF,0xFF,0x7F,
0x0F,0x07,0x03,0x03,0x02,0x02,0x04,0xFE,0x06,0x03,0x0F,0x73,0xC1,0x80,0x00,0x00,
0x01,0x02,0x04,0x0C,0xFC,0xFC,0xC4,0x00,0x02,0x02,0x02,0x04,0x04,0x1E,0x7F,0xFF,
0xFF,0xFF,0xFF,0x0F,0x03,0x01,0x01,0x01,0x01,0x03,0xFF,0x01,0x01,0x08,0x3F,0x61,
0xC1,0x80,0x00,0x07,0x0C,0x08,0x10,0x90,0xF0,0xF0,0x08,0x04,0x03,0x03,0x03,0x07,
0x0F,0x3F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0xFE,0x00,0x00,0x00,0x00,0x38,0x46,0x81,
0x80,0x80,0x80,0x80,0xC0,0x60,0x7C,0x43,0x00,0x00,0x00,0x00,0x01,0x0E,0x70,0xC0,
0x80,0x00,0x00,0x80,0x81,0xEF,0xFF,0xFF,0xFF,0xF9,0xE0,0xE0,0xE0,0xC0,0xC0,0xC0,
0xC0,0xC0,0xE0,0xE0,0xE0,0xF0,0xFC,0xFF,0xE0,0xC0,0xC0,0xE0,0xE0,0xE0,0xE0,0xF0,
0xF0,0xF8,0xFF,0xF8,0xF0,0xE0,0xE0,0xE0,0xF0,0xF9,0xFF,0xFF,0xFF,0xF0,0xE0,0xE0,
0xC0,0xE0,0xE0,0xF0,0xF8,0xFC,0xFE,0xFF,0xFF,0xE0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,
0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xE0,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFC,0xFE,0xFE,0xFF,0xFF,0xFF,0xFF,0xFF,0xF9,0xF0,0xE0,0xE0,
0xE0,0xE0,0xF0,0xF8,0xFF,0xF9,0xE0,0xC0,0xC0,0xC0,0xC0,0xC3,0xC3,0xC6,0xC6,0xC6,
0xC3,0xC3,0xC1,0xC0,0xC1,0xE7,0xFC,0xF8,0xF0,0xF0,0xF0,0xF8,0xF8,0xFF,0xFF,0xFF,
0xF0,0xE0,0xE0,0xE0,0xE0,0xE0,0xF0,0xF8,0xFF,0xF0,0xE0,0xC0,0xC0,0xC0,0xC0,0xC1,
0xC1,0xC2,0xC2,0xC2,0xC3,0xC1,0xC0,0xC0,0xE7,0xFC,0xF0,0xF0,0xE0,0xF0,0xF0,0xF0,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xE0,0xC0,0xC0,0xC0,0xC0,0xC0,0xE0,0xFF,0xFF,
0xFF,0xFF,0xE0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xE0,0xF0,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x1F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,
0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x03,0x01,0x01,0x01,0x03,0x03,
0x03,0x07,0x07,0x07,0x0F,0x0F,0x0F,0x1F,0x1F,0x1F,0x3F,0x3F,0x3F,0x7F,0x7F,0x7F,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x3F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,
0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x07,0x03,0x03,0x03,0x07,0x07,
0x07,0x0F,0x0F,0x0F,0x1F,0x1F,0x1F,0x3F,0x3F,0x3F,0x7F,0x7F,0x7F,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x3F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,
0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x07,0x03,0x03,0x03,0x07,
0x07,0x07,0x0F,0x0F,0x0F,0x1F,0x1F,0x1F,0x3F,0x3F,0x3F,0x7F,0x7F,0x7F,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x3F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,
0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x07,0x03,0x03,0x03,0x07,
0x07,0x07,0x0F,0x0F,0x0F,0x1F,0x1F,0x1F,0x3F,0x3F,0x3F,0x7F,0x7F,0x7F,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x80,0x80,0x80,0xC0,0xC0,0xC0,0xE0,0xE0,0xE0,0xF0,0xF1,
0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x80,0x80,0xC0,0xC0,0xC0,0xE1,0xE3,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x80,0x80,0xC0,0xC0,0xC0,0xE1,
0xE3,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x80,0x80,0xC0,0xC0,0xC0,0xE1,
0xE3,0xFF,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,
0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3C,0x38,0x38,0x38,0x3C,0x3C,0x3C,0x3E,0x3E,0x3E,
0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,
0x3F,0x3F,0x3F,0x3F,0x3E,0x3E,0x3E,0x3E,0x3E,0x3E,0x3E,0x3E,0x3E,0x3E,0x3E,0x3E,
0x3E,0x3E,0x3E,0x3E,0x3E,0x3E,0x38,0x30,0x30,0x30,0x38,0x38,0x38,0x3C,0x3C,0x3C,
0x3E,0x3E,0x3E,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,
0x3F,0x3F,0x3F,0x3F,0x3F,0x3E,0x3E,0x3E,0x3E,0x3E,0x3E,0x3E,0x3E,0x3E,0x3E,0x3E,
0x3E,0x3E,0x3E,0x3E,0x3E,0x3E,0x3E,0x38,0x30,0x30,0x30,0x38,0x38,0x38,0x3C,0x3C,
0x3C,0x3E,0x3E,0x3E,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,
0x3F,0x3F,0x3F,0x3F,0x3F,0x3E,0x3E,0x3E,0x3E,0x3E,0x3E,0x3E,0x3E,0x3E,0x3E,0x3E,
0x3E,0x3E,0x3E,0x3E,0x3E,0x3E,0x3E,0x38,0x30,0x30,0x30,0x38,0x38,0x38,0x3C,0x3C,
0x3C,0x3E,0x3E,0x3E,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F
};

/******************** (C) COPYRIGHT 2015 DammStanger ****END OF FILE***************************/
