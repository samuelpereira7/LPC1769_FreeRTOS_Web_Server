/*
 * Accelerometer.c
 *
 *  Created on: 10 de abr de 2018
 *      Author: samuelpereira
 */

#include "Accelerometer.h"
#include "lpc17xx_i2c.h"
#include "lpc17xx_pinsel.h"

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
	Accelerometer_init_i2c();
	acc_init();
}

void Accelerometer_read (int8_t* x, int8_t* y, int8_t* z)
{
	acc_read(x, y, z);
}

void Accelerometer_setRange(acc_range_t range)
{
	acc_setRange(range);
}

void Accelerometer_setMode(acc_mode_t mode)
{
	acc_setMode(mode);
}

