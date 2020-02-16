
#ifndef uchar 
#define uchar unsigned char 
#endif 
#ifndef uint 
#define uint unsigned int 
#endif 


uchar read_i2c_slave(uchar xdevaddr,uchar RdAddr);
void  set_i2c_slave(uchar xdevaddr,uchar xbyte_addr,uchar xbyte_data);
//uchar read_i2c_slave_si(uchar xdevaddr,uchar RdAddr);
//void  set_i2c_slave_si(uchar xdevaddr,uchar xbyte_addr,uchar xbyte_data);