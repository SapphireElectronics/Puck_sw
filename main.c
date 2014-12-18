// PUCK
// Accelerometer based lighted puck

#pragma chip PIC12F1822

/* Pin mappings
	Pn	Port	Type	Name	Chan	Details
   	1	Vdd		Pwr		Vdd				Power
	2	RA5		Din		Int				Interrupt input
	3	RA4		Dout	LED				LED Output
	4	RA3		Pwr		Vpp				ICSP Power
	5	RA2		DIO		SDA				Serial Data to Accel
	6	RA1		Dout	SCL				Serial Clock / ICSP Clock
	7	RA0		Unused	DAT				ICSP Data
   	8	Vss		Pwr		GND				Ground
*/

enum { I2C_NORMAL, I2C_NO_ACK_ADDR, I2C_NO_ACK_DATA };

uns8 i2c_tx( uns8 addr, uns8 data )
{
	SEN = 1;			// set Start condition

	while( !SSP1IF );	// wait until SSP1IF is set
	SSP1IF = 0;

	SSP1BUF = addr;		// load address

	while( BF );		// wait while buffer is full
	if( ACKSTAT )		// a slave did not acknowledge
		return( I2C_NO_ACK_ADDR );
	
	SSP1BUF = data;
	while( BF );		// wait while buffer is full
	if( ACKSTAT )		// a slave did not acknowledge
		return( I2C_NO_ACK_DATA );
		
	return( I2C_NORMAL );
}	

uns8 i2c_tx_multi( uns8 addr, uns8 *data_ptr, uns8 length )
{
	SEN = 1;			// set Start condition

	while( !SSP1IF );	// wait until SSP1IF is set
	SSP1IF = 0;

	SSP1BUF = addr;		// load address

	while( BF );		// wait while buffer is full
	if( ACKSTAT )		// a slave did not acknowledge
		return( I2C_NO_ACK_ADDR );


	while( length )
	{
		SSP1BUF = *data_ptr++;
		length--;

		while( BF );		// wait while buffer is full
		if( ACKSTAT )		// a slave did not acknowledge
			return( I2C_NO_ACK_DATA );
	}

	return( I2C_NORMAL );
}	


void main( void )
{
}	