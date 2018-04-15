/*
 * Temperature.h
 *
 *  Created on: 10 de abr de 2018
 *      Author: samuelpereira
 */

#ifndef SERVICES_TEMPERATURE_H_
#define SERVICES_TEMPERATURE_H_

#include <stdint.h>

void Temperature_init (uint32_t (*getMsTick)(void));
int32_t Temperature_read(void);
int32_t Temperature_getTemp(void);

#endif /* SERVICES_TEMPERATURE_H_ */
