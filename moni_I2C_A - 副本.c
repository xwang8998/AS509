/*********************************************************************************************************************************/
#include	"STC15Fxxxx.H"

#ifndef uchar 
#define uchar unsigned char 
#endif 
#ifndef uint 
#define uint unsigned int 
#endif 

#define WD7188	0X40
#define RD7188	0X41 

sbit	pSDA	=	P3^7;
sbit	pSCL	=	P3^6;
bit   bACK;

 void iicStart()
   {
    uchar i2cStartI;
    pSDA=1;
    pSCL=1;
 while(pSCL==0){;}
    for(i2cStartI=0;i2cStartI<40;i2cStartI++){_nop_();}
    pSDA=0;
    for(i2cStartI=0;i2cStartI<40;i2cStartI++){_nop_();}
    pSCL=0;
    }

 void iicStop()
    {
     uchar i2cStopI;
     pSDA=0;
     pSCL=1;
     while(pSCL==0){;}
     pSDA=1;
     for(i2cStopI=0;i2cStopI<40;i2cStopI++){_nop_();}
     for(i2cStopI=0;i2cStopI<40;i2cStopI++){_nop_();}
     pSCL=0; 
     }

 void iic_send_Mnack()
    {
      uchar i2cMnackI;
      pSDA=1;
      pSCL=1;
      for(i2cMnackI=0;i2cMnackI<40;i2cMnackI++){_nop_();}  
      pSCL=0;
      pSDA=0;   
      }

 void iic_getAck()
     {
       uchar i2cCackI;
       pSDA=1;
       pSCL=1;
       bACK=0;
       if(pSDA==0)
         {
           pSCL=0;
           for(i2cCackI=0;i2cCackI<40;i2cCackI++){_nop_();}            
         }
       else
         {
           bACK=1;
           pSCL=0;       
           for(i2cCackI=0;i2cCackI<40;i2cCackI++){_nop_();}  
         }
     }

 void iicwrbit_0()
     {
        uchar i2cWrbyt0I;
        pSDA=0;
        pSCL=1;
        for(i2cWrbyt0I=0;i2cWrbyt0I<40;i2cWrbyt0I++){_nop_();}
        pSCL=0;       
     }

 void iicwrbit_1()
     {
        uchar i2cWrbyt1I;
        pSDA=1;
        pSCL=1;
        for(i2cWrbyt1I=0;i2cWrbyt1I<40;i2cWrbyt1I++){_nop_();} 
        pSCL=0;
        pSDA=0;     
     }
//----------------------------------------------------------------
 void iicwrByte(uchar i2cWrbytWrData)
      {
        uchar i2cWrbytI,i2cWrbytJ;
        if((i2cWrbytWrData&0x80)>0)
           {pSDA=1;}
        else
           {pSDA=0;}
        pSCL=1;
        while(pSCL==0){;}
        for(i2cWrbytI=0;i2cWrbytI<40;i2cWrbytI++){_nop_();}
        pSCL=0;
        pSDA=0;
        i2cWrbytWrData=_crol_(i2cWrbytWrData,1);
        for(i2cWrbytJ=1;i2cWrbytJ<8;i2cWrbytJ++)
         {
           if((i2cWrbytWrData&0x80)>0)
              {iicwrbit_1();}
           else
              {iicwrbit_0();}
           i2cWrbytWrData=_crol_(i2cWrbytWrData,1);
           }  
      }

 uchar iicrdByte()
     {
       uchar i2cRdbytRdData=0xff,i2cRdbytJ;
       for(i2cRdbytJ=0;i2cRdbytJ<8;i2cRdbytJ++)
         {
          pSDA=1;
          pSCL=1;
          if(pSDA==0)
            {
             i2cRdbytRdData=i2cRdbytRdData&0x7f;
             i2cRdbytRdData=_crol_(i2cRdbytRdData,1);
             pSCL=0;
              } 
          else
            {
             i2cRdbytRdData=i2cRdbytRdData|0x80;
             i2cRdbytRdData=_crol_(i2cRdbytRdData,1);
             pSCL=0; 
              }
          }
       return(i2cRdbytRdData);
       }

