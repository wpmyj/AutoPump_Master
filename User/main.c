/******************** (C) COPYRIGHT 2016 DammStanger *****************************************
**--------------�ļ���Ϣ----------------------------------------------------------
 * �ļ���	��main.c
 * ��	��	��Һλ�Զ�������Ŀ����
 *            
 * ʵ��ƽ̨	���Կ�ˮ��V2.0
 * Ӳ������	��
 * �� 	��	��V0.0.150711
 * ������ϵ	��PoolAuto
 * ��汾	����
 * ����ʱ��	��2015.7.11
 * ���༭	��2016.1.26
 **-------------------------------------------------------------------------------

 * ��	��	��Damm Stanger
 * ��	��	��dammstanger@qq.com
**********************************************************************************************/

/****************************����ͷ�ļ�*******************************************/
#include "globaldefine.h"
#include "stdio.h"
#include "UART_51.h"
#include "SI4432.h"
#include "Transmit.h"
#include "DS18B20.h"
#include "ADC_51.h"
#include "DS3231.h"
#include "IIC_soft_51.h"
/****************************�궨��***********************************************/
#define P2_5	0x20
#define P2_7	0x80

/****************************��������*********************************************/

/****************************��������*********************************************/
sbit START 	= P2^7;
sbit STOP	= P2^5;
sbit ALARM	= P4^0;
char temp;
char dat[] = "abc";
/****************************��������*********************************************/

void delay200ms(void)   //��� -0.000000000028us
{
    unsigned char a,b,c;
    for(c=178;c>0;c--)
        for(b=230;b>0;b--)
            for(a=12;a>0;a--);
}

void delay1s(void)   ////11.0592 STC1T ��� -0.000000000099us
{
    unsigned char a,b,c;
    for(c=217;c>0;c--)
        for(b=171;b>0;b--)
            for(a=73;a>0;a--);
}

void EXTI0_Init()
{
	IT0 = 1;                        //set INT0 int type (1:Falling 0:Low level)
    EX0 = 1;                        //enable INT0 interrupt
}

void JiDianQ_Init()
{;
	P2M0 = 0;//P2_5|P2_7;				//P2.1 P2.2ǿ����
	P2M1 = 0;
}



void main()
{
	delay1s();
	AUXR = AUXR|0x40;  	// T1, 1T Mode

//	IE2 |= ESPI;
	EXTI0_Init();                         
	UART_Init();
//	JiDianQ_Init();
	SPI_Init(MASTER);
	IIC_GPIO_Config();
	delay1s();
	DS3231_Init();
	SI4432_Init();
	SI4432_SetRxMode();	//����ģʽ
//	ADC_Init();
//	delay1s();
//	SendString("ROMID Search...\r\n");
//	SendROMID(DS18B20_SearchRomID());
//	SendString("\r\n");					//������Ϣʱ����
	//-----------------------------------------------------
	EA = 1;								//ע�⣺�����ʼ�����ٿ��жϣ�

	while(1)
	{	
		
//		ADC_STARTCOV(ADC_CH0,ADC_SPEED_540T);
//		delay200ms();
//		delay200ms();
//		DATA_Cmd_ACK();
//		if(Trans_RevPakFin)
//		{
//			Trans_RevPakFin = 0;
//			if(1==Pak_Handle())
//				SendString("valid data received.\r\n");					//������Ϣʱ����
//		}
		delay1s();
		DS3231_Init();
//		SendString("temp:\r\n");									//������Ϣʱ����
//		SendTemp(DS18B20_ReadTemperature(1));
//		SendString("\r\n");											//������Ϣʱ����
//		SendString("temp::\r\n");									//������Ϣʱ����
//		SendTemp(DS18B20_ReadTemperature(2));
//		SendString("\r\n");											//������Ϣʱ����
		LED1 = 0;
		ALARM = 0;
		START = 0;
		STOP = 0;
		delay1s();
		ALARM = 1;
		START = 1;
		STOP = 1;
		LED1 = 1;
//		debug();
	}
}



void EXTI0_ISR() interrupt 0 
{	//��Ӧ��IE0�Զ����
	SI4432_ISR();
	SendString("ISR completed.\r\n");					//������Ϣʱ����	
}

/******************* (C) COPYRIGHT 2016 DammStanger *****END OF FILE************/
