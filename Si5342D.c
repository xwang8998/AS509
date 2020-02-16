//#include  "Si5342_49_147_96k.h"
//#include  "Si5342_24_147_48k.h"
//#include  "Si5342_24_0_48k.h"
//#include  "Si5342_0_24_48k.h"
//#include "Si5342_38MHz.h"
//#include	"moni_I2C_A.h"

//#include  "Si5342_3_147_48k.h"
//#include  "Si5342_2_147_44p1k.h/"

//#include  "Si5342_6_147_96k.h"
//#include  "Si5342_5_147_88p2k.h"

//#include  "Si5342_12_147_192k.h"
//#include  "Si5342_11_147_176p4k.h"

#include  "Si5342_196_147_48x.h"
#include  "Si5342_180_147_44p1x.h"
//#include  "Si5342_196_196_48x.h"
#include  "Si5342_196_182_48x.h"
//#include  "Si5342_196_156_48x.h"
#include  "Si5342_196_pll.h"

#include  "Si5342_196_off_48x.h"




extern void UART_SEND(unsigned char dat);


/*
#define cSi5342D_addr 0xd0 
void config_init_si5342d(void)
{
	unsigned int i;
	unsigned int xaddr;
	unsigned char xreg_addr,xchar,xchar_old,xcharB;
	
	xchar_old = 0xff;
	
	for(i=0;i<=SI5342_REVB_REG_CONFIG_NUM_REGS;i++)
		{
	    xaddr = si5342_revb_registers[i].address;
			xchar = xaddr >> 8;
			if(xchar_old != xchar)
			{
				 xchar_old = xchar;
				 set_i2c_slave_si(cSi5342D_addr,0x01,xchar);
			}
			xchar = xaddr;
			xcharB = si5342_revb_registers[i].value;
			set_i2c_slave_si(cSi5342D_addr,xchar,xcharB);
		}
}
*/


extern void si_spi_write(unsigned char xreg_addr,unsigned char xreg_data);
extern unsigned char si_spi_read(unsigned char xreg_addr);





//si5342_182_registers
//si5342_156_registers

void config_init_si5342d(void)
{
	unsigned int i;
	unsigned int xaddr;
	unsigned char xreg_addr,xchar,xchar_old,xcharB,xtest;
	
	xchar_old = 0xff;
	
	for(i=0;i<SI5342_REVB_REG_CONFIG_NUM_REGS;i++)
		{
	    xaddr = si5342_48x_registers[i].address;
			xchar = xaddr >> 8;
			if(xchar_old != xchar)
			{
				 xchar_old = xchar;
				 si_spi_write(0x01,xchar);//set page number
				 //UART_SEND(xchar);
			   xtest = si_spi_read(0x01);
			   //UART_SEND(xtest);
			}
			xchar = xaddr;
			//UART_SEND(xchar);
			xcharB = si5342_48x_registers[i].value;
			//UART_SEND(xcharB);
			si_spi_write(xchar,xcharB);
			xtest = si_spi_read(xchar);
			//UART_SEND(xtest);
		}
	
}



void config_44p1x_si5342d(void)
{
	unsigned int i;
	unsigned int xaddr;
	unsigned char xreg_addr,xchar,xchar_old,xcharB,xtest;
	
	xchar_old = 0xff;
	
	for(i=0;i<SI5342_REVB_REG_CONFIG_NUM_REGS;i++)
		{
	    xaddr = si5342_441x_registers[i].address;
			xchar = xaddr >> 8;
			if(xchar_old != xchar)
			{
				 xchar_old = xchar;
				 si_spi_write(0x01,xchar);//set page number
				 //UART_SEND(xchar);
			   xtest = si_spi_read(0x01);
			   //UART_SEND(xtest);
			}
			xchar = xaddr;
			//UART_SEND(xchar);
			xcharB = si5342_441x_registers[i].value;
			//UART_SEND(xcharB);
			si_spi_write(xchar,xcharB);
			xtest = si_spi_read(xchar);
			//UART_SEND(xtest);
		}
	
}



void config_pll_si5342d(void)
{
	unsigned int i;
	unsigned int xaddr;
	unsigned char xreg_addr,xchar,xchar_old,xcharB,xtest;
	
	xchar_old = 0xff;
	
	for(i=0;i<SI5342_REVB_REG_CONFIG_NUM_REGS;i++)
		{
	    xaddr = si5342_pll_registers[i].address;
			xchar = xaddr >> 8;
			if(xchar_old != xchar)
			{
				 xchar_old = xchar;
				 si_spi_write(0x01,xchar);//set page number
				 //UART_SEND(xchar);
			   xtest = si_spi_read(0x01);
			   //UART_SEND(xtest);
			}
			xchar = xaddr;
			//UART_SEND(xchar);
			xcharB = si5342_pll_registers[i].value;
			//UART_SEND(xcharB);
			si_spi_write(xchar,xcharB);
			xtest = si_spi_read(xchar);
			//UART_SEND(xtest);
		}
	
}

