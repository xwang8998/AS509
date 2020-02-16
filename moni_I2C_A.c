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

//sbit	pSDA	=	P1^2;//P3^7;
//sbit	pSCL	=	P1^1;//P3^6;
sbit	pSDA	=	P2^4;//P3^2;  //7 
sbit	pSCL	=	P2^1;//P3^3;  //8


bit   bACK;

unsigned char xdelay;


extern uchar	keyedA, keyedB;	

extern bit tst ;
extern bit tstb;

void iicStart()  //if scl==0 it crashed;
   {
    uchar i2cStartI;
    pSDA=1;
    pSCL=1;
		//0913 while(pSCL==0){;}
    for(i2cStartI=0;i2cStartI<60;i2cStartI++){_nop_();}
    pSDA=0;
    for(i2cStartI=0;i2cStartI<60;i2cStartI++){_nop_();}
    pSCL=0;
		for(i2cStartI=0;i2cStartI<60;i2cStartI++){_nop_();}
    }

void iicwrbit_0()
     {
        //uchar i2cWrbyt0I;
				pSCL=0;
			  for(xdelay=0;xdelay<60;xdelay++){_nop_();}
        pSDA=0;
			  for(xdelay=0;xdelay<60;xdelay++){_nop_();}
        pSCL=1;
        for(xdelay=0;xdelay<60;xdelay++){_nop_();}
        pSCL=0;       
				for(xdelay=0;xdelay<60;xdelay++){_nop_();}
        
     }

 void iicwrbit_1()
     {
        //uchar i2cWrbyt1I;
        pSCL=0;
			  for(xdelay=0;xdelay<60;xdelay++){_nop_();}
        pSDA=1;
			  for(xdelay=0;xdelay<60;xdelay++){_nop_();}
        pSCL=1;
        for(xdelay=0;xdelay<60;xdelay++){_nop_();}
        pSCL=0;
				for(xdelay=0;xdelay<60;xdelay++){_nop_();}
                
     }
		
		
 void iic_getAck() //no crash
     {
       //uchar i2cCackI;
			 pSCL=0;
			 for(xdelay=0;xdelay<60;xdelay++){_nop_();} 
			 pSDA=1;
       for(xdelay=0;xdelay<60;xdelay++){_nop_();} 
			 pSCL=1;
       for(xdelay=0;xdelay<60;xdelay++){_nop_();} 
			 if(pSDA==0)
         {
           bACK=0; 
         }
       else
         {
           bACK=1;
         }
			pSCL=0;
			for(xdelay=0;xdelay<60;xdelay++){_nop_();} 
			 
     }

 void iicStop() //if scl==0 it crashed;
    {
     uchar i2cStopI;
     
		 pSCL=0;
		 for(xdelay=0;xdelay<60;xdelay++){_nop_();} 
		 pSDA=0;	 
		 for(xdelay=0;xdelay<60;xdelay++){_nop_();} 
		 pSCL=1;
		 //0913 while(pSCL==0){;}
     for(xdelay=0;xdelay<60;xdelay++){_nop_();} 
		 pSDA=1;
     for(xdelay=0;xdelay<60;xdelay++){_nop_();} 
		 }

 void iic_send_MACK() //no crash
    {
      //uchar i2cMnackI;
      
			pSCL=0;
			for(xdelay=0;xdelay<50;xdelay++){_nop_();}
      pSDA=0;
      for(xdelay=0;xdelay<50;xdelay++){_nop_();}
      pSCL=1;
      for(xdelay=0;xdelay<50;xdelay++){_nop_();}  
      pSCL=0;
      //pSDA=1;   
      for(xdelay=0;xdelay<50;xdelay++){_nop_();}  
      }

 //----------------------------------------------------------------
 void iicwrByte(uchar i2cWrbytWrData)
      {
        uchar i2cWrbytJ;
        for(i2cWrbytJ=0;i2cWrbytJ<8;i2cWrbytJ++)
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
			 pSCL=0;
			 for(xdelay=0;xdelay<50;xdelay++){_nop_();}
			 pSDA=1;
			 for(xdelay=0;xdelay<50;xdelay++){_nop_();}
       for(i2cRdbytJ=0;i2cRdbytJ<8;i2cRdbytJ++)
         {
          pSCL=1;
					for(xdelay=0;xdelay<50;xdelay++){_nop_();}   
          if(pSDA==0)
            {
             i2cRdbytRdData=i2cRdbytRdData&0x7f;
             i2cRdbytRdData=_crol_(i2cRdbytRdData,1);
              } 
          else
            {
             i2cRdbytRdData=i2cRdbytRdData|0x80;
             i2cRdbytRdData=_crol_(i2cRdbytRdData,1);
             }
					for(xdelay=0;xdelay<50;xdelay++){_nop_();} 
					pSCL=0; 
          for(xdelay=0;xdelay<50;xdelay++){_nop_();} 
					}
       return(i2cRdbytRdData);
       }

