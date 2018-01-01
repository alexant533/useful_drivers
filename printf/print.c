/******************** (C) COPYRIGHT 2010 ZJCTP ******************************************************
* File Name          : print.c
* Author             : Langley
* Version            : V0.0.1
* Date               : 01/13/2010
* Description        : ��������printfʹ�õĴ��ڣ������ʡ����ںš�����Ӧ�Ĺܽź�
*                      
*****************************************************************************************************/
#include <includes.h>
#include "stm32_reg.h"
#include "print.h"

//��Щ����ֻ��ʹ��print()ʱ�������Ų������
#if PRINT_EN > 0
#if UART_INIT_SELECT >0 
/*********************************************************************************************************
 ** ��������: stm32_UsartSetup()
 ** ��������: ����printf����Ĵ���
 ** �䡡  ��: ��
 ** �䡡  ��: ��
 ** ����ģ��: �û���ʼ������ 
 ********************************************************************************************************/
void print_uart_init(void)
{
	/*----------------------------------------USART1 Used--------------------------------------*/
#if(UART_SEL == 1)

	{
		RCC_APB2ENR |= 0x00000001; // enable clock for Alternate Function
		AFIO_MAPR &= ~(1 << 2); // clear USART1 remap

#if((USART1_REMAP & 0x04) == 0x00) 				       // = 0x0ʱ������ӳ��
		{ // USART1 no remap
			RCC_APB2ENR |= 0x00000004; // enable clock for GPIOA
			GPIOA_CRH &= ~(0xFFUL << 4); // Clear PA9, PA10
			GPIOA_CRH |= (0x0BUL << 4); // USART1 Tx (PA9)  alternate output push-pull
			GPIOA_CRH |= (0x04UL << 8); // USART1 Rx (PA10) input floating
		}
#else 												   // = 0x4ʱ����ӳ��
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
		printf("�˿ڣ�1\r\n");
	}

	/*----------------------------------------USART2 Used--------------------------------------*/
#elif(UART_SEL == 2)

	{
		RCC_APB2ENR |= 0x00000001; // enable clock for Alternate Function
		AFIO_MAPR &= ~(1 << 3); // clear USART2 remap
#if((USART2_REMAP & 0x08) == 0x00) 				       // = 0x0ʱ������ӳ��
		{ // USART2 no remap
			RCC_APB2ENR |= 0x00000004; // enable clock for GPIOA
			GPIOA_CRL &= ~(0xFFUL << 8); // Clear PA2, PA3
			GPIOA_CRL |= (0x0BUL << 8); // USART2 Tx (PA2)  alternate output push-pull
			GPIOA_CRL |= (0x04UL << 12); // USART2 Rx (PA3)  input floating
		}
#else 												   // = 0x8ʱ����ӳ��
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
		printf("�˿ڣ�2\r\n");
	}

	/*----------------------------------------USART3 Used--------------------------------------*/
#elif(UART_SEL == 3)

	{
		RCC_APB2ENR |= 0x00000001; // enable clock for Alternate Function
		AFIO_MAPR &= ~(3 << 4); // clear USART3 remap
#if((USART3_REMAP & 0x30) == 0x00) 				       // = 0x0ʱ������ӳ��
		{ // USART3 no remap
			RCC_APB2ENR |= 0x00000008; // enable clock for GPIOB
			GPIOB_CRH &= ~(0xFFUL << 8); // Clear PB10, PB11
			GPIOB_CRH |= (0x0BUL << 8); // USART3 Tx (PB10) alternate output push-pull
			GPIOB_CRH |= (0x04UL << 12); // USART3 Rx (PB11) input floating
		}
#elif ((USART3_REMAP & 0x30) == 0x10) 			       // = 0x10ʱ����ӳ���
	{ // USART3 partial remap
		RCC_APB2ENR |= 0x00000001; // enable clock for Alternate Function
		AFIO_MAPR |= USART3_REMAP; // set   USART3 remap
		RCC_APB2ENR |= 0x00000010; // enable clock for GPIOC
		GPIOC_CRH &= ~(0xFFUL << 8); // Clear PC10, PC11
		GPIOC_CRH |= (0x0BUL << 8); // USART3 Tx (PC10) alternate output push-pull
		GPIOC_CRH |= (0x04UL << 12); // USART3 Rx (PC11) input floating
	}
#else 												   // = 0x30ʱ����ӳ���
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
		printf("�˿ڣ�3\r\n");
	}
#endif
}
#endif //end of UART_INIT_SELECT 
/*********************************************************************************************************
 ** ��������: my_send_str
 ** ��������: �മ�ڷ���һ����
 ** ��     ��:     p  �����׵�ַ
 ** ��     ��:     cnt ���͵��ֽ���
 **         
 ** ����ģ��: print();
 ** �޸���:
 ** �ա���:
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
 ** ��������: my_send_str
 ** ��������: �മ�ڷ���һ����
 ** ��     ��:     p  �����׵�ַ
 ** ��     ��:     cnt ���͵��ֽ���
 **         
 ** ����ģ��: print();
 **
 ** �ա���:
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
 ** ��������: myprintf
 ** ��������: printf()��ʵ�֣��������κο⡢������
 ** �䡡��: srt   ---���ƴ�
 **          .... ---��printfһ�����ɱ���� 
 **
 ** �䡡��: int ��������
 ** ����ģ��: printf_main()
 **-------------------------------------------------------------------------------------------------------
 ** �޸���:
 ** �ա���:
 **------------------------------------------------------------------------------------------------------
 ********************************************************************************************************/
