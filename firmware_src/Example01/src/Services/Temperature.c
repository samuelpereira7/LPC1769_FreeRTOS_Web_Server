/*
 * Temperature.c
 *
 *  Created on: 10 de abr de 2018
 *      Author: samuelpereira
 */

#include "Temperature.h"
#include <temp.h>

typedef struct tagTemperature
{
	int32_t temperature;
}ttagTemperature;

static ttagTemperature Temp_Instance;

void Temperature_init (uint32_t (*getMsTick)(void))
{
	temp_init(getMsTick);
}

int32_t Temperature_read(void)
{
	Temp_Instance.temperature = temp_read();
	return Temp_Instance.temperature;
}

int32_t Temperature_getTemp(void)
{
	return Temp_Instance.temperature;
}

