/*
 * OLED_display.h
 *
 *  Created on: 15 de abr de 2018
 *      Author: samuelpereira
 */

#ifndef SERVICES_OLED_DISPLAY_H_
#define SERVICES_OLED_DISPLAY_H_

#include <stdint.h>

/* FreeRTOS.org includes. */
#include "FreeRTOS.h"
#include "queue.h"

#include "common.h"

xQueueHandle OLED_display_queue;

void OLED_display_init (void);
void OLED_display_fillRect(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1);
void OLED_display_clearScreen(void);
void OLED_display_putString(uint8_t x, uint8_t y, uint8_t *pStr);

#endif /* SERVICES_OLED_DISPLAY_H_ */
