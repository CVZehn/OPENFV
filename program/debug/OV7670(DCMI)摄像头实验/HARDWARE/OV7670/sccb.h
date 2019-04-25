#ifndef __SCCB_H
#define __SCCB_H
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F407������
//OVϵ������ͷ SCCB ��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2014/5/14
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 


//IO��������
#define SCCB_SDA_IN()  {GPIOD->MODER&=~(3<<(3*2));GPIOD->MODER|=0<<3*2;}	//PD7 ����
#define SCCB_SDA_OUT() {GPIOD->MODER&=~(3<<(3*2));GPIOD->MODER|=1<<3*2;} 	//PD7 ���


//IO��������	 
#define SCCB_SCL    		PDout(2)	 	//SCL
#define SCCB_SDA    		PDout(3) 		//SDA	 

#define SCCB_READ_SDA   PDin(3)  		//����SDA    
#define SCCB_ID   			0X42  			//OV7670��ID

///////////////////////////////////////////
void SCCB_Init(void);
void SCCB_Start(void);
void SCCB_Stop(void);
void SCCB_No_Ack(void);
u8 SCCB_WR_Byte(u8 dat);
u8 SCCB_RD_Byte(void);
u8 SCCB_WR_Reg(u8 reg,u8 data);
u8 SCCB_RD_Reg(u8 reg);
#endif













