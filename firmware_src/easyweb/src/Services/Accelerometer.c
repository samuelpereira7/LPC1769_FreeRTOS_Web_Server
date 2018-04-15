/*
 * Accelerometer.c
 *
 *  Created on: 10 de abr de 2018
 *      Author: samuelpereira
 */

#include "Accelerometer.h"
#include "lpc17xx_i2c.h"
#include "lpc17xx_pinsel.h"

typedef struct tagAccelerometer
{
	int32_t xoff;
	int32_t yoff;
	int32_t zoff;
	int8_t cx;
	int8_t cy;
	int8_t cz;
}ttagAccelerometer;

static ttagAccelerometer Acc_Instance;

static void Accelerometer_init_i2c(void);

void Accelerometer_init_i2c(void)
{
	PINSEL_CFG_Type PinCfg;

	/* Initialize I2C2 pin connect */
	PinCfg.Funcnum = 2;
	PinCfg.Pinnum = 10;
	PinCfg.Portnum = 0;
	PINSEL_ConfigPin(&PinCfg);
	PinCfg.Pinnum = 11;
	PINSEL_ConfigPin(&PinCfg);

	// Initialize I2C peripheral
	I2C_Init(LPC_I2C2, 100000);

	/* Enable I2C1 operation */
	I2C_Cmd(LPC_I2C2, ENABLE);
}

void Accelerometer_init (void)
{
	int8_t x = 0;
	int8_t y = 0;
	int8_t z = 0;

	Accelerometer_init_i2c();
	acc_init();

	acc_read(&x, &y, &z);
	Acc_Instance.xoff = 0 - x;
	Acc_Instance.yoff = 0 - y;
	Acc_Instance.zoff = 64 - z;
}

void Accelerometer_read (int8_t* x, int8_t* y, int8_t* z)
{
	acc_read(x, y, z);
	*x += Acc_Instance.xoff;
	*y += Acc_Instance.yoff;
	*z += Acc_Instance.zoff;

	Acc_Instance.cx = *x;
	Acc_Instance.cy = *y;
	Acc_Instance.cz = *z;
}

void Accelerometer_setRange(acc_range_t range)
{
	acc_setRange(range);
}

void Accelerometer_setMode(acc_mode_t mode)
{
	acc_setMode(mode);
}

int8_t Accelerometer_getX()
{
	return Acc_Instance.cx;
}

int8_t Accelerometer_getY()
{
	return Acc_Instance.cy;
}

int8_t Accelerometer_getZ()
{
	return Acc_Instance.cz;
}
