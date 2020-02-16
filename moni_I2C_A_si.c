/*********************************************************************************************************************************/
#include	"STC15Fxxxx.H"

#ifndef uchar 
#define uchar unsigned char 
#endif 
#ifndef uint 
#define uint unsigned int 
#endif 

//#define WD7188	0X40
//#define RD7188	0X41 

sbit	pSDA_si	=	P1^4;//P3^2;  //7 
sbit	pSCL_si	=	P1^5;//P3^3;  //8


bit   bACK_si;

unsigned char xdelay_si;


//extern uchar	keyedA, keyedB;	
//extern bit tst ;
//extern bit tstb;

void iicStart_si()  //if scl==0 it crashed;
   {
    uchar i2cStartI;
    pSDA_si=1;
    pSCL_si=1;
		//0913 while(pSCL_si==0){;}
    for(i2cStartI=0;i2cStartI<60;i2cStartI++){_nop_();}
    pSDA_si=0;
    for(i2cStartI=0;i2cStartI<60;i2cStartI++){_nop_();}
    pSCL_si=0;
		for(i2cStartI=0;i2cStartI<60;i2cStartI++){_nop_();}
    }

void iicwrbit_0_si()
     {
        //uchar i2cWrbyt0I;
				pSCL_si=0;
			  for(xdelay_si=0;xdelay_si<60;xdelay_si++){_nop_();}
        pSDA_si=0;
			  for(xdelay_si=0;xdelay_si<60;xdelay_si++){_nop_();}
        pSCL_si=1;
        for(xdelay_si=0;xdelay_si<60;xdelay_si++){_nop_();}
        pSCL_si=0;       
				for(xdelay_si=0;xdelay_si<60;xdelay_si++){_nop_();}
        
     }

 void iicwrbit_1_si()
     {
        //uchar i2cWrbyt1I;
        pSCL_si=0;
			  for(xdelay_si=0;xdelay_si<60;xdelay_si++){_nop_();}
        pSDA_si=1;
			  for(xdelay_si=0;xdelay_si<60;xdelay_si++){_nop_();}
        pSCL_si=1;
        for(xdelay_si=0;xdelay_si<60;xdelay_si++){_nop_();}
        pSCL_si=0;
				for(xdelay_si=0;xdelay_si<60;xdelay_si++){_nop_();}
                
     }
		
		
 void iic_getAck_si() //no crash
     {
       //uchar i2cCackI;
			 pSCL_si=0;
			 for(xdelay_si=0;xdelay_si<60;xdelay_si++){_nop_();} 
			 pSDA_si=1;
       for(xdelay_si=0;xdelay_si<60;xdelay_si++){_nop_();} 
			 pSCL_si=1;
       for(xdelay_si=0;xdelay_si<60;xdelay_si++){_nop_();} 
			 if(pSDA_si==0)
         {
           bACK_si=0; 
         }
       else
         {
           bACK_si=1;
         }
			pSCL_si=0;
			for(xdelay_si=0;xdelay_si<60;xdelay_si++){_nop_();} 
			 
     }

 void iicStop_si() //if scl==0 it crashed;
    {
     uchar i2cStopI;
     
		 pSCL_si=0;
		 for(xdelay_si=0;xdelay_si<60;xdelay_si++){_nop_();} 
		 pSDA_si=0;	 
		 for(xdelay_si=0;xdelay_si<60;xdelay_si++){_nop_();} 
		 pSCL_si=1;
		 //0913 while(pSCL_si==0){;}
     for(xdelay_si=0;xdelay_si<60;xdelay_si++){_nop_();} 
		 pSDA_si=1;
     for(xdelay_si=0;xdelay_si<60;xdelay_si++){_nop_();} 
		 }

 void iic_send_MACK_si() //no crash
    {
      //uchar i2cMnackI;
      
			pSCL_si=0;
			for(xdelay_si=0;xdelay_si<50;xdelay_si++){_nop_();}
      pSDA_si=0;
      for(xdelay_si=0;xdelay_si<50;xdelay_si++){_nop_();}
      pSCL_si=1;
      for(xdelay_si=0;xdelay_si<50;xdelay_si++){_nop_();}  
      pSCL_si=0;
      //pSDA_si=1;   
      for(xdelay_si=0;xdelay_si<50;xdelay_si++){_nop_();}  
      }

 //----------------------------------------------------------------
 void iicwrByte_si(uchar i2cWrbytWrData)
      {
        uchar i2cWrbytJ;
        for(i2cWrbytJ=0;i2cWrbytJ<8;i2cWrbytJ++)
         {
           if((i2cWrbytWrData&0x80)>0)
              {iicwrbit_1_si();}
           else
              {iicwrbit_0_si();}
           i2cWrbytWrData=_crol_(i2cWrbytWrData,1);
           }  
      }

 uchar iicrdByte_si()
     {
       uchar i2cRdbytRdData=0xff,i2cRdbytJ;
			 pSCL_si=0;
			 for(xdelay_si=0;xdelay_si<50;xdelay_si++){_nop_();}
			 pSDA_si=1;
			 for(xdelay_si=0;xdelay_si<50;xdelay_si++){_nop_();}
       for(i2cRdbytJ=0;i2cRdbytJ<8;i2cRdbytJ++)
         {
          pSCL_si=1;
					for(xdelay_si=0;xdelay_si<50;xdelay_si++){_nop_();}   
          if(pSDA_si==0)
            {
             i2cRdbytRdData=i2cRdbytRdData&0x7f;
             i2cRdbytRdData=_crol_(i2cRdbytRdData,1);
              } 
          else
            {
             i2cRdbytRdData=i2cRdbytRdData|0x80;
             i2cRdbytRdData=_crol_(i2cRdbytRdData,1);
             }
					for(xdelay_si=0;xdelay_si<50;xdelay_si++){_nop_();} 
					pSCL_si=0; 
          for(xdelay_si=0;xdelay_si<50;xdelay_si++){_nop_();} 
					}
       return(i2cRdbytRdData);
       }

