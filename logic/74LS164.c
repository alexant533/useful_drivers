#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"

#include "74LS164.h"
/* 延时模块82615468 sp-320-12
 * */
static void delay(u32 t)
{
	u32 i;
	while(t--)
		for (i = 0; i < 1; i++);
}


void Ls164Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(LS164_CLK_GPIO_CLK | LS164_DATA_GPIO_CLK, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = LS164_CLK_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(LS164_CLK_GPIO, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = LS164_DATA_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(LS164_DATA_GPIO, &GPIO_InitStructure);
	LS164_CLK_H();
	LS164_DATA_H();
	
}
void Ls164Send(u8 data)
{
	u8 k;
	for(k = 8; k > 0; k--)
	{
		LS164_CLK_L();
		delay(1);
		if(data & 0x01)
			LS164_DATA_H();
		else
			LS164_DATA_L();
		LS164_CLK_H();        
		delay(1);
		data >>= 1;
	}	
}


/*                          _____________________________________________________________
  164SendTime1 Line0  0bit |                                                             |
               Line1  1bit |                                                             |
               Line2  2bit |                                                             |
               Line3  3bit |                                                             |
               Line4  4bit |                                                             |
               Line5  5bit |                                                             |
               Line6  6bit |                                                             |
               Line7  7bit |                                                             |
  164SendTime0 Line8  0bit |                                                             |
               Line9  1bit |                                                             |
               Line10 2bit |                                                             |
               Line11 3bit |                                                             |
               Line12 4bit |                                                             |
               Line13 5bit |                                                             |
               Line14 6bit |                                                             |
               Line15 7bit |_____________________________________________________________|                          
 */

void LedLineOut(u8 LineN)
{
	u16 LineData;
	LineN %= 16;                   //行取值范围
	LineData = ~(0x0001 << LineN); //取反低电平有效
	Ls164Send(LineData & 0xff);    //第1片164(Line0~7)
	Ls164Send(LineData >> 8);      //第0片164(Line8~15)
}



//end of file	
	

