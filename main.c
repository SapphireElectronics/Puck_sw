// PUCK
// Accelerometer based lighted puck

#pragma chip PIC12F1822

#pragma config =      0x3fbc
#pragma config reg2 = 0x1eff

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

/* ADXL343 Data
	I2C Mode
	CS is High (modified PCB)
	Pullups are 10k (modified PCB)
	Alt Address is high:
		Write Addr = 0x3a 
		Read Addr = 0x3b
	Use 100 kHz clock
*/

#include "i2c.h"
#include "adxl.h"

#include "i2c.c"
#include "adxl.c"

void main( void )
{
	OSCCON = 0b01101000;		// 4 MHz Fosc
	
	i2c_init();
	
	while(1)
	{
		i2c_tx( 0x3a, 0x55 );

		char i, j;
		for(i=0; i<255; i++ )
			for( j=0; j<255; j++ )
				nop();
		
	}	
}	