//----------------------------------------------------------------
	

void set_i2c_slave_si(uchar xdevaddr,uchar xbyte_addr,uchar xbyte_data)
  {
		do{
				do{
					do{
							iicStart();	
							iicwrByte_si(xdevaddr);	//0xc0
							iic_getAck_si();
					}while(bACK_si==1);
					iicwrByte_si(xbyte_addr);
					iic_getAck_si();
				}while(bACK_si==1);
		    iicwrByte_si(xbyte_data);
		    iic_getAck_si();
	    }while(bACK_si==1);
	 iicStop_si();
  }

uchar read_i2c_slave_si(uchar xdevaddr,uchar RdAddr)
     {
	  uchar temp;
		uchar x_wr_devaddr;
		x_wr_devaddr = xdevaddr + 1;	 
	  do{
	     do{
		      do{
			       iicStart();
		         iicwrByte_si(xdevaddr);//0xc0  这里0xa0 要改成 24C04 的addr + 1(for read)
		         iic_getAck_si();
						 //PTSTA = tst;//tst GPIO
		         //tst = ~tst;	 
			       }while(bACK_si==1);
					iicwrByte_si(RdAddr);
			    iic_getAck_si();
					//PTSTA = tst;//tst GPIO
		      //tst = ~tst;	 
		      }while(bACK_si==1);
				iicStop_si(); 	
		    iicStart();
		    iicwrByte_si(x_wr_devaddr);//0xc1
		    iic_getAck_si();
			  //PTSTA = tst;//tst GPIO
		    //tst = ~tst;	 
	      }while(bACK_si==1);
	   temp=iicrdByte_si();
     iic_send_MACK_si();
	   iicStop_si();
		 //PTSTA = tst;//tst GPIO
		 //tst = ~tst;	 
	   return(temp);
	  }