//----------------------------------------------------------------
void set_ATM_T1(uchar addr7188,uchar data7188)
  {
		do{
				do{
					do{
							iicStart();
							iicwrByte(WD7188);
							iic_getAck();
					}while(bACK==1);
					iicwrByte(addr7188);
					iic_getAck();
				}while(bACK==1);
		    iicwrByte(data7188);
		    iic_getAck();
	    }while(bACK==1);
	 iicStop();
  }

 void ADV7188w(uchar addr7188,uchar data7188)
  {
		do{
				do{
					do{
							iicStart();
							iicwrByte(WD7188);
							iic_getAck();
					}while(bACK==1);
					iicwrByte(addr7188);
					iic_getAck();
				}while(bACK==1);
		    iicwrByte(data7188);
		    iic_getAck();
	    }while(bACK==1);
	 iicStop();
  }

uchar ADV7188r(uchar addr7188)
   {
     uchar temp;
        do{
		  do{
			 do{
				iicStart();
				iicwrByte(WD7188);
				iic_getAck();
			   }while(bACK==1);
		      iicwrByte(addr7188);
			  iic_getAck();
		     }while(bACK==1);
		    iicStart();
		    iicwrByte(RD7188);
			iic_getAck();
	       }while(bACK==1);
	    temp=iicrdByte();
	    iicStop();
	    return(temp);
     }


 
void tdelay(uchar delay_num)  //22.1184 the loop time is 0.543us
   {
    uchar tdelayI,tdelayK;                //delay_num 0.1ms/num
    for(tdelayI=delay_num;tdelayI>0;tdelayI--)
     {
      for(tdelayK=100;tdelayK>0;tdelayK--)
       {;}
      }
    }


 void init7188Comp(void)
	{
	 uchar ADV7188temp;
	 for(ADV7188temp=0;ADV7188temp<25;ADV7188temp+=2)
	 //ADV7188w(ADV7188RegComp[ADV7188temp],ADV7188RegComp[ADV7188temp+1]);
	 //ADV7188w(ADV7188RegComp[ADV7188temp],ADV7188RegComp[ADV7188temp+1]);
	 tdelay(10);
	}
/* void init7188Rgb(void)
	{
	 uchar ADV7188temp;
	 for(ADV7188temp=0;ADV7188temp<22;ADV7188temp+=2)
	 //ADV7188w(ADV7188RegComp[ADV7188temp],ADV7188RegComp[ADV7188temp+1]);
	ADV7188w(ADV7188RegRgb[ADV7188temp],ADV7188RegRgb[ADV7188temp+1]);
	 tdelay(10);
	}
	*/
 void init7188Yuv(void)
	{
	 uchar ADV7188temp;
	 for(ADV7188temp=0;ADV7188temp<17;ADV7188temp+=2)
	 //ADV7188w(ADV7188RegYuv[ADV7188temp],ADV7188RegYuv[ADV7188temp+1]);
	 tdelay(10);
	}

/*
void iic24cxxwr(uchar WrAddr,uchar WrData)
     {
	   do{
	      do{ 
             do{
	            iicStart();
		        iicwrByte(0xa0);
		        iic_getAck();
	           }while(bACK==1);
		      iicwrByte(WrAddr);
			  iic_getAck();
             }while(bACK==1);
		  iicwrByte(WrData);
		  iic_getAck();
         }while(bACK==1);
		 iicStop();
		 
	  }

uchar iic24cxxrd(uchar RdAddr)
     {
	  uchar temp;
	  do{
	     do{
		    do{
			    iicStart();
		        iicwrByte(0xa0);
		        iic_getAck();
			  }while(bACK==1);
		       iicwrByte(RdAddr);
			   iic_getAck();
		    }while(bACK==1);
		    iicStart();
		    iicwrByte(0xa1);
		    iic_getAck();            
	      }while(bACK==1);
	   temp=iicrdByte();
       iic_send_Mnack();
	   iicStop();
	   return(temp);
	  }
*/
