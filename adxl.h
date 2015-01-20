#ifndef _ADXL_H
#define _ADXL_H

// ADXH343 Register Definitions
#define ADXL_DEVID			0x00	// R
#define	ADXL_THRESH_TAP		0x1d	// R/W
#define ADXL_OFSX			0x1e	// R/W
#define ADXL_OFSY			0x1f	// R/W
#define ADXL_OFSZ			0x20	// R/W
#define ADXL_DUR			0x21	// R/W
#define ADXL_Latent			0x22	// R/W
#define ADXL_Window			0x23	// R/W
#define ADXL_THRESH_ACT		0x24	// R/W
#define ADXL_THRESH_INACT	0x25	// R/W
#define ADXL_TIME_INACT		0x26	// R/W
#define ADXL_ACT_INACT_CTL	0x27	// R/W
#define ADXL_THRESH_FF		0x28	// R/W
#define ADXL_TIME_FF		0x29	// R/W
#define ADXL_TAP_AXES		0x2a	// R/W
#define ADXL_ACT_TAP_STATUS	0x2b	// R
#define ADXL_BW_RATE		0x2c	// R/W
#define ADXL_POWER_CTL		0x2d	// R/W
#define ADXL_INT_ENABLE		0x2e	// R/W
#define ADXL_INT_MAP		0x2f	// R/W
#define ADXL_INT_SOURCE		0x30	// R
#define ADXL_DATA_FORMAT	0x31	// R/W
#define ADXL_DATAX0			0x32	// R
#define ADXL_DATAX1			0x33	// R
#define ADXL_DATAY0			0x34	// R
#define ADXL_DATAY1			0x35	// R
#define ADXL_DATAZ0			0x36	// R
#define ADXL_DATAZ1			0x37	// R
#define ADXL_FIFO_CTL		0x38	// R/W
#define ADXL_FIFO_STATUS	0x39	// R

// External Functions
void adxl_init( void );

// Internal Functions


#endif // _ADXL_H