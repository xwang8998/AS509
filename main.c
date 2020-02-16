

/* --- Mobile: (86)13468751142 -------------------------------------*/
/* --- QQ:  441300942 ----------------------------------------------*/

#include	"STC15Fxxxx.H"
#include	"config.h"
//#include	"USART1.h"
#include	"delay.h"
#include	"i2c_slave.h"
#include	"moni_I2C_A.h"


#ifndef uchar 
#define uchar unsigned char 
#endif 
#ifndef uint 
#define uint unsigned int 
#endif

//sbit	PTSTA	=	P3^4;
//sbit	PTSTB	=	P3^5;

//sbit	si5342_i2c_a0	=	P1^2;
//sbit	si5342_i2c_a1	=	P1^3;

bit tst ;
bit tstb;

//本示例在Keil开发环境下请选择Intel的8058芯片型号进行编译
//假定测试芯片的工作频率为18.432MHz




//#define MAIN_Fosc		22118400L	//定义主时钟
//#define	BaudRate		115200UL	//选择波特率
//#define	Timer1_Reload	(65536UL -(MAIN_Fosc / 4 / BaudRate1))		//Timer 1 重装值， 对应300KHZ
//#define	Timer2_Reload	(65536UL -(MAIN_Fosc / 4 / BaudRate1))		//Timer 2 重装值， 对应300KHZ


/***************************************************************************/
//-----------------------------------------
//define baudrate const
//BAUD = 256 - FOSC/3/BAUDRATE/M (1T:M=1; 12T:M=12)
//NOTE: (FOSC/3/BAUDRATE) must be greater then 98, (RECOMMEND GREATER THEN 110)

//#define BAUD	0xF400                  // 1200bps @ 11.0592MHz
//#define BAUD	0xFA00                  // 2400bps @ 11.0592MHz
//#define BAUD	0xFD00                  // 4800bps @ 11.0592MHz
//#define BAUD	0xFE80                  // 9600bps @ 11.0592MHz
//#define BAUD	0xFF40                  //19200bps @ 11.0592MHz

#define BAUD	0xFFA0					//38400bps @ 11.0592MHz

//#define BAUD	0xEC00                  // 1200bps @ 18.432MHz
//#define BAUD	0xF600                  // 2400bps @ 18.432MHz
//#define BAUD	0xFB00                  // 4800bps @ 18.432MHz
//#define BAUD	0xFD80                  // 9600bps @ 18.432MHz
//#define BAUD	0xFEC0                  //19200bps @ 18.432MHz

//#define BAUD	0xFF60                  //38400bps @ 18.432MHz

//#define BAUD	0xE800                  // 1200bps @ 22.1184MHz
//#define BAUD	0xF400                  // 2400bps @ 22.1184MHz
//#define BAUD	0xFA00                  // 4800bps @ 22.1184MHz
//#define BAUD	0xFD00                  // 9600bps @ 22.1184MHz
//#define BAUD	0xFE80                  //19200bps @ 22.1184MHz
//#define BAUD	0xFF40                  //38400bps @ 22.1184MHz
//#define BAUD	0xFF80                  //57600bps @ 22.1184MHz

#define ID_ADDR_RAM 0x71                //STC104W系列ID号的存放在RAM区的地址
#define ID_ADDR_ROM 0x0ff9              //STC104W系列ID号的存放在ROM区的地址

//sfr AUXR = 0x8E;
sbit RXB = P3^0;                        //define UART TX/RX port
sbit TXB = P3^1;

typedef bit BOOL;
typedef unsigned char BYTE;
typedef unsigned int WORD;

BYTE TBUF,RBUF;
BYTE TDAT,RDAT;
BYTE TCNT,RCNT;
BYTE TBIT,RBIT;
BOOL TING,RING;
BOOL TEND,REND;
unsigned char gx_rxdata;
unsigned char gx_rxOK;
unsigned char gx_rx_cnt;