//----------------------------------------------------------------
//for test 
			 /*
void set_si5351c(uchar xbyte_addr,uchar xbyte_data)
  {
		
							iicStart();	
							iicwrByte(0xa0);	
							iic_getAck();//P2=0x07;
							if(bACK==1){while(1){;}}
							iicwrByte(xbyte_addr);
							iic_getAck();
							if(bACK==1){P2=0x30;while(1){;}}
							iicwrByte(xbyte_data);
		          iic_getAck();
							if(bACK==1){P2=0x70;while(1){;}}
							iicStop();	
							P2=0xf0;	
		
  }
	*/

	

void set_i2c_slave(uchar xdevaddr,uchar xbyte_addr,uchar xbyte_data)
  {
		do{
				do{
					do{
							iicStart();	
							iicwrByte(xdevaddr);	//0xc0
							iic_getAck();
					}while(bACK==1);
					iicwrByte(xbyte_addr);
					iic_getAck();
				}while(bACK==1);
		    iicwrByte(xbyte_data);
		    iic_getAck();
	    }while(bACK==1);
	 iicStop();
  }

uchar read_i2c_slave(uchar xdevaddr,uchar RdAddr)
     {
	  uchar temp;
		uchar x_wr_devaddr;
		x_wr_devaddr = xdevaddr + 1;	 
	  do{
	     do{
		      do{
			       iicStart();
		         iicwrByte(xdevaddr);//0xc0  这里0xa0 要改成 24C04 的addr + 1(for read)
		         iic_getAck();
						 //PTSTA = tst;//tst GPIO
		         //tst = ~tst;	 
			       }while(bACK==1);
					iicwrByte(RdAddr);
			    iic_getAck();
					//PTSTA = tst;//tst GPIO
		      //tst = ~tst;	 
		      }while(bACK==1);
				iicStop(); 	
		    iicStart();
		    iicwrByte(x_wr_devaddr);//0xc1
		    iic_getAck();
			  //PTSTA = tst;//tst GPIO
		    //tst = ~tst;	 
	      }while(bACK==1);
	   temp=iicrdByte();
     iic_send_MACK();
	   iicStop();
		 //PTSTA = tst;//tst GPIO
		 //tst = ~tst;	 
	   return(temp);
	  }



/*

void set_si5351c(uchar xbyte_addr,uchar xbyte_data)
  {
		do{
				do{
					do{
							iicStart();	
							iicwrByte(0xc0);	//0xc0
							iic_getAck();
					}while(bACK==1);
					iicwrByte(xbyte_addr);
					iic_getAck();
				}while(bACK==1);
		    iicwrByte(xbyte_data);
		    iic_getAck();
	    }while(bACK==1);
	 iicStop();
  }

uchar read_si5351c(uchar RdAddr)
     {
	  uchar temp;
	  do{
	     do{
		      do{
			       iicStart();
		         iicwrByte(0xc0);//这里0xa0 要改成 24C04 的addr + 1(for read)
		         iic_getAck();
						 //PTSTA = tst;//tst GPIO
		         //tst = ~tst;	 
			       }while(bACK==1);
					iicwrByte(RdAddr);
			    iic_getAck();
					//PTSTA = tst;//tst GPIO
		      //tst = ~tst;	 
		      }while(bACK==1);
		    iicStart();
		    iicwrByte(0xc1);
		    iic_getAck();
			  //PTSTA = tst;//tst GPIO
		    //tst = ~tst;	 
	      }while(bACK==1);
	   temp=iicrdByte();
     iic_send_MACK();
	   iicStop();
		 //PTSTA = tst;//tst GPIO
		 //tst = ~tst;	 
	   return(temp);
	  }
*/		

/*
void iic24cxxwr(uchar WrAddr,uchar WrData)
     {
	   do{
	      do{ 
             do{
	            iicStart();
		        iicwrByte(0xa0);//这里0xa0 要改成 24C04 的addr
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
		         iicwrByte(0xa1);//这里0xa0 要改成 24C04 的addr + 1(for read)
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
     iic_send_MACK();
	   iicStop();
	   return(temp);
	  }


void iicwrByte(uchar i2cWrbytWrData)
      {
        uchar i2cWrbytI,i2cWrbytJ;
				pSCL=0;
        for(i2cWrbytI=0;i2cWrbytI<50;i2cWrbytI++){_nop_();}
				
				if((i2cWrbytWrData&0x80)>0)
           {pSDA=1;}
        else
           {pSDA=0;}
				for(i2cWrbytI=0;i2cWrbytI<50;i2cWrbytI++){_nop_();}
        
				pSCL=1;
        //0913 while(pSCL==0){;}
        for(i2cWrbytI=0;i2cWrbytI<50;i2cWrbytI++){_nop_();}
				
				//----------------------------------------------
        pSCL=0;// pSDA=0;
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




*/
