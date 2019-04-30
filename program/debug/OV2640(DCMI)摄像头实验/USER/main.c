#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "key.h"
#include "usmart.h"  
#include "usart2.h"  
#include "timer.h" 
#include "dcmi.h" 
#include "ov2640.h"
#include "QDTFT_demo.h"
//ALIENTEK ̽����STM32F407������ ʵ��35
//����ͷ ʵ�� -�⺯���汾
//����֧�֣�www.openedv.com
//�Ա����̣�http://eboard.taobao.com  
//������������ӿƼ����޹�˾  
//���ߣ�����ԭ�� @ALIENTEK
u16 buff[120] [160] __attribute__ ((at(0X20001000)));

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
		
		for(i=0;i<120;i++)
		{
			printf("L");//???
			for(j=0;j < 160;j++)//??
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
			for(k=0;k<160;k++)
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
	uart_init(115200);		//��ʼ�����ڲ�����Ϊ115200
	
 	Mco1_8MHz_Init();					
	
//	QDTFT_Test_Demo();
	while(OV2640_Init())//��ʼ��OV7670
	{
//		LCD_ShowString(30,130,240,16,16,"OV7670 ERR");
		delay_ms(200);
//	    LCD_Fill(30,130,239,170,WHITE);
		printf("OV2640 FAIL:\n");
		delay_ms(200);
	}
	OV2640_OutSize_Set(160,120);//OV7670�����������
	printf("OV2640 OK:\n");
	delay_ms(200);
	My_DCMI_Init();			//DCMI����
	DCMI_DMA_Init((u32)&buff,19200,DMA_MemoryDataSize_HalfWord,DMA_MemoryInc_Enable);//DCMI DMA����  
	DCMI_Start(); 		//��������
	
 	while(1)
	{	
	}
}
