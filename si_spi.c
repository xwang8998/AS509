#include	"STC15Fxxxx.H"

/*
set address : 0000_0000  + 8-bit address
write data  : 0100_0000  + 8-bit data
read data   : 1000_0000  + 8-bit data

*/

#define Set_Addr_CMD   0x00
#define Write_reg_CMD  0x40
#define Read_reg_CMD   0x80

sbit	si_spi_cs  = P1^2; 
sbit	si_spi_sdo = P1^3; // master in  change for AS313
sbit	si_spi_sdi  = P1^4; // master out  change for AS313
//sbit	si_spi_sdi = P1^3; // master in
//sbit	si_spi_sdo = P1^4; // master out
sbit	si_spi_clk = P1^5; 

//extern void UART_SEND(unsigned char dat);

void si_delay(void)
{
	unsigned char i,j;
	for(i=0;i<2;i++)
	  {
			for(j=0;j<8;j++){;}
		}
	
}

void si_spi_init(void)
{
	si_spi_cs =  1;
	si_spi_sdi = 1;
	si_spi_sdo = 1;
	si_spi_clk = 1;
}

void si_unselect(void)
{
	si_spi_cs = 1;
	si_spi_clk = 0;
	//--------------
	si_delay();
	si_spi_clk = 1;
	si_delay();
	si_spi_clk = 0;
	//--------------
	si_delay();
	si_spi_clk = 1;
	si_delay();
	si_spi_clk = 0;
	//---------------
	si_delay();
	si_spi_clk = 1;
	si_delay();
	si_spi_clk = 0;
	//---------------
	si_delay();
} // last :si_spi_clk = 0; si_spi_cs = 1;

unsigned char si_16_bit_sip(unsigned char xa,unsigned char xb)
{
	 unsigned int xwr ,xrd;
	 unsigned char i,xret;
	 xwr = xa;
	 xwr = xwr << 8;
	 xwr = xwr + xb;
	 xrd = 0;
	 //--------------
	 si_unselect();//last :si_spi_clk = 0; si_spi_cs = 1;
	 si_spi_cs = 0;
	 si_delay();
	 for(i=0;i<16;i++)
	  {
			//-----------------
			if((xwr & 0x8000) != 0)
					si_spi_sdo = 1;
			else
					si_spi_sdo = 0;
			xwr = xwr << 1;
			si_delay();
			//-----------------
			si_spi_clk = 1;
			si_delay();
			//-----------------
			si_spi_sdi = 1;
			xrd = xrd << 1;
			if(si_spi_sdi==1)
				 xrd += 1;
			si_delay();
			//------------------
			si_spi_clk = 0;
		}
	si_unselect();	
	xret = xrd;
	return(xret);
}


/*
#define Set_Addr_CMD   0x00;
#define Write_reg_CMD  0x40;
#define Read_reg_CMD   0x80;
*/

void si_spi_write(unsigned char xreg_addr, unsigned char xreg_data)
{
	si_16_bit_sip(Set_Addr_CMD,xreg_addr);
	si_16_bit_sip(Write_reg_CMD,xreg_data);
}

unsigned char si_spi_read(unsigned char xreg_addr)
{
	unsigned char xret;
	si_16_bit_sip(Set_Addr_CMD,xreg_addr);
	xret = si_16_bit_sip(Read_reg_CMD,0x00);
	return(xret);
}
