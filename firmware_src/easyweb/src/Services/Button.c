/*
 * Button.c
 *
 *  Created on: 10 de abr de 2018
 *      Author: samuelpereira
 */

#include "Button.h"
#include "lpc17xx_gpio.h"

#define INPUT 	0
#define OUTPUT	1

#define DEFAULT_PORT	0
#define DEFAULT_PIN		4

void Button_init(void)
{
	GPIO_SetDir( DEFAULT_PORT, DEFAULT_PIN, INPUT);
}

uint8_t Button_read(void)
{
	return ((GPIO_ReadValue(DEFAULT_PORT) >> DEFAULT_PIN) & 0x01);
}
