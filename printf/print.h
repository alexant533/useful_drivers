/******************** (C) COPYRIGHT 2010 ZJCTP ******************************************************
 * File Name          : print.h
 * Author             : Langley
 * Version            : V0.0.1
 * Date               : 01/13/2010
 * Description        : ��������printfʹ�õĴ��ڣ������ʡ����ںš�����Ӧ�Ĺܽź�
 *                      
 *****************************************************************************************************/
#ifndef __PRINT_H
#define __PRINT_H
//-------- <<< Use Configuration Wizard in Context Menu >>> -----------------
//=========================================================================== 
//  <e> Printf�����������
//     <o1> 1.����ѡ��
//          <1=>         ����1
//          <2=>         ����2
//			<3=>         ����3
//			<i> Ĭ�ϴ���1 
//     <o2> 2.������ 
//          <9600=>    9600 bsp
//          <14400=>   14400 bsp
//          <19200=>   19200 bsp
//          <28800=>   28800 bsp
//          <38400=>   38400 bsp
//          <56000=>   56000 bsp
//          <57600=>   57600 bsp
//          <115200=>  115200 bsp
//			<i> Ĭ��9600
//     <o3> 3.����1����ӳ��
//          <0=>         TX1 = PA9, RX1 = PA10
//          <1=>         TX1 = PB6, RX1 = PB7
//          <i> Ĭ��TX1 = PA9, RX1 = PA10
//     <o4> 4.����2����ӳ��
//          <0=>         TX2 = PA2, RX2 = PA3 
//          <1=>         TX2 = PD5, RX2 = PD6 
//			<i> Ĭ��TX2 = PA2, RX2 = PA3 
//     <o5> 5.����3����ӳ��
//          <0=>         TX3 = PB10, RX3 = PB11 
//          <1=>         TX3 = PC10, RX3 = PC11  
//          <3=>         TX3 = PB10, RX3 = PB11
//          <i> Ĭ��TX1 = PA9, RX1 = PA10  
//     <o6> 6.APB1ʱ��Ƶ��[Hz] <4000000-36000000>
//          <i> Default: 8000000  (8MHz)
//     <o7> 7.APB2ʱ��Ƶ��[Hz] <4000000-72000000>
//          <i> Ĭ��t: 8000000  (8MHz)
//     <o8> 8.���ڳ�ʼ������
//          <0=>         ʹ���Զ���  
//          <1=>         ʹ��ģ���ڲ� 
//          <i> Ĭ��ʹ��ģ���ڲ�,��Ҫ����������ڵ���print_init()
//  </e>
#define PRINT_EN                   0x1				
#define UART_SEL                   0x1				
#define BAUDRATE                   9600
#define USART1_REMAP		       0x0	//0x0:Tx->(PA9),Rx->(PA3);  0x4:Tx->(PB6),Rx->(PB7)
#define USART2_REMAP		       0x0	//0x0:Tx->(PA2),Rx->(PA3);  0x8:Tx->(PD5),Rx->(PD6)													   							 	
#define USART3_REMAP		       0x00	//0x0:Tx->(PB10),Rx->(PB11) 0x10:Tx->(PC10),Rx->(PC11) 0x30:Tx->(PD8),Rx->(PD9)												          	     
#define APB1CLK                    36000000
#define APB2CLK                    72000000
#define UART_INIT_SELECT           0x1				

#if PRINT_EN > 0
	void print_uart_init(void);
	int print(const char* str, ...);
	#if UART_INIT_SELECT > 0
		#define print_init() print_uart_init()
	#endif
	#define printf(...)  print(__VA_ARGS__)
#else
	#define print_init()
	#define printf(...)  
#endif

#endif

/***************************** the end of file ****************************/
