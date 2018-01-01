/******************** (C) COPYRIGHT 2010 ZJCTP ******************************************************
* File Name          : print.c
* Author             : Langley
* Version            : V0.0.1
* Date               : 01/13/2010
* Description        : 用于配置printf使用的串口，波特率、串口号、及对应的管脚号
*                      
*****************************************************************************************************/
#include <includes.h>
#include "stm32_reg.h"
#include "print.h"

//这些函数只有使用print()时，函数才参与编译
#if PRINT_EN > 0
#if UART_INIT_SELECT >0 
/*********************************************************************************************************
 ** 函数名称: stm32_UsartSetup()
 ** 功能描述: 配置printf输出的串口
 ** 输　  入: 无
 ** 输　  出: 无
 ** 调用模块: 用户初始化函数 
 ********************************************************************************************************/
void print_uart_init(void)
{
	/*----------------------------------------USART1 Used--------------------------------------*/
#if(UART_SEL == 1)

	{
		RCC_APB2ENR |= 0x00000001; // enable clock for Alternate Function
		AFIO_MAPR &= ~(1 << 2); // clear USART1 remap

#if((USART1_REMAP & 0x04) == 0x00) 				       // = 0x0时，不重映射
		{ // USART1 no remap
			RCC_APB2ENR |= 0x00000004; // enable clock for GPIOA
			GPIOA_CRH &= ~(0xFFUL << 4); // Clear PA9, PA10
			GPIOA_CRH |= (0x0BUL << 4); // USART1 Tx (PA9)  alternate output push-pull
			GPIOA_CRH |= (0x04UL << 8); // USART1 Rx (PA10) input floating
		}
#else 												   // = 0x4时，重映射
		{ // USART1    remap
			RCC_APB2ENR |= 0x00000001; // enable clock for Alternate Function
			AFIO_MAPR |= USART1_REMAP; // set   USART1 remap
			RCC_APB2ENR |= 0x00000008; // enable clock for GPIOB
			GPIOB_CRL &= ~(0xFFUL << 24); // Clear PB6, PB7
			GPIOB_CRL |= (0x0BUL << 24); // USART1 Tx (PB6)  alternate output push-pull
			GPIOB_CRL |= (0x04UL << 28); // USART1 Rx (PB7) input floating
		}
#endif
		RCC_APB2ENR |= 0x00004000; // enable clock for USART1
		USART1_BRR = USART_DIV(APB2CLK, BAUDRATE); // set baudrate
		USART1_CR1 = 0; // set Data bits
		USART1_CR2 = 0; // set Stop bits
		USART1_CR3 = 0; // Set Flow Control
		USART1_CR1 |= (0x00000004 | 0x00000008); // RX, TX enable
		USART1_CR1 |= 0x00002000; // USART enable
		printf("端口：1\r\n");
	}

	/*----------------------------------------USART2 Used--------------------------------------*/
#elif(UART_SEL == 2)

	{
		RCC_APB2ENR |= 0x00000001; // enable clock for Alternate Function
		AFIO_MAPR &= ~(1 << 3); // clear USART2 remap
#if((USART2_REMAP & 0x08) == 0x00) 				       // = 0x0时，不重映射
		{ // USART2 no remap
			RCC_APB2ENR |= 0x00000004; // enable clock for GPIOA
			GPIOA_CRL &= ~(0xFFUL << 8); // Clear PA2, PA3
			GPIOA_CRL |= (0x0BUL << 8); // USART2 Tx (PA2)  alternate output push-pull
			GPIOA_CRL |= (0x04UL << 12); // USART2 Rx (PA3)  input floating
		}
#else 												   // = 0x8时，重映射
	{ // USART2    remap
		RCC_APB2ENR |= 0x00000001; // enable clock for Alternate Function
		AFIO_MAPR |= USART2_REMAP; // set   USART2 remap
		RCC_APB2ENR |= 0x00000020; // enable clock for GPIOD
		GPIOD_CRL &= ~(0xFFUL << 20); // Clear PD5, PD6
		GPIOD_CRL |= (0x0BUL << 20); // USART2 Tx (PD5)  alternate output push-pull
		GPIOD_CRL |= (0x04UL << 24); // USART2 Rx (PD6)  input floating
	}
#endif
		RCC_APB1ENR |= 0x00020000; // enable clock for USART2
		USART2_BRR = USART_DIV(APB1CLK, BAUDRATE); // set baudrate
		USART2_CR1 = 0 | 0; // set Data bits  set Parity
		USART2_CR2 = 0; // set Stop bits
		USART2_CR1 |= (0x00000004 | 0x00000008); // RX, TX enable
		USART2_CR1 |= 0x00002000; // USART enable
		printf("端口：2\r\n");
	}

	/*----------------------------------------USART3 Used--------------------------------------*/
#elif(UART_SEL == 3)

	{
		RCC_APB2ENR |= 0x00000001; // enable clock for Alternate Function
		AFIO_MAPR &= ~(3 << 4); // clear USART3 remap
#if((USART3_REMAP & 0x30) == 0x00) 				       // = 0x0时，不重映射
		{ // USART3 no remap
			RCC_APB2ENR |= 0x00000008; // enable clock for GPIOB
			GPIOB_CRH &= ~(0xFFUL << 8); // Clear PB10, PB11
			GPIOB_CRH |= (0x0BUL << 8); // USART3 Tx (PB10) alternate output push-pull
			GPIOB_CRH |= (0x04UL << 12); // USART3 Rx (PB11) input floating
		}
#elif ((USART3_REMAP & 0x30) == 0x10) 			       // = 0x10时，重映射此
	{ // USART3 partial remap
		RCC_APB2ENR |= 0x00000001; // enable clock for Alternate Function
		AFIO_MAPR |= USART3_REMAP; // set   USART3 remap
		RCC_APB2ENR |= 0x00000010; // enable clock for GPIOC
		GPIOC_CRH &= ~(0xFFUL << 8); // Clear PC10, PC11
		GPIOC_CRH |= (0x0BUL << 8); // USART3 Tx (PC10) alternate output push-pull
		GPIOC_CRH |= (0x04UL << 12); // USART3 Rx (PC11) input floating
	}
#else 												   // = 0x30时，重映射此
	{ // USART3 full remap
		RCC_APB2ENR |= 0x00000001; // enable clock for Alternate Function
		AFIO_MAPR |= USART3_REMAP; // set   USART3 remap
		RCC_APB2ENR |= 0x00000020; // enable clock for GPIOD
		GPIOD_CRH &= ~(0xFFUL << 0); // Clear PD8, PD9
		GPIOD_CRH |= (0x0BUL << 0); // USART3 Tx (PD8) alternate output push-pull
		GPIOD_CRH |= (0x04UL << 4); // USART3 Rx (PD9) input floating
	}
#endif
		RCC_APB1ENR |= 0x00040000; // enable clock for USART3

		USART3_BRR = USART_DIV(APB1CLK, BAUDRATE); // set baudrate
		USART3_CR1 = 0; // set Data bits	 set Parity
		USART3_CR2 = 0; // set Stop bits
		USART3_CR1 |= (0x00000004 | 0x00000008); // RX, TX enable
		USART3_CR1 |= 0x00002000; // USART enable
		printf("端口：3\r\n");
	}
#endif
}
#endif //end of UART_INIT_SELECT 
/*********************************************************************************************************
 ** 函数名称: my_send_str
 ** 功能描述: 多串口发送一个串
 ** 输     入:     p  串的首地址
 ** 输     出:     cnt 发送的字节数
 **         
 ** 调用模块: print();
 ** 修改人:
 ** 日　期:
 **------------------------------------------------------------------------------------------------------
 ********************************************************************************************************/
