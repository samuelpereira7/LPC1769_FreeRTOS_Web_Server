/*
 * RGB_Leds.c
 *
 *  Created on: 11 de abr de 2018
 *      Author: samuelpereira
 */

#include "RGB_Leds.h"

/* FreeRTOS.org includes. */
#include "task.h"

#include <stdbool.h>

#define INVALID 126

void RGB_Leds_task( void *pvParameters );
inline static uint8_t calc_threshold( uint16_t trimpot_value );

typedef struct tagRGB_Leds
{
	bool on;
	int8_t y;
	uint8_t threshold;
}ttagRGB_Leds;

static ttagRGB_Leds RGB_Leds_Instance;

void RGB_Leds_init (void)
{
	rgb_init();

	RGB_Leds_setLeds(0);

	RGB_Leds_Instance.on = true;
	RGB_Leds_Instance.y = INVALID;
	RGB_Leds_Instance.threshold = INVALID;

	RGB_Leds_queue = xQueueCreate( 15, sizeof(message_t) );

	xTaskCreate( RGB_Leds_task, "RGB Task", 256, NULL, 1, NULL );
}

void RGB_Leds_setLeds (uint8_t ledMask)
{
	rgb_setLeds(ledMask);
}

void RGB_Leds_task( void *pvParameters )
{
	message_t msg;
	portBASE_TYPE xStatus = pdFALSE;
	portTickType blockTime = 20 / portTICK_RATE_MS;
	bool valid_source = false;

	while(1)
	{
		xStatus = xQueueReceive(RGB_Leds_queue, &msg, blockTime);

		if( xStatus == pdTRUE )
		{
			switch( msg.source )
			{
				case ACC:
					vPrintString( "Acc message received\n" );

					if( msg.payload[1] > -80 && msg.payload[1] < 80 )
					{
						RGB_Leds_Instance.y = msg.payload[1];
					}

					valid_source = true;
					break;
				case BUT:
					vPrintString( "Button message received\n" );

					if( msg.payload[0] == 0)
					{
						RGB_Leds_Instance.on = !RGB_Leds_Instance.on;
					}

					valid_source = true;
					break;
				case TRIM:
					vPrintString( "Trimpot message received\n" );

					/* calculating the threshold value for y-axis of the accelerometer */
					RGB_Leds_Instance.threshold = calc_threshold( (uint16_t)msg.payload[0] );

					valid_source = true;
					break;
				default:
					break;
			}

			if( valid_source == true )
			{
				if( RGB_Leds_Instance.threshold != INVALID && RGB_Leds_Instance.y != INVALID )
				{
					if( (RGB_Leds_Instance.y > RGB_Leds_Instance.threshold) && RGB_Leds_Instance.on )
					{
						RGB_Leds_setLeds( RGB_LEDS_BLUE );
					}
					else if( (RGB_Leds_Instance.y < -RGB_Leds_Instance.threshold) && RGB_Leds_Instance.on )
					{
						RGB_Leds_setLeds( RGB_LEDS_RED );
					}
					else
					{
						RGB_Leds_setLeds( 0 );
					}
				}
			}
		}
	}
}

uint8_t calc_threshold( uint16_t trimpot_value )
{
	return (uint8_t) (10 + (trimpot_value / 1000) * 2);
}
