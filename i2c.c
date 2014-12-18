#ifndef _I2C_C
#define _I2C_C

#include "i2c.h"

void i2c_init( void )
{
	SSP1STAT = 0b11000000;	// slew rate disabled, SMBus compliant levels
	SSP1CON1 = 0b00001000;	// I2C Master Mode
	SSP1CON2 = 0b00000000;
	SSP1CON3 = 0b00000000;	// no interrupts used
//	SSP1MSK = 				// not set in intiatialization
	SSP1ADD = 0x09;			// Baud rate: 100 khz Fclock with 4 MHz Fosc.
	SSP1CON1.5 = 1;				// Enable I2C
}	

uns8 i2c_tx( uns8 addr, uns8 data )
{
	i2c_start();

	SSP1BUF = addr;		// load address

	while( !SSP1IF );
	SSP1IF = 0;
	
	if( ACKSTAT )		// a slave did not acknowledge
	{
		i2c_stop();
		return( I2C_NO_ACK_ADDR );
	}	
	
	SSP1BUF = data;

	while( !SSP1IF );
	SSP1IF = 0;

	if( ACKSTAT )		// a slave did not acknowledge
	{
		i2c_stop();
		return( I2C_NO_ACK_DATA );
	}		
	
	i2c_stop();
	return( I2C_NORMAL );
}	

uns8 i2c_tx_multi( uns8 addr, uns8 *data_ptr, uns8 length )
{
	SEN = 1;			// set Start condition

	while( !SSP1IF );	// wait until SSP1IF is set
	SSP1IF = 0;

	SSP1BUF = addr;		// load address

	while( !SSP1IF );
	SSP1IF = 0;

	if( ACKSTAT )		// a slave did not acknowledge
	{
		i2c_stop();
		return( I2C_NO_ACK_ADDR );
	}

	while( length )
	{
		SSP1BUF = *data_ptr++;
		length--;

		while( !SSP1IF );
		SSP1IF = 0;

		if( ACKSTAT )		// a slave did not acknowledge
		{
			i2c_stop();
			return( I2C_NO_ACK_DATA );
		}	
	}

	i2c_stop();
	return( I2C_NORMAL );
}	

// set I2C Start Condition
void i2c_start( void )
{
	SEN = 1;			// set Start condition
	while( !SSP1IF );	// wait until SSP1IF is set
	SSP1IF = 0;
}

// set I2C Stop Condition
void i2c_stop( void )
{
	PEN = 1;	
	while( !SSP1IF );	// wait until SSP1IF is set
	SSP1IF = 0;
}		

#endif //_IC2_C