/*void tm0() interrupt 1 using 1
{
    if (RING)
    {
        if (--RCNT == 0)
        {
            RCNT = 3;                   //reset send baudrate counter
            if (--RBIT == 0)
            {
                RBUF = RDAT;            //save the data to RBUF
                RING = 0;               //stop receive
                //REND = 1;               //set receive completed flag
							  //--------------------------------
							  if(gx_rxOK == 0)
								{
									 //----------
									 if(gx_rx_cnt == 2)
									 {
										  gx_rx_cnt=0;
										  gx_rxdata = RBUF;
										  gx_rxOK = 1;
									 }
									 //----------
									 else if(gx_rx_cnt == 1)
									 {
										  if(RBUF == 0x55)
												 gx_rx_cnt=2;
											else
												 gx_rx_cnt=0;
									 }
									 //----------
									 else if(gx_rx_cnt == 0)
									 {
										  if(RBUF == 0xaa)
												 gx_rx_cnt=1;
									 }
								}
							  //--------------------------------
            }
            else
            {
                RDAT >>= 1;
                if (RXB) RDAT |= 0x80;	//shift RX data to RX buffer
            }
        }
    }
    else if (!RXB)
    {
        RING = 1;                       //set start receive flag
        RCNT = 4;                       //initial receive baudrate counter
        RBIT = 9;                       //initial receive bit number (8 data bits + 1 stop bit)
    }

    if (--TCNT == 0)
    {
        TCNT = 3;                       //reset send baudrate counter
        if (TING)                       //judge whether sending
        {
            if (TBIT == 0)
            {
                TXB = 0;                //send start bit
                TDAT = TBUF;            //load data from TBUF to TDAT
                TBIT = 9;               //initial send bit number (8 data bits + 1 stop bit)
            }
            else
            {
                TDAT >>= 1;             //shift data to CY
                if (--TBIT == 0)
                {
                    TXB = 1;
                    TING = 0;           //stop send
                    TEND = 1;           //set send completed flag
                }
                else
                {
                    TXB = CY;           //write CY to TX port
                }
            }
        }
    }
}	

 void UART_INIT()
{
    TING = 0;
    RING = 0;
    TEND = 1;
    REND = 0;
    TCNT = 0;
    RCNT = 0;
}

void un_UART_INIT()
{
    TING = 0;
    RING = 0;
    TEND = 0;
    REND = 0;
    TCNT = 0;
    RCNT = 0;
}
//-----------------------------------------
//Send UART data


void UART_SEND(BYTE dat)
{
    while (!TEND);
    TEND = 0;
    TBUF = dat;
    TING = 1;
}  */
//extern void config_init_si5342d(void);
//extern void config_44p1x_si5342d(void);
//extern void config_pll_si5342d(void);
//extern void configure_xK( si5342_revb_register_t *xp);
//extern void config_44p1_si5342d(void);
//extern void config_96k_si5342d(void);
//extern void config_88p2k_si5342d(void);
//extern void config_192k_si5342d(void);
//extern void config_176p4k_si5342d(void);
extern void config_init_si5340d(void);
extern void config_100p(void);
extern void si_spi_write(unsigned char xreg_addr,unsigned char xreg_data);
extern unsigned char si_spi_read(unsigned char xreg_addr);





sbit	Si_nOE	=	P3^3;
sbit  Si_Reset = P3^6;

//sbit  nFPGA_Reset	=	P2^2;
//sbit  nFPGA_Reset_tst	=	P1^0;

void my_delay(void)
{
	unsigned char j,i;
	for(i=0;i<200;i++)
	  {for(j=0;j<200;j++){;} }
	for(i=0;i<200;i++)
	  {for(j=0;j<200;j++){;} }
//	for(i=0;i<200;i++)
	  //{for(j=0;j<200;j++){;} }

}


void power_delay(void)
{
	unsigned char j,i;
	for(i=0;i<200;i++)
	  {for(j=0;j<200;j++){;} }
	
	
}


 BYTE code *cptr; 

//-----------------------------------------
//Send UART data




