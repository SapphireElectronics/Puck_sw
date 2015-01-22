#ifndef _ADXL_C
#define _ADXL_C

#include "i2c.h"

void adxl_init( void )
{
	i2c_tx_reg( ADXL_WR_ADDR, ADXL_THRESH_ACT, ADXL_2G0 );		// activity if more than 2G
	i2c_tx_reg( ADXL_WR_ADDR, ADXL_THRESH_INACT, ADXL_0G5 );	// no activity if less than 0.5G
	i2c_tx_reg( ADXL_WR_ADDR, ADXL_INT_ENABLE, 0b00010000 );	// interrupt on activity.
}	


#endif // _ADXL_C