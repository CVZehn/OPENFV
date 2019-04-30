#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "key.h"
#include "Lcd_Driver.h"
#include "usmart.h"  
#include "usart2.h"  
#include "timer.h" 
#include "ov7670.h" 
#include "dcmi.h" 
#include "QDTFT_demo.h"
//ALIENTEK ̽����STM32F407������ ʵ��35
//����ͷ ʵ�� -�⺯���汾
//����֧�֣�www.openedv.com
//�Ա����̣�http://eboard.taobao.com  
//������������ӿƼ����޹�˾  
//���ߣ�����ԭ�� @ALIENTEK
u16 buff[120][160] __attribute__ ((at(0X20001000)));
u16 buf[2];
void Mco1_8MHz_Init(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//??PA

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;//PA8
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//??????

  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//????
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//50MHz


  GPIO_Init(GPIOA, &GPIO_InitStructure);  


 RCC_MCO1Config(RCC_MCO1Source_HSI,RCC_MCO1Div_4);  //?????HSI,16M  2??

}
void OV7670_CreatColor()
{
	uint16_t i,j,k = 0;
	uint16_t color = 0;
	//????
	uint16_t buff[320];
  
	while(1)
	{
		//????(????,????)
		printf("data:\n");
		
		for(i=0;i<240;i++)
		{
			printf("L");//???
			for(j=0;j < 320;j++)//??
			{
				if(i < 30)
				{
					color = 0xFFFF;
				}else if(i < 60)
				{
					color = 0xF800;//R
				}else if(i < 90)
				{
					color = 0x001F;//B
				}else if(i < 120)
				{
					color = 0x07E0;//G
				}else if(i < 160)
				{
					color = 0x07E0;
				}
				buff[j] = color;
			}
			//???????
			for(k=0;k<320;k++)
			{
				printf("%04X", buff[k]);//????
			}
			printf("\n");
		}
	}
}

int main(void)
{ 

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init(168);  //��ʼ����ʱ����
	uart_init(600000);		//��ʼ�����ڲ�����Ϊ115200
//	usart2_init(42,115200);		//��ʼ������2������Ϊ115200
//	LED_Init();					//��ʼ��LED 
 	QDTFT_Test_Demo();					//LCD��ʼ��  
	Mco1_8MHz_Init();
	while(OV7670_Init())//��ʼ��OV7670
	{
		delay_ms(200);
		printf("OV7670 FAIL:\n");
		delay_ms(200);
	}
	OV7670_Window_Set(12,174,120,160);	//���ô���	 
	TIM3_Int_Init(10000-1,8400-1);//10Khz����,1�����ж�һ�� 
	My_DCMI_Init();			//DCMI����
	DCMI_DMA_Init((u32)&buff,19200,DMA_MemoryDataSize_HalfWord,DMA_MemoryInc_Enable);//DCMI DMA����
//    M2M_DMA_Init((u32)&buff,19200,DMA_MemoryDataSize_HalfWord,DMA_MemoryInc_Enable);    
	DCMI_Start(); 		//��������
    
 	while(1)
	{	
	}
}
