#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"

#include "74HC595.h"
/* 延时模块82615468 sp-320-12
 * */
static void delay(u32 t)
{
	u32 i;
	while(t--)
		for (i = 0; i < 1; i++);
}


void HC595Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(HC595_CLK_GPIO_CLK | HC595_DATA_GPIO_CLK | HC595_CS_GPIO_CLK, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = HC595_CLK_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(HC595_CLK_GPIO, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = HC595_DATA_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(HC595_DATA_GPIO, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = HC595_CS_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(HC595_CS_GPIO, &GPIO_InitStructure);
	HC595_CLK_H();
	HC595_DATA_H();
	HC595_CS_H();
	
}
void HC595Send(u8 data)
{
  u8 j;
  for (j = 8; j > 0; j--)
	{
    if(data & 0x80)
		   HC595_DATA_H();
		else
			HC595_DATA_L();
    HC595_CLK_L();              //上升沿发生移位
		delay(1);
    data <<= 1;
    HC595_CLK_H();
		delay(1);
  }
	//HC595Load();
}

void HC595Load(void)
{
	HC595_CS_L();
	HC595_CS_H();
}

/*
void LedRowOn(u8 Row7_0, u8 Row15_8, u8 Row16_23,u8 Row31_24)
{
	HC595Send(Row15_8);
	HC595Send(Row7_0);
	HC595Send(Row31_24);
	HC595Send(Row16_23);
	HC595Load();
}
*/

void LedRowOut(u32 Data)
{
	HC595Send(Data >> 24);
	HC595Send(Data >> 16);
	HC595Send(Data >> 8);
	HC595Send(Data >> 0);
	HC595Load();
}

//end of file	
	

