
void xi2c_wait()
{
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
}

void xi2c_sbit (bit d)
{
	xSDA = d;
	xi2c_wait();
	xSCL = 1;
	xi2c_wait();
	xSCL = 0;
	xi2c_wait();
}

bit xi2c_rbit ()
{
	bit i;

	xSDA = 1;		// release SDA line to high impedance 
	xi2c_wait();
	xSCL = 1;
	xi2c_wait();
	xi2c_wait();
	i = xSDA;
	xSCL = 0;
	xi2c_wait();
	return i;
}

void xi2c_stop()
{
	xSDA = 0;
	xi2c_wait();
	xSCL = 1;
	xi2c_wait();
	xi2c_wait();
	xSDA = 1;
	xi2c_wait();
	xi2c_wait();
}

void xi2c_start()
{
		xSCL = 0;////////////////////Don't know why?
		xi2c_wait();////////////////////??????????
	xSDA = 1;
	xi2c_wait();
	xSCL = 1;

	xi2c_wait();
	xi2c_wait();
	xSDA = 0;
	xi2c_wait();
	xSCL = 0;
	xi2c_wait();
}

bit xi2c_wr8b (unsigned char j)
{
	unsigned char n;

	for (n=0; n<8; n++) {
		if ((j & 0x80) > 0)
			xi2c_sbit (1);
		else
			xi2c_sbit (0);
		j <<= 1;
	}

	return xi2c_rbit();
}

unsigned char xi2c_rd8b (bit lastdata)
{
	unsigned char n, j;

	j = 0x0;
	for (n=0; n<8; n++) {
		j <<= 1;
		if (xi2c_rbit() == 1)
			j |= 0x01;
		else
			j &= 0xFE;
	}
	
	xi2c_sbit (lastdata);
	return j;
}

unsigned char xi2c_read (unsigned char daddr, unsigned char raddr )
{
//	unsigned char j;	
 // unsigned char *d;
 unsigned char Rdata;
	xi2c_start();
	if (xi2c_wr8b(daddr & 0xFE) == 1) {
		xi2c_stop();
		return 0;
	}
	if (xi2c_wr8b(raddr) == 1) {
		xi2c_stop();
		return 0;
	}
	xi2c_start();
	if (xi2c_wr8b(daddr | 0x01) == 1) {
		xi2c_stop();
		return 0;
	}
Rdata=xi2c_rd8b(0);
//	j = 0;
//	while (j < (n-1)) 
//		*(d + j++) = xi2c_rd8b(0);
///	*(d + j) = xi2c_rd8b(1);			// last byte, no ack by master

//	xi2c_stop();
	return Rdata;
}

bit xi2c_write (unsigned char daddr, unsigned char raddr, unsigned char Sdata)
{

	xi2c_start();
	if (xi2c_wr8b(daddr & 0xFE) == 1) {
		xi2c_stop();
		return 0;
	}
	if (xi2c_wr8b(raddr) == 1) {
		xi2c_stop();
		return 0;
	}
 if( xi2c_wr8b(Sdata)==1);
        {xi2c_stop();
		return 0;}

	xi2c_stop();
	return 1;
}



  bit xi2c_write2 (unsigned char daddr, unsigned char raddr, unsigned char *d, unsigned char n)
{
	unsigned char j;

	xi2c_start();
	if (xi2c_wr8b(daddr & 0xFE) == 1) {
		xi2c_stop();
		return 0;
	}
	if (xi2c_wr8b(raddr) == 1) {
		xi2c_stop();
		return 0;
	}

	j = 0;
	while (j < n) {
		if (xi2c_wr8b(*(d + j++)) == 1) {
			xi2c_stop();
			return 0;
		}
	}

	xi2c_stop();
	return 1;
}
