/*
 * Temperature.c
 *
 *  Created on: 10 de abr de 2018
 *      Author: samuelpereira
 */

#include "Temperature.h"
#include <temp.h>

void Temperature_init (uint32_t (*getMsTick)(void))
{
	temp_init(getMsTick);
}

int32_t Temperature_read(void)
{
	return temp_read();
}

