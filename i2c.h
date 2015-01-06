#ifndef _I2C_H
#define _I2C_H

enum { I2C_NORMAL, I2C_NO_ACK_ADDR, I2C_NO_ACK_DATA };

void i2c_init( void );

uns8 i2c_tx( uns8 addr, uns8 data );
uns8 i2c_tx_multi( uns8 addr, uns8 *data_ptr, uns8 length );

uns8 i2c_rx( uns8 addr, uns8 *data );
uns8 i2c_rx_multi( uns8 addr, uns8 *data_ptr, uns8 *length );

void i2c_start( void );
void i2c_stop( void );

#endif //_IC2_H