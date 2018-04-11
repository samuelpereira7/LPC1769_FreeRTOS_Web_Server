/*
 * Accelerometer.c
 *
 *  Created on: 10 de abr de 2018
 *      Author: samuelpereira
 */

#include "Accelerometer.h"

void Accelerometer_init (void)
{
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

