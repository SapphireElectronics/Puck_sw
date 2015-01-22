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
	i2c_start();					// send START

	if( i2c_put_byte( addr ) )		// a slave did not acknowledge
	{
		i2c_stop();
		return( I2C_NO_ACK_ADDR );
	}	
	
	if( i2c_put_byte( data ) )		// a slave did not acknowledge
	{
		i2c_stop();
		return( I2C_NO_ACK_DATA );
	}		
	
	i2c_stop();						// send STOP
	return( I2C_NORMAL );
}	

uns8 i2c_tx_reg( uns8 addr, uns8 reg, uns8 data )
{
	i2c_start();					// send START

	if( i2c_put_byte( addr ) )		// a slave did not acknowledge
	{
		i2c_stop();
		return( I2C_NO_ACK_ADDR );
	}	
	
	if( i2c_put_byte( reg ) )		// a slave did not acknowledge
	{
		i2c_stop();
		return( I2C_NO_ACK_ADDR );
	}	

	if( i2c_put_byte( data ) )		// a slave did not acknowledge
	{
		i2c_stop();
		return( I2C_NO_ACK_DATA );
	}		
	
	i2c_stop();						// send STOP
	return( I2C_NORMAL );
}	


// not debugged
uns8 i2c_tx_multi( uns8 addr, uns8 *data_ptr, uns8 length )
{
	i2c_start();			// send START

	if( i2c_put_byte( addr ) )		// a slave did not acknowledge
	{
		i2c_stop();
		return( I2C_NO_ACK_ADDR );
	}	
	
	while( length )
	{
		length--;

		if( i2c_put_byte( *data_ptr++ ) )		// a slave did not acknowledge
		{
			i2c_stop();
			return( I2C_NO_ACK_DATA );
		}		
	}

	i2c_stop();			// send STOP
	return( I2C_NORMAL );
}	

uns8 i2c_rx( uns8 addr, uns8 *data )
{
	uns8 dt;
	i2c_start();					// send START

	if( i2c_put_byte( addr ) )		// slave did not acknowledge
	{
		i2c_stop();
		return( I2C_NO_ACK_ADDR );
	}	
	
	dt = i2c_get_byte();	// get a data byte
	*data = dt;
	
	i2c_send_noack();		// this is the last byte
	
	i2c_stop();				// send STOP
	return( I2C_NORMAL );
}	

// not debugged
uns8 i2c_rx_multi( uns8 addr, uns8 *data_ptr, uns8 length )
{
	uns8 dt;
	i2c_start();					// send START

	if( i2c_put_byte( addr ) )		// slave did not acknowledge
	{
		i2c_stop();
		return( I2C_NO_ACK_ADDR );
	}	
	
	while( length )
	{
		length--;

		dt = i2c_get_byte();	// get a data byte
		*data_ptr++ = dt;
	
		if( length )
			i2c_send_ack();		// this is not the last byte
	}	
	
	i2c_send_noack();		// this was the last byte
	
	i2c_stop();				// send STOP
	return( I2C_NORMAL );
}


// set I2C Start Condition
void i2c_start( void )
{
	SEN = 1;			// set START condition
	while( !SSP1IF );	// wait until SSP1IF is set
//	SSP1IF = 0;
}

// set I2C Stop Condition
void i2c_stop( void )
{
	PEN = 1;			// set STOP condition
	while( !SSP1IF );	// wait until SSP1IF is set
	SSP1IF = 0;
}		

void i2c_send_ack( void )
{
	ACKDT = 0;			// set ACK
	ACKEN = 1;			// initiate ACK sequence;
	while( !SSP1IF );	// wait until SSP1IF is set
	SSP1IF = 0;
}

void i2c_send_noack( void )
{
	ACKDT = 1;			// set NO_ACK
	ACKEN = 1;			// initiate ACK sequence;
	while( !SSP1IF );	// wait until SSP1IF is set
	SSP1IF = 0;
}		

bit i2c_get_ack( void )
{
	while( !SSP1IF );	// wait until SSP1IF is set
	SSP1IF = 0;
	return( ACKSTAT );	// return ACK value
}

bit i2c_put_byte( uns8 data )
{
	SSP1BUF = data;			// send data byte
	SSP1IF = 0;
	return i2c_get_ack();	// return ACK value
}	

uns8 i2c_get_byte( void )	
{
	RCEN = 1;			// set as receiver
	
	while( !SSP1IF );	// wait until SSP1IF is set
	SSP1IF = 0;

	return( SSP1BUF );	// return received data byte
}	
		
#endif //_IC2_C