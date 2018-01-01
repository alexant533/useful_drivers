#ifndef __74LS164_H__
#define __74LS164_H__

#define	 LS164_CLK_PIN    	      GPIO_Pin_4
#define  LS164_CLK_GPIO           GPIOA
#define  LS164_CLK_GPIO_CLK       RCC_APB2Periph_GPIOA
#define  LS164_CLK_H()            GPIOA->BSRR = LS164_CLK_PIN
#define  LS164_CLK_L()		        GPIOA->BRR = LS164_CLK_PIN

#define	 LS164_DATA_PIN    	      GPIO_Pin_5
#define  LS164_DATA_GPIO          GPIOA
#define  LS164_DATA_GPIO_CLK      RCC_APB2Periph_GPIOA
#define  LS164_DATA_H()           GPIOA->BSRR = LS164_DATA_PIN
#define  LS164_DATA_L()		        GPIOA->BRR = LS164_DATA_PIN

void Ls164Send(u8 data);
void Ls164Init(void);
void LedLineOut(u8 LineN);
#endif