void my_send_char (char ch)
{
#if(UART_SEL == 1)

	{
		while (!(USART1_SR & USART_FLAG_TXE));
		USART1_DR = (ch & 0x1FF);
	}
#elif(UART_SEL == 2)

	{
		while (!(USART2_SR & USART_FLAG_TXE));
		USART2_DR = (ch & 0x1FF);
	}
#elif(UART_SEL == 3)

	{
		while (!(USART3_SR & USART_FLAG_TXE));
		USART3_DR = (ch & 0x1FF);
	}
#endif
}
/*********************************************************************************************************
 ** 函数名称: my_send_str
 ** 功能描述: 多串口发送一个串
 ** 输     入:     p  串的首地址
 ** 输     出:     cnt 发送的字节数
 **         
 ** 调用模块: print();
 **
 ** 日　期:
 **------------------------------------------------------------------------------------------------------
 ********************************************************************************************************/
u16 my_send_str(char *p)
{
	u16 c;
	c = 0;
	while (*p != '\0')
	{
		my_send_char(*p);
		p++;
		c++;
	}
	return c;
}

/*--------------------------------------end of stm32_UsartSetup()--------------------------------*/

/*********************************************************************************************************
 ** 函数名称: myprintf
 ** 功能描述: printf()的实现，不依赖任何库、编译器
 ** 输　入: srt   ---控制串
 **          .... ---与printf一样，可变参数 
 **
 ** 输　出: int 参数错误
 ** 调用模块: printf_main()
 **-------------------------------------------------------------------------------------------------------
 ** 修改人:
 ** 日　期:
 **------------------------------------------------------------------------------------------------------
 ********************************************************************************************************/