/*
void config_init_si5342d(void)
{
	unsigned int i;
	unsigned int xaddr;
	unsigned char xreg_addr,xchar,xchar_old,xcharB,xtest;
	
	xchar_old = 0xff;
	
	for(i=0;i<SI5342_REVB_REG_CONFIG_NUM_REGS;i++)
		{
	    xaddr = si5342_revb_registers[i].address;
			xchar = xaddr >> 8;
			if(xchar_old != xchar)
			{
				 xchar_old = xchar;
				 si_spi_write(0x01,xchar);//set page number
				 //UART_SEND(xchar);
			   xtest = si_spi_read(0x01);
			   //UART_SEND(xtest);
			}
			xchar = xaddr;
			//UART_SEND(xchar);
			xcharB = si5342_revb_registers[i].value;
			//UART_SEND(xcharB);
			si_spi_write(xchar,xcharB);
			xtest = si_spi_read(xchar);
			//UART_SEND(xtest);
		}
	
}

void config_44p1_si5342d(void)
{
	unsigned int i;
	unsigned int xaddr;
	unsigned char xreg_addr,xchar,xchar_old,xcharB,xtest;
	
	xchar_old = 0xff;
	
	for(i=0;i<SI5342_REVB_REG_CONFIG_NUM_REGS;i++)
		{
	    xaddr = si5342_44p1_registers[i].address;
			xchar = xaddr >> 8;
			if(xchar_old != xchar)
			{
				 xchar_old = xchar;
				 si_spi_write(0x01,xchar);//set page number
				 //UART_SEND(xchar);
			   xtest = si_spi_read(0x01);
			   //UART_SEND(xtest);
			}
			xchar = xaddr;
			//UART_SEND(xchar);
			xcharB = si5342_44p1_registers[i].value;
			//UART_SEND(xcharB);
			si_spi_write(xchar,xcharB);
			xtest = si_spi_read(xchar);
			//UART_SEND(xtest);
		}
	
}




void config_96k_si5342d(void)
{
	unsigned int i;
	unsigned int xaddr;
	unsigned char xreg_addr,xchar,xchar_old,xcharB,xtest;
	
	xchar_old = 0xff;
	
	for(i=0;i<SI5342_REVB_REG_CONFIG_NUM_REGS;i++)
		{
	    xaddr = si5342_96k_registers[i].address;
			xchar = xaddr >> 8;
			if(xchar_old != xchar)
			{
				 xchar_old = xchar;
				 si_spi_write(0x01,xchar);//set page number
				 xtest = si_spi_read(0x01);
			}
			xchar = xaddr;
			xcharB = si5342_96k_registers[i].value;
			si_spi_write(xchar,xcharB);
			xtest = si_spi_read(xchar);
		}
	
}

void config_88p2k_si5342d(void)
{
	unsigned int i;
	unsigned int xaddr;
	unsigned char xreg_addr,xchar,xchar_old,xcharB,xtest;
	
	xchar_old = 0xff;
	
	for(i=0;i<SI5342_REVB_REG_CONFIG_NUM_REGS;i++)
		{
	    xaddr = si5342_88p2_registers[i].address;
			xchar = xaddr >> 8;
			if(xchar_old != xchar)
			{
				 xchar_old = xchar;
				 si_spi_write(0x01,xchar);//set page number
				 xtest = si_spi_read(0x01);
			}
			xchar = xaddr;
			xcharB = si5342_88p2_registers[i].value;
			si_spi_write(xchar,xcharB);
			xtest = si_spi_read(xchar);
		}
	
}






void config_192k_si5342d(void)
{
	unsigned int i;
	unsigned int xaddr;
	unsigned char xreg_addr,xchar,xchar_old,xcharB,xtest;
	
	xchar_old = 0xff;
	
	for(i=0;i<SI5342_REVB_REG_CONFIG_NUM_REGS;i++)
		{
	    xaddr = si5342_192k_registers[i].address;
			xchar = xaddr >> 8;
			if(xchar_old != xchar)
			{
				 xchar_old = xchar;
				 si_spi_write(0x01,xchar);//set page number
				 xtest = si_spi_read(0x01);
			}
			xchar = xaddr;
			xcharB = si5342_192k_registers[i].value;
			si_spi_write(xchar,xcharB);
			xtest = si_spi_read(xchar);
		}
	
}

void config_176p4k_si5342d(void)
{
	unsigned int i;
	unsigned int xaddr;
	unsigned char xreg_addr,xchar,xchar_old,xcharB,xtest;
	
	xchar_old = 0xff;
	
	for(i=0;i<SI5342_REVB_REG_CONFIG_NUM_REGS;i++)
		{
	    xaddr = si5342_176p4_registers[i].address;
			xchar = xaddr >> 8;
			if(xchar_old != xchar)
			{
				 xchar_old = xchar;
				 si_spi_write(0x01,xchar);//set page number
				 xtest = si_spi_read(0x01);
			}
			xchar = xaddr;
			xcharB = si5342_176p4_registers[i].value;
			si_spi_write(xchar,xcharB);
			xtest = si_spi_read(xchar);
		}
	
}


*/

























/*
void configure_xK( si5342_revb_register_t * xp)
{
	unsigned int i;
	unsigned int xaddr;
	unsigned char xreg_addr,xchar,xchar_old,xcharB,xtest;
	
	xchar_old = 0xff;
	
	for(i=0;i<SI5342_REVB_REG_CONFIG_NUM_REGS;i++)
		{
	    xaddr = xp[i].address;
			xchar = xaddr >> 8;
			if(xchar_old != xchar)
			{
				 xchar_old = xchar;
				 si_spi_write(0x01,xchar);//set page number
				 UART_SEND(xchar);
			   xtest = si_spi_read(0x01);
			   UART_SEND(xtest);
			}
			xchar = xaddr;
			UART_SEND(xchar);
			xcharB = xp[i].value;
			UART_SEND(xcharB);
			si_spi_write(xchar,xcharB);
			xtest = si_spi_read(xchar);
			UART_SEND(xtest);
		}	
}
*/



