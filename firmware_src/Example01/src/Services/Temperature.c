/*
 * Temperature.c
 *
 *  Created on: 10 de abr de 2018
 *      Author: samuelpereira
 */

#include "Temperature.h"
#include <temp.h>

/* FreeRTOS.org includes. */
#include "FreeRTOS.h"
#include "task.h"

/* Demo includes. */
#include "basic_io.h"

static callback_t tx_callback;

void Temperature_task( void *pvParameters );

typedef struct tagTemperature
{
	int32_t temperature;
}ttagTemperature;

static ttagTemperature Temp_Instance;

void Temperature_init (uint32_t (*getMsTick)(void))
{
	temp_init(getMsTick);
	xTaskCreate( Temperature_task, "Temp", 192, NULL, 1, NULL );
}

void Temperature_setCallback(callback_t c)
{
	if (c != NULL)
	{
		tx_callback = c;
	}
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

void Temperature_task( void *pvParameters )
{
	message_t msg;

	while(1)
	{
		memset(&msg, 0x00, sizeof(msg));
		msg.source = TEMP;
		msg.payload[0] = Temperature_read();

		if( msg.payload[0] > 0 && msg.payload[0] < 700 )
		{
			if (tx_callback != NULL)
			{
				tx_callback(msg);
			}
		}

		vTaskDelay( 500 / portTICK_RATE_MS );
	}
}



