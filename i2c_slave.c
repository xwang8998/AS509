
#include	"i2c_slave.h"
#include	"STC15Fxxxx.H"


#ifndef uchar 
#define uchar unsigned char 
#endif 
#ifndef uint 
#define uint unsigned int 
#endif 


#define ack 0 
#define noack 1 
#define false 0 
#define ture 1 
//#define EE_ADD 0x00 
#define EE_BYTEADDR 0x00//// 
#define EE_WRITE 0xa0 
#define EE_READ 0xa1 

sbit scl=P3^0;////STC2052.PIN19-SPICLK-SPIC 
sbit sda=P3^1;////STC2052.PIN17-MOSI-SPID 

bit iic_start_wait(); 
bit iic_stop_wait(); 
void iic_ack_send(bit); 
bit iic_ack_wait(); 
bit iic_send_byte(uchar);//reentrant; 
bit i2c_device_Imitate(uchar *p); 

unsigned char gx_get_data;

void i2c_slave_config()
{
	 scl = 1;
	 sda = 1;
}

bit iic_start_wait()////iic开始判断 
{ 
	while(0==scl);////开始条件不满足 
	while(1==sda);//while((1==scl)&&(1==sda));////开始条件正在建立,则等待 

	if((1==scl)&&(0==sda))////开始 
		{ 
		while(1==scl);////等待到时钟线开始跳变 
		return ture; 
		} 
	else 
		return false; 
} 

bit iic_stop_wait() 
{ 
	while(0==scl);////结束条件不满足 
	while(0==sda);//while((1==scl)&&(0==sda));////结束条件正在建立,则等待 
	if((1==scl)&&(1==sda))////结束 
		return ture; 
	else 
		return false; 
} 


void iic_ack_send(bit a)////回应ACK或NOACK 
{ 
	if(ack==a) 
		sda=0; 
	else 
		sda=1; 
	while(0==scl);////等待SCL低电平 
	while(1==scl);////时钟线高电平时保持 
} 

bit iic_ack_wait() 
{ 
	bit ack_flag;////局部变量 
	//-----------------sda=1;  ////8位发送完毕，释放数据线SDA，准备接收应答位 
	while(0==scl);////等待SCL变高电平 
	ack_flag=0; 
	if(0==sda)////sda==0说明有回应 
		ack_flag=1;////设置回应成功标志 
	else 
		ack_flag=0; 
	while(1==scl); 
	return(ack_flag); 
} 

bit iic_send_byte(uchar sdata) //reentrant 
{	uchar i; 
	for(i=0;i<8;i++) 
	{		 
		sda=(bit)(sdata&0x80); 
		sdata=sdata<<1; 
		while(0==scl); 
		while(1==scl);////检测scl，高电平时数据保持，scl跳到低电平才改变数据 
	} 
	return(iic_ack_wait());////判断主机有无回应 
} 

uchar iic_receive_byte() //reentrant 
{	uchar i; 
	uchar rdata=0; 
	sda=1; 
	for(i=0;i<8;i++) 
		{ 
		rdata<<=1; 
		while(0==scl);////当时钟线为低时，数据无效，等待 
		if(1==sda) 
			rdata++; 
		while(1==scl);////防止在一个高电平时读8次 
		} 
	return (rdata); 
} 


/* 
用页写CAT24WC01 可一次写入8 个字节数据CAT24WC02/04/08/16 可以一次写入16 个字节的 
数据页写操作的启动和字节写一样不同在于传送了一字节数据后并不产生停止信号主器件被允许 
发送P CAT24WC01 P="7" CAT24WC02/04/08/16 P="15" 个额外的字节每发送一个字节数据后 
CAT24WC01/02/04/08/16 产生一个应答位并将字节地址低位加1 高位保持不变 
如果在发送停止信号之前主器件发送超过P+1个字节地址计数器将自动翻转先前写入的数据被 
覆盖 
接收到P+1字节数据和主器件发送的停止信号后CAT24CXXX启动内部写周期将数据写到数据区所 
有接收的数据在一个写周期内写入CAT24WC01/02/04/08/16 
*/ 
/* 
选择性读 
选择性读操作允许主器件对寄存器的任意字节进行读操作主器件首先通过发送起始信号从器件 
地址和它想读取的字节数据的地址执行一个伪写操作在CAT24WC01/02/04/08/16 应答之后主器件重 
新发送起始信号和从器件地址此时R/W 位置1 CAT24WC01/02/04/08/16 响应并发送应答信号然后 
输出所要求的一个8 位字节数据主器件不发送应答信号但产生一个停止信号 
*/ 

bit i2c_device_Imitate(uchar *p) 
{ 
	uchar s; 
	while(!iic_start_wait());//等待IIC开始 

	s=iic_receive_byte();////器件地址 
	if(EE_WRITE==s) 
		{ 
			iic_ack_send(ack); ////回应 
			s=iic_receive_byte();////存储字节地址 
			if(EE_BYTEADDR==s) 
			   {
						iic_ack_send(ack); ////回应 
					  s=iic_receive_byte();////存储数据
					  iic_ack_send(ack); ////回应
						//store s here;
					  gx_get_data = s << 2;
					  gx_get_data |= 0x03;
					  P3 = gx_get_data;					  
				 }
			else 
					{ 
						iic_ack_send(noack); 
						goto enderr; 
					} 
		} 
	else
		{ 
		iic_ack_send(noack); 
		goto enderr; 
		} 
	if(iic_stop_wait()) 
		return ture; 
enderr: 
	scl=sda=1; 
	return false; 
}






bit xx_i2c_device_Imitate(uchar *p) 
{ 
	uchar s; 
	while(!iic_start_wait());//等待IIC开始 

	s=iic_receive_byte();////器件地址 
	if(EE_WRITE==s) 
		{ 
			iic_ack_send(ack); ////回应 
		} 
	else 
		{ 
		iic_ack_send(noack); 
		goto enderr; 
		} 

	s=iic_receive_byte();////存储字节地址 
	if(EE_BYTEADDR==s) 
		iic_ack_send(ack); ////回应 
	else 
		{ 
			iic_ack_send(noack); 
			goto enderr; 
		} 
  //---------------------------------------------------
	while(!iic_start_wait());//如果iic开始 
	s=iic_receive_byte();////器件地址 
	if(EE_READ==s) ////主机要读EE的数据 
		iic_ack_send(ack); ////回应 
	else 
		{		 
			iic_ack_send(noack); 
			goto enderr; 
		} 

	while(iic_send_byte(*p)){p++;};////判断有NOACK后停止发送，接着判断停止位 
	if(iic_stop_wait()) 
		return ture; 
enderr: 
	scl=sda=1; 
	return false; 
}

