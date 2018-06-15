/*
 * Accelerometer.h
 *
 *  Created on: 10 de abr de 2018
 *      Author: samuelpereira
 */

#ifndef SERVICES_ACCELEROMETER_H_
#define SERVICES_ACCELEROMETER_H_

#include "acc.h"
#include <stdint.h>
#include "common.h"

void Accelerometer_init (void);
void Accelerometer_read (int8_t* x, int8_t* y, int8_t* z);
void Accelerometer_setCallback(callback_t c);
void Accelerometer_setRange(acc_range_t range);
void Accelerometer_setMode(acc_mode_t mode);
int8_t Accelerometer_getX();
int8_t Accelerometer_getY();
int8_t Accelerometer_getZ();


#endif /* SERVICES_ACCELEROMETER_H_ */