int print(const char* str, ...)
{
	char *arp = 0;
	unsigned char c, f, r; //f的第1位代表空位是否填充'0' f =  1
	//f的第2位代表参数为L或l形     f =| 2
	//f的第2位代表数的-或+         f =| 4
	unsigned long val; //r代表数的进制
	char s[16];
	int i, w, res, cc;
	w = f = r = 0; //f为格式 ,w为宽度

	arp = (char *) & str;
	arp += sizeof(str); //将arp指向下一个参数，第一个格式输出的参数

	for (cc = res = 0; cc != MY_EOF; res += cc)
	{
		c = *str++;
		if (c == 0)
			break; /* End of string                                        */
		if (c != '%') /* Non escape cahracter                                 */
		{
			my_send_char(c);
			cc = 1; //cc保存当前循环发送的数据
			continue;
		}
		w = f = 0; //f为格式 ,w为宽度
		c = *str++;
		if (c == '0') /* Flag: '0' padding                                   */
		{
			f = 1;
			c = *str++; //等于c = *(str);先取值，最后str++ ;
			//f的第0位代表用0填充对齐 c = *(str++);
		}
		while (c >= '0' && c <= '9') /* Precision                                           */
		{
			w = w * 10 + (c - '0'); //计算对齐宽度
			c = *str++;
		}
		if (c == 'l' || c == 'L') /* Prefix: Size is long int                            */
		{
			f |= 2;
			c = *str++; //f的第二位代表Long前缀
		}
		if (c == 's' || c == 'S')
		{ /* Type is string                                      */
			my_send_str(*(char **) arp);
			arp += sizeof(char *); //arp指向下一个格式输出参数
			continue; /* go to for()                                         */
		}
		if (c == 'c' || c == 'C')
		{ /* Type is character */
			my_send_char(*((int *) arp));
			arp += sizeof(int);
			cc = 1;
			continue; /* go to for()                                         */
		}

		r = 0;
		if (c == 'd' || c == 'D')
		{
			r = 10; //r代表进制  /* Type is signed decimal */
		}

		if (c == 'u' || c == 'U')
		{
			r = 10; /* Type is unsigned decimal */
		}

		if (c == 'X' || c == 'x')
		{
			r = 16; /* Type is unsigned hexdecimal */
		}

		if (r == 0)
		{
			break; /* Unknown type */
		}

		if (f & 2)
		{ /* Get the value */
			val = (unsigned long) (*((long *) arp)); //获取Long型参数,arp指向下一个参数
			arp += sizeof(unsigned long); //按类型取出参数值
			//arp指向下一个格式输出参数
		}
		else //没有'l'标志
		{
			if (c == 'd' || c == 'D') //有符号数
			{
				val = (unsigned long) (*((int*) arp)); //按类型取出参数值
				arp += sizeof(int); //arp指向下一个格式输出参数
			} else //无符号数
			{
				val = (unsigned long) (*((unsigned int*) arp)); //按类型取出参数值
				arp += sizeof(unsigned int); //arp指向下一个格式输出参数
			}
		}
		/* Put numeral string */
		if (c == 'd' || c == 'D')
		{ //如果是'd'前缀就要判断刚获取的参数是正还是付
			if (val >= 0x80000000)
			{ //最高位为1说明是负的
				val = 0 - val;
				f |= 4; //f的第三位代表"+/-"
			}
		}

		i = sizeof(s) - 1;
		s[i] = 0; //i=15,将数组内的最后一个置成'\0'
		do //相当于i_to_a();函数
		{
			c = (unsigned char) (val % r + '0'); //r代表进制
			if (c > '9') //如果大于9，是16进制
			{
				c += 7; //对于16进制 转换到对应的'abc...'需要+7 :'
			} //'\58'+7='65'='a
			s[--i] = c; //从后面开始保存
			val /= r; //移到高位继续转
		}
		while (i && val); //i_to_a()结束条件，i和val都非0

		if (i && (f & 4)) //是负数添加'-'号
		{
			s[--i] = '-';
		}
		w = sizeof(s) - 1 - w; //根据f的第1位，决定空处填充'0'还是' '
		while (i && i > w)
			s[--i] = (f & 1) ? '0' : ' ';
		cc = my_send_str(&s[i]);
	}
	arp = 0;
	return (cc == MY_EOF) ? cc : res;
}
#endif	  //end of PRINT_EN