int print(const char* str, ...)
{
	char *arp = 0;
	unsigned char c, f, r; //f�ĵ�1λ�����λ�Ƿ����'0' f =  1
	//f�ĵ�2λ�������ΪL��l��     f =| 2
	//f�ĵ�2λ��������-��+         f =| 4
	unsigned long val; //r�������Ľ���
	char s[16];
	int i, w, res, cc;
	w = f = r = 0; //fΪ��ʽ ,wΪ���

	arp = (char *) & str;
	arp += sizeof(str); //��arpָ����һ����������һ����ʽ����Ĳ���

	for (cc = res = 0; cc != MY_EOF; res += cc)
	{
		c = *str++;
		if (c == 0)
			break; /* End of string                                        */
		if (c != '%') /* Non escape cahracter                                 */
		{
			my_send_char(c);
			cc = 1; //cc���浱ǰѭ�����͵�����
			continue;
		}
		w = f = 0; //fΪ��ʽ ,wΪ���
		c = *str++;
		if (c == '0') /* Flag: '0' padding                                   */
		{
			f = 1;
			c = *str++; //����c = *(str);��ȡֵ�����str++ ;
			//f�ĵ�0λ������0������ c = *(str++);
		}
		while (c >= '0' && c <= '9') /* Precision                                           */
		{
			w = w * 10 + (c - '0'); //���������
			c = *str++;
		}
		if (c == 'l' || c == 'L') /* Prefix: Size is long int                            */
		{
			f |= 2;
			c = *str++; //f�ĵڶ�λ����Longǰ׺
		}
		if (c == 's' || c == 'S')
		{ /* Type is string                                      */
			my_send_str(*(char **) arp);
			arp += sizeof(char *); //arpָ����һ����ʽ�������
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
			r = 10; //r�������  /* Type is signed decimal */
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
			val = (unsigned long) (*((long *) arp)); //��ȡLong�Ͳ���,arpָ����һ������
			arp += sizeof(unsigned long); //������ȡ������ֵ
			//arpָ����һ����ʽ�������
		}
		else //û��'l'��־
		{
			if (c == 'd' || c == 'D') //�з�����
			{
				val = (unsigned long) (*((int*) arp)); //������ȡ������ֵ
				arp += sizeof(int); //arpָ����һ����ʽ�������
			} else //�޷�����
			{
				val = (unsigned long) (*((unsigned int*) arp)); //������ȡ������ֵ
				arp += sizeof(unsigned int); //arpָ����һ����ʽ�������
			}
		}
		/* Put numeral string */
		if (c == 'd' || c == 'D')
		{ //�����'d'ǰ׺��Ҫ�жϸջ�ȡ�Ĳ����������Ǹ�
			if (val >= 0x80000000)
			{ //���λΪ1˵���Ǹ���
				val = 0 - val;
				f |= 4; //f�ĵ���λ����"+/-"
			}
		}

		i = sizeof(s) - 1;
		s[i] = 0; //i=15,�������ڵ����һ���ó�'\0'
		do //�൱��i_to_a();����
		{
			c = (unsigned char) (val % r + '0'); //r�������
			if (c > '9') //�������9����16����
			{
				c += 7; //����16���� ת������Ӧ��'abc...'��Ҫ+7 :'
			} //'\58'+7='65'='a
			s[--i] = c; //�Ӻ��濪ʼ����
			val /= r; //�Ƶ���λ����ת
		}
		while (i && val); //i_to_a()����������i��val����0

		if (i && (f & 4)) //�Ǹ������'-'��
		{
			s[--i] = '-';
		}
		w = sizeof(s) - 1 - w; //����f�ĵ�1λ�������մ����'0'����' '
		while (i && i > w)
			s[--i] = (f & 1) ? '0' : ' ';
		cc = my_send_str(&s[i]);
	}
	arp = 0;
	return (cc == MY_EOF) ? cc : res;
}
#endif	  //end of PRINT_EN
