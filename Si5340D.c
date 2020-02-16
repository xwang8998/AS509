//#include  "Si5340-disable.h"
//#include  "Si5340_196_cmos.h"
//#include  "Si5340_180_cmos.h"
//#include  "Si5340_98_cmos.h"
//#include  "Si5340_90_cmos.h"

//#include  "Si5340_49_cmos.h"
//#include  "Si5340_45_cmos.h"
//#include  "Si5340_24_cmos.h"
//#include  "Si5340_22_cmos.h"

#include  "new/Si5340d_new_22p5792.h"
//#include  "new/Si5340d_new_45p1584.h"

extern void UART_SEND(unsigned char dat);
extern void si_spi_write(unsigned char xreg_addr,unsigned char xreg_data);
extern unsigned char si_spi_read(unsigned char xreg_addr);



void config_num_si5340d(unsigned int xleng,si5340_revb_register_t *xp)
{
	unsigned int i;
	unsigned int xaddr;
	unsigned char xreg_addr,xchar,xchar_old,xcharB,xtest;
	
	xchar_old = 0xff;
	
	for(i=0;i<xleng;i++)
		{
	    xaddr = (*xp)[i].address;
			xchar = xaddr >> 8;
			if(xchar_old != xchar)
			{
				 xchar_old = xchar;
				 si_spi_write(0x01,xchar);//set page number
			//	UART_SEND(xchar);
			//   xtest = si_spi_read(0x01);
			//   UART_SEND(xtest);
			}
			xchar = xaddr;
		//	UART_SEND(xchar);
			xcharB = (*xp)[i].value;
			si_spi_write(xchar,xcharB);
		//	UART_SEND(xcharB);
		//	xtest = si_spi_read(xchar);
		//	UART_SEND(xtest);
		}
	
}




//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
void config_init_si5340d(void)
{
 config_num_si5340d(SI5340_22p5792_NUM_REGS,&si5340_100p_registers);
	
}

//------------------------------------------------------------

 void config_100p(void)
{
	config_num_si5340d(SI5340_22p5792_NUM_REGS,&si5340_100p_registers);
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



