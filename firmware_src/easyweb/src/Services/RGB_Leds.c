/*
 * RGB_Leds.c
 *
 *  Created on: 11 de abr de 2018
 *      Author: samuelpereira
 */

#include "RGB_Leds.h"

void RGB_Leds_init (void)
{
	rgb_init();

	RGB_Leds_setLeds(0);
}

void RGB_Leds_setLeds (uint8_t ledMask)
{
	rgb_setLeds(ledMask);
}
