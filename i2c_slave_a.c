#ifndef uchar 
#define uchar unsigned char 
#endif 
#ifndef uint 
#define uint unsigned int 
#endif 
//#include<intrins.h> 
//#include <serial.h> 

#define ack 0 
#define noack 1 
#define false 0 
#define ture 1 
//#define EE_ADD 0x00 
#define EE_BYTEADD 0x00//// 
#define EE_WRITE 0xa0 
#define EE_READ 0xa1 

sbit scl="P1"^7;////STC2052.PIN19-SPICLK-SPIC 
sbit sda="P1"^5;////STC2052.PIN17-MOSI-SPID 
//bit ack_flag=0;////局部定义产生重入 

//void iic_sdelay(uchar); 
bit iic_start_decide(); 
bit iic_stop_decide(); 
void iic_ack_send(bit); 
bit iic_ack_decide(); 
//void iic_ack(); 
//void iic_noack(); 
bit iic_send(uchar);//reentrant; 
bit EEPROM_Imitate(uchar *p); 
//uchar iic_receive();//reentrant;///////////////////////////////////////////////////////////////// 
//bit iic_writestr(uchar*,uchar,uchar); 
//bit iic_writeabyte(uchar,uchar); 
//bit iic_readstr(uchar*,uchar,uchar); 
//bit iic_readabyte(void); 

bit iic_start_decide()////iic开始判断 
{ 
while(0==scl);////开始条件不满足 
while((1==scl)&&(1==sda));////开始条件正在建立,则等待 

if((1==scl)&&(0==sda))////开始 
{ 
while(1==scl);////等待到时钟线开始跳变 
return ture; 
} 
else 
return false; 
} 

bit iic_stop_decide() 
{ 
while(0==scl);////结束条件不满足 
while((1==scl)&&(0==sda));////结束条件正在建立,则等待 

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

bit iic_ack_decide() 
{ 
bit ack_flag;////局部变量 
//////////////////////////////////////sda=1;  ////8位发送完毕，释放数据线SDA，准备接收应答位 
while(0==scl);////等待SCL变高电平 
ack_flag=0; 
if(0==sda)////sda==0说明有回应 
ack_flag=1;////设置回应成功标志 
else 
ack_flag=0; 
//scl=0;    ////嵌住总线，准备发送或接收数据 
//iic_sdelay(4); 
while(1==scl); 
return(ack_flag); 
} 

bit iic_send(uchar sdata) //reentrant 
{uchar i; 
for(i=0;i<8;i++) 
{ 
sda=(bit)(sdata&0x80); 
sdata=sdata<<1; 
while(0==scl); 
while(1==scl);////检测scl，高电平时数据保持，scl跳到低电平才改变数据 
} 
return(iic_ack_decide());////判断主机有无回应 
} 

uchar iic_receive() //reentrant 
{uchar i; 
uchar rdata="0"; 
sda=1; 
for(i=0;i<8;i++) 
{ 
rdata<<=1; 
while(0==scl);////当时钟线为低时，数据无效，等待 
if(1==sda) 
rdata++; 
while(1==scl);////防止在一个高电平时读8次 
} 
//iic_sdelay(4); 
//scl=0;   ////嵌住总线，准备发送或接收数据////这里使用的是从模式 
//iic_sdelay(8); 
return (rdata); 
} 

/* 
void iic_sdelay(uchar i) 
{for(;i>0;i--); 
}*/ 

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
bit iic_writestr(uchar *s,uchar num) 
//bit iic_writeabyte(uchar s,uchar subadd) 
{ 
uchar i; 
//iic_start_check(); 

for(i=0;i<num;i++) 
{ 
if(!iic_send(*s)) 
//iic_send(s); 
return 0; 
s++; 
} 
if(iic_stop_decide()) 
return ture; 
} 
*/ 
/* 
选择性读 
选择性读操作允许主器件对寄存器的任意字节进行读操作主器件首先通过发送起始信号从器件 
地址和它想读取的字节数据的地址执行一个伪写操作在CAT24WC01/02/04/08/16 应答之后主器件重 
新发送起始信号和从器件地址此时R/W 位置1 CAT24WC01/02/04/08/16 响应并发送应答信号然后 
输出所要求的一个8 位字节数据主器件不发送应答信号但产生一个停止信号 
*/ 
//bit EEPROM_Imitate(uchar *p,uchar num) 
bit EEPROM_Imitate(uchar *p) 
{ 
//uchar i; 
uchar s; 
while(!iic_start_decide());//等待IIC开始 

s=iic_receive();////器件地址 
//serial_send(s); 
if(EE_WRITE==s) 
{ 
iic_ack_send(ack); ////回应 
//serial_send(s); 
} 
else 
{ 
iic_ack_send(noack); 
goto enderr; 
} 

s=iic_receive();////存储字节地址 
//serial_send(s); 

if(EE_BYTEADD==s) 
iic_ack_send(ack); ////回应 
else 
{ 
iic_ack_send(noack); 
goto enderr; 
} 

while(!iic_start_decide());//如果iic开始 

s=iic_receive();////器件地址 
//serial_send(s); 
if(EE_READ==s) ////主机要读EE的数据 
iic_ack_send(ack); ////回应 
else 
{ 
iic_ack_send(noack); 
goto enderr; 
} 

/*for(i=0;i<num;i++) 
{ 
if(!iic_send(*p))////如果主机没有回应，则发送失败 
return false; 
p++; 
}*/ 
while(iic_send(*p)){p++;};////判断有NOACK后停止发送，接着判断停止位 
if(iic_stop_decide()) 
return ture; 
enderr: 
scl=sda=1; 
return false; 
}