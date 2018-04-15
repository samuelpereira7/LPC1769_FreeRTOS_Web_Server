/*
 * RGB_Leds.h
 *
 *  Created on: 11 de abr de 2018
 *      Author: samuelpereira
 */

#ifndef SERVICES_RGB_LEDS_H_
#define SERVICES_RGB_LEDS_H_

#include "rgb.h"
#include <stdint.h>

#define RGB_LEDS_RED   RGB_RED
#define RGB_LEDS_BLUE  RGB_BLUE
#define RGB_LEDS_GREEN RGB_GREEN

void RGB_Leds_init (void);
void RGB_Leds_setLeds (uint8_t ledMask);

#endif /* SERVICES_RGB_LEDS_H_ */
