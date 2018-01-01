#ifndef __74HC595_H__
#define __74HC595_H__

#define	HC595_CLK_PIN    	      GPIO_Pin_6
#define HC595_CLK_GPIO          GPIOA
#define HC595_CLK_GPIO_CLK      RCC_APB2Periph_GPIOA
#define HC595_CLK_H()           GPIOA->BSRR = HC595_CLK_PIN
#define HC595_CLK_L()		        GPIOA->BRR  = HC595_CLK_PIN

#define	HC595_CS_PIN    	      GPIO_Pin_7
#define HC595_CS_GPIO           GPIOA
#define HC595_CS_GPIO_CLK       RCC_APB2Periph_GPIOA
#define HC595_CS_H()            GPIOA->BSRR = HC595_CS_PIN
#define HC595_CS_L()		        GPIOA->BRR  = HC595_CS_PIN

#define	HC595_DATA_PIN    	    GPIO_Pin_10
#define HC595_DATA_GPIO         GPIOE
#define HC595_DATA_GPIO_CLK     RCC_APB2Periph_GPIOE
#define HC595_DATA_H()          GPIOE->BSRR = HC595_DATA_PIN
#define HC595_DATA_L()		      GPIOE->BRR  = HC595_DATA_PIN

void HC595Send(u8 data);
void HC595Init(void);
void HC595Load(void);
void LedRowOn(u8 Row7_0, u8 Row15_8, u8 Row16_23,u8 Row31_24);
void LedRowOut(u32 Data);

#endif