unsigned char xsample_rate,xsample_rate_old;
/******************** task main **************************/
void main(void)
{
	int i=0;
    unsigned char xaddr,xwrdata,xreaddata;
	power_delay();
	si_spi_init();

	
	

	/*
	//---- copy for uart -----
    TMOD = 0x00;                        //timer0 in 16-bit auto reload mode
    AUXR = 0x80;                        //timer0 working at 1T mode
    TL0 = BAUD;
    TH0 = BAUD>>8;                      //initial timer0 and set reload value
    TR0 = 1;                            //tiemr0 start running
    ET0 = 1;                            //enable timer0 interrupt
    PT0 = 1;                            //improve timer0 interrupt priority
    EA =  1;                            //open global interrupt switch
	 */
   
	
	  //-- config si5340D ------
/*	  UART_SEND(0xff);
	  xreaddata = si_spi_read(0x1);
	  UART_SEND(xreaddata); 
	  xreaddata = si_spi_read(0x2);
	  UART_SEND(xreaddata); 
	UART_SEND(0xff);		  */
	//UART_INIT();
	Si_Reset= 1 ;
	config_100p();
//	Si_nOE = 1; //Enable
	my_delay();my_delay();
	
	Si_nOE = 0; //Enable
	my_delay();
	while(1)
	{}

		

	
  }
  /*unsigned char xaddr,xwrdata,xreaddata;
	unsigned char i,xbyte,xbyteii,xcase,xcase_ii,xRBUF;
	unsigned char xH_S,xH_S_old,xRXB_old,xTXB_old;
	
		tst = 1;
		tstb = 1;
		xaddr = 0x0;
	  xsample_rate_old =0 ;
	  xcase = 0;
		xcase_ii = 0;
	
	  gx_rxOK = 0;
    gx_rx_cnt = 0;

	  //nFPGA_Reset_tst	= 0 ; nFPGA_Reset = 0;
		// *
	  H_S = 1;
	  power_delay();
	  si_spi_init();
	  xH_S_old = 0x3f;
	  if(H_S == 0) 
			 xH_S = 0;
	  else
			 xH_S = 1;
	  
	  if(xH_S==0)
		{
			xH_S = 0;
		//---- copy for uart -----
    TMOD = 0x00;                        //timer0 in 16-bit auto reload mode
    AUXR = 0x80;                        //timer0 working at 1T mode
    TL0 = BAUD;
    TH0 = BAUD>>8;                      //initial timer0 and set reload value
    TR0 = 1;                            //tiemr0 start running
    ET0 = 1;                            //enable timer0 interrupt
    PT0 = 1;                            //improve timer0 interrupt priority
    EA =  1;                            //open global interrupt switch

    UART_INIT();
	  Si_nOE = 1;Si_Reset	= 0 ; 
	  my_delay();
	
	  //-- config si5340D ------
	  UART_SEND(0xff);
	  xreaddata = si_spi_read(0x1);
	  UART_SEND(xreaddata); 
	  xreaddata = si_spi_read(0x2);
	  UART_SEND(xreaddata); 
		UART_SEND(0xff);
   }
	 else
	 {
		 RXB = 1; TXB = 1;
		 xRXB_old=0x3f;xTXB_old=0x3f;
		 xH_S = 1;
	 }

	
	Si_Reset	= 1 ; 
	config_init_si5340d();
	xsample_rate_old = 1;
	my_delay();
	my_delay();
	Si_nOE = 0; //Enable
	my_delay();
	
	while (1)
	{
	  if(H_S == 0) 
			 xH_S = 0;
		else
			 xH_S = 1;

		if(xH_S==0)
		{
		xaddr = 0;
		//------------------------------
    if(gx_rxOK == 1)
		{
			xcase_ii = gx_rxdata;
			gx_rxOK=0;
			//gx_rxcnt=0;
			UART_SEND(xcase_ii);
		}
		//-------------------------------------------------------	 
		if(xcase_ii != 0)
		{
			 Si_nOE = 1;
			 //------ config all ------------
			 xbyte = xcase_ii & 0x0f;
			 xbyteii = xcase_ii & 0x20;
			 if(xbyte == 0x07) 
			 { //config_22_cimos_si5340d(); 
				 if(xbyteii != 0)
					  config_22p5792_DIV512();
				  else
				    config_22p5792();
				}
			 else if(xbyte == 0x03) 
			 { //config_45_cimos_si5340d(); 
				 if(xbyteii != 0)
				 { config_45p1584_DIV512();}//UART_SEND(0xfd);}
				 else
				   {config_45p1584();}//UART_SEND(0xfc);}
				}
			 else if(xbyte == 0x02) 
			 { //config_90_cimos_si5340d(); 
				 if(xbyteii != 0)
					  config_90p3168_DIV512();
				 else
				    config_90p3168();
				}
			 else if(xbyte == 0) 
			 { //config_180_cimos_si5340d(); 
				 if(xbyteii != 0)
					 config_180P6336_DIV512();
				 else
					 config_180P6336();
				}


			 else if(xbyte == 0x08) 
			 { //config_24_cimos_si5340d(); 
				 if(xbyteii != 0)
					 config_24p576_DIV512();
				 else
					 config_24p576();
				}
				
			 else if(xbyte == 0x0c) 
			 { //config_49_cimos_si5340d(); 
				 if(xbyteii != 0)
					 config_49p152_DIV512();
				 else
					 config_49p152();
				 
				}

			 else if(xbyte == 0xe) 
			 { //config_98_cimos_si5340d(); 
				 if(xbyteii != 0)
					 config_98p3040_DIV512();
				 else
					 config_98p3040();
				}
				
			 else 	if(xbyte == 0xf) 
			 { //config_196_cmos_si5340d(); 
				 if(xbyteii != 0)
					 config_196p6080_DIV512();
				 else
					 config_196p6080();
				}



			 //-------LVDS--------------
			 xbyte = xcase_ii & 0x10;
			 xbyteii = xcase_ii & 0x0f;
			 if(xbyte == 0x10)
				 if((xbyteii!=0) && (xbyteii!=0xf))
				    config_si5340d_lvds(0,0);
				 else
						config_si5340d_lvds(1,0);
			 
			 //-------Enable------------
			 xbyte = xcase_ii & 0x80;
			 if(xbyte == 0 )//if(xbyte != 0 )//
				 Si_nOE = 1;
			 else
				 Si_nOE = 0;
			 
			 
			 //-------all finished ------------
			 UART_SEND(0xbd);
			 UART_SEND(xcase_ii);
			 xcase_ii = 0;
			 UART_SEND(0xbb);
			 //--------------------------------
     }	
	 }//if(xH_S==0) else 	 
	 else
	 {
		 TXB =1; RXB =1;
		 if((TXB == 1) &&(xTXB_old!=1))
		 {
			  xTXB_old = 1;
			  if(RXB == 1)
				{config_196p6080();xRXB_old = 1;}
				else
				{config_180P6336();xRXB_old = 0;}
				
		  }
		 if((TXB == 0) &&(xTXB_old!=0))
		 {
			  xTXB_old = 0;
			  if(RXB == 1)
				{config_196p6080();xRXB_old = 1;}
				else
				{config_180P6336();xRXB_old = 0;}
				config_si5340d_lvds_b(1);
		  }
     //-----------------------------
			if((RXB == 1) &&(xRXB_old !=1))
			{
			   xRXB_old = 1;
				 config_196p6080();
			}
		 if((RXB == 0) &&(xRXB_old !=0))
			{
			   xRXB_old = 0;
				 config_180P6336();
			}
			//----------------------------
		 
		 //----------------------
		 
	 }
	}
}




/*
		if(REND)				//如果接收完,把接收到的值存入接收buff
			{
				REND = 0;
				xRBUF = RBUF;
				UART_SEND(RBUF);
				switch(xcase)
				 {
					 case 0: 
						 if(xRBUF==0xaa) xcase = 1;
					   break;
					 case 1:
						 if(xRBUF==0x55) xcase = 2;
					   else xcase =0 ;
					   break;
           case 2:
              xcase = 0;
							xcase_ii = xRBUF;
             break; 
           default:
             xcase = 0;						 
				 }
			 }

*/


