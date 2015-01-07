#ifndef _I2C_H
#define _I2C_H

enum { I2C_NORMAL, I2C_NO_ACK_ADDR, I2C_NO_ACK_DATA };


// External Functions
// - all external functions return an error code

void i2c_init( void );

uns8 i2c_tx( uns8 addr, uns8 data );
uns8 i2c_tx_multi( uns8 addr, uns8 *data_ptr, uns8 length );

uns8 i2c_rx( uns8 addr, uns8 *data );
uns8 i2c_rx_multi( uns8 addr, uns8 *data_ptr, uns8 length );


// Internal Functions

void i2c_start( void );
void i2c_stop( void );
void i2c_send_ack( void );
void i2c_send_noack( void );
bit  i2c_get_ack( void );
uns8 i2c_get_byte( void );
bit  i2c_put_byte( uns8 data );

#endif //_IC2_H