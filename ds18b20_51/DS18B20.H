/***********************************************************/
/*     ________    ___   ___                 __________    */
/*    /_____  /\  /  /\ /  /\               /  _______/\   */
/*    \___/ / /   |  |/   / /  _________   /  /_______\/   */
/*       / / /     |    / /   /________/\ /  ______ /\     */
/*     / / /      /  / \ /    \________\//  /\______\/     */
/*   / /_/___   /  / /\ \               /  / /             */
/*  /_______/\ /__/ / |__\             /__/ /              */
/*  \_______\/ \__\/  \___\            \__\/               */
/*                                                         */
/***********************************************************/
//////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////*以下操作是产生一线时序*///////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
#define Delay1us() WDT();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_()
//22.1184MHz 时钟每个周期45.2ns 22个NOP为0.9946us
void Delay5us(unsigned char i)
{ 
	do{
		i--;
		Delay1us();
        Delay1us();
        Delay1us();
        Delay1us();
        Delay1us();
	  }while(i!=0);
}
///////////////////////////////////////////////////////////////////////////////////////////
bit NetReset()//1ms
{
   bit result; 
   unsigned char temp;
   TS=0;            
   Delay5us(100);   //500us
   TS=1;            
   Delay5us(12);    //60us
   result=TS;            
   for(temp=0;temp<10;temp++)//100us
   {	            
      Delay5us(2);                     
	    result&=TS;                                
   }                
   Delay5us(68); //340us                                  
   return result;
}     
/***************************************************************************************/
bit NetReadBit()//80us
{
	bit result;
	TS=0;        
	Delay5us(2); 
	TS=1;
	Delay5us(2); 
	result=TS;   //exampled at 20us                                   
	Delay5us(12);//delay 60us
	
    return result;
}     
/*****************************************************************************************/
void NetWriteBit(unsigned char sendbit)//80us
{
  TS=0;                       
	Delay5us(1);
	TS=sendbit;
	Delay5us(13);       
	TS=1;        
	Delay5us(2);         
}               
/*******************************************************************************************/
void NetWriteByte(unsigned char sendbyte)//0.64ms
{
   unsigned char i;
   for (i = 0; i < 8; i++)
   {
       NetWriteBit((bit)(sendbyte&0x01));
       sendbyte >>= 1;
   }
}
/************************************************************/
unsigned char NetReadByte()//0.64ms
{
   unsigned char i;
   unsigned char result = 0;
   for (i = 0; i < 8; i++)
   {
       result|=((unsigned char)NetReadBit())<<i;
   }
   return result;
}
/************************************************************/
int NetGetTemp()
{
    union div{
		        unsigned char a[2];
				int  b;
			 }div;
	  unsigned char i;
	  NetReset();
    NetWriteByte(0xcc);
    NetWriteByte(0x44);                           
    for(i=0;i<251;i++)  //delay 960ms beyond 870ms
	  {
       Delay5us(255);
       Delay5us(255);
       Delay5us(255);                                                                  
	  }
    NetReset();
    NetWriteByte(0xcc);
    NetWriteByte(0xbe);
    div.a[1]=NetReadByte();
	  div.a[0]=NetReadByte();
    NetReset();
	  return div.b;
}          
/******************************************************************/     
int ReadTemp()//4.6ms
{
    union div{
		        unsigned char a[2];
				int  b;
			 }div;
    NetReset();//1ms
    NetWriteByte(0xcc);//0.64ms
    NetWriteByte(0xbe);//0.64ms
    div.a[1]=NetReadByte();//0.64ms
	  div.a[0]=NetReadByte();//0.64ms
    NetReset();//1ms
	  return div.b;
}   
/************************************************************/
void BeginTempCONV()//2.3ms
{
	 NetReset();//1ms
   NetWriteByte(0xcc);//0.64ms
   NetWriteByte(0x44);//0.64ms                           
}          
