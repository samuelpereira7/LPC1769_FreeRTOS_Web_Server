/*
 * Button.c
 *
 *  Created on: 10 de abr de 2018
 *      Author: samuelpereira
 */

#include "Button.h"
#include "lpc17xx_gpio.h"

/* FreeRTOS.org includes. */
#include "FreeRTOS.h"
#include "task.h"

/* Demo includes. */
#include "basic_io.h"

#include <stdlib.h>

static callback_t tx_callback;

void Button_readerTask( void *pvParameters );

#define INPUT 	0
#define OUTPUT	1

#define DEFAULT_PORT	0
#define DEFAULT_PIN		4

void Button_init(void)
{
	GPIO_SetDir( DEFAULT_PORT, DEFAULT_PIN, INPUT);

	xTaskCreate( Button_readerTask, "Button", 192, NULL, 1, NULL );
}

void Button_setCallback(callback_t c)
{
	if (c != NULL)
	{
		tx_callback = c;
	}
}

uint8_t Button_read(void)
{
	return ((GPIO_ReadValue(DEFAULT_PORT) >> DEFAULT_PIN) & 0x01);
}

void Button_readerTask( void *pvParameters )
{
	message_t msg;

	while(1)
	{
		memset(&msg, 0x00, sizeof(msg));
		msg.source = BUT;
		msg.payload[0] = Button_read();

		if (tx_callback != NULL)
		{
			tx_callback(msg);
		}

		vTaskDelay( 400 / portTICK_RATE_MS );
	}
}
