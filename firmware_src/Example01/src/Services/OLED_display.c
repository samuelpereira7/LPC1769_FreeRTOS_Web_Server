/*
 * OLED_display.c
 *
 *  Created on: 15 de abr de 2018
 *      Author: samuelpereira
 */


#include "OLED_display.h"
#include "oled.h"

#include "LPC17xx.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_ssp.h"

#include <stdbool.h>

/* FreeRTOS.org includes. */
#include "task.h"
#include "semphr.h"

/* Demo includes. */
#include "basic_io.h"

#include "tcpip.h"

#define INVALID -126

typedef struct oled_data
{
	int32_t x;
	int32_t y;
	int32_t z;
	int32_t temp;
	bool rgb_on;
	bool ready;
} oled_data_t;

static oled_data_t data;
xSemaphoreHandle data_semaphr;

static void OLED_display_init_ssp(void);

void OLED_display_mainTask( void *pvParameters );
void OLED_display_updaterTask( void *pvParameters );

void OLED_display_init_ssp(void)
{
	SSP_CFG_Type SSP_ConfigStruct;
	PINSEL_CFG_Type PinCfg;

	/*
	 * Initialize SPI pin connect
	 * P0.7 - SCK;
	 * P0.8 - MISO
	 * P0.9 - MOSI
	 * P2.2 - SSEL - used as GPIO
	 */
	PinCfg.Funcnum = 2;
	PinCfg.OpenDrain = 0;
	PinCfg.Pinmode = 0;
	PinCfg.Portnum = 0;
	PinCfg.Pinnum = 7;
	PINSEL_ConfigPin(&PinCfg);
	PinCfg.Pinnum = 8;
	PINSEL_ConfigPin(&PinCfg);
	PinCfg.Pinnum = 9;
	PINSEL_ConfigPin(&PinCfg);
	PinCfg.Funcnum = 0;
	PinCfg.Portnum = 2;
	PinCfg.Pinnum = 2;
	PINSEL_ConfigPin(&PinCfg);

	SSP_ConfigStructInit(&SSP_ConfigStruct);

	// Initialize SSP peripheral with parameter given in structure above
	SSP_Init(LPC_SSP1, &SSP_ConfigStruct);

	// Enable SSP peripheral
	SSP_Cmd(LPC_SSP1, ENABLE);
}

void OLED_display_init (void)
{
	OLED_display_init_ssp();
	oled_init();

	OLED_display_clearScreen();

	data.rgb_on = false;
	data.x = INVALID;
	data.y = INVALID;
	data.z = INVALID;
	data.temp = INVALID;
	data.ready = false;

	OLED_display_queue = xQueueCreate( 8, sizeof(message_t) );
	data_semaphr = xSemaphoreCreateMutex();

	xTaskCreate( OLED_display_mainTask, "OLED Main", 240, NULL, 1, NULL );
	xTaskCreate( OLED_display_updaterTask, "OLED Updater", 100, NULL, 1, NULL );
}

void OLED_display_fillRect(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1)
{
	oled_fillRect(x0, y0, x1, y1, OLED_COLOR_WHITE);
}

void OLED_display_clearScreen(void)
{
	oled_clearScreen(OLED_COLOR_WHITE);
}

void OLED_display_putString(uint8_t x, uint8_t y, uint8_t *pStr)
{
	oled_putString(x, y, pStr, OLED_COLOR_BLACK, OLED_COLOR_WHITE);
}

void OLED_display_mainTask( void *pvParameters )
{
	uint8_t buf[30];

	vPortEnterCritical();

	OLED_display_clearScreen();
	OLED_display_putString( 1, 1, (uint8_t*) "+Aviao Cajada+" );
	OLED_display_putString( 1, 9, (uint8_t*) "IP Address:" );
	sprintf( (char*) buf, " %d.%d.%d.%d", MYIP_1, MYIP_2, MYIP_3, MYIP_4 );
	OLED_display_putString( 1, 9, (uint8_t*) buf );
	OLED_display_putString( 1, 25, (uint8_t*) "Acc x  : " );
	OLED_display_putString( 1, 33, (uint8_t*) "Acc y  : " );
	OLED_display_putString( 1, 41, (uint8_t*) "Acc z  : " );
	OLED_display_putString( 1, 49, (uint8_t*) "Temp   : " );

	vPortExitCritical();

	while(1)
	{
		if( data.ready == false )
		{
			if( data.x != INVALID && data.y != INVALID && data.z != INVALID && data.temp != INVALID )
			{
				data.ready = true;
			}
		}
		else
		{
			vPortEnterCritical();

			/* displaying info in the oled display */
			OLED_display_fillRect( (1 + 9 * 6), 17, 80, 24 );
			if (data.rgb_on == true)
			{
				OLED_display_putString( 1, 17, (uint8_t*) "RGB ON " );
			}
			else
			{
				OLED_display_putString( 1, 17, (uint8_t*) "RGB OFF" );
			}

			vPortExitCritical();

			vTaskDelay(10);

			vPortEnterCritical();

			intToString( data.x, buf, 10, 10 );
			OLED_display_fillRect( (1 + 9 * 6), 25, 80, 32 );
			OLED_display_putString( (1 + 9 * 6), 25, buf );

			intToString( data.y, buf, 10, 10 );
			OLED_display_fillRect( (1 + 9 * 6), 33, 80, 40 );
			OLED_display_putString( (1 + 9 * 6), 33, buf );

			intToString( data.z, buf, 10, 10 );
			OLED_display_fillRect( (1 + 9 * 6), 41, 80, 48 );
			OLED_display_putString( (1 + 9 * 6), 41, buf );

			sprintf( (char*) buf, "%d.%dC", data.temp / 10, data.temp % 10 );
			OLED_display_fillRect( (1 + 9 * 6), 49, 90, 56 );
			OLED_display_putString( (1 + 9 * 6), 49, buf );

			vPortExitCritical();

			vTaskDelay( 1000 / portTICK_RATE_MS);
		}

	}
}

void OLED_display_updaterTask( void *pvParameters )
{
	message_t msg;
	portBASE_TYPE xStatus = pdFALSE;
	portTickType blockTime = 20 / portTICK_RATE_MS;

	while(1)
	{
		xStatus = xQueueReceive( OLED_display_queue , &msg, blockTime );

		if( xStatus == pdTRUE )
		{
			switch( msg.source )
			{
				case ACC:
					xSemaphoreTake(data_semaphr, blockTime);
					data.x = msg.payload[0];
					data.y = msg.payload[1];
					data.z = msg.payload[2];
					xSemaphoreGive(data_semaphr);
					vPrintString("Acc updated\n");
					break;
				case TEMP:
					xSemaphoreTake(data_semaphr, blockTime);
					data.temp = msg.payload[0];
					xSemaphoreGive(data_semaphr);
					vPrintString("Temp updated\n");
					break;
				case RGB:
					xSemaphoreTake(data_semaphr, blockTime);
					data.rgb_on = msg.payload[0];
					xSemaphoreGive(data_semaphr);
					vPrintString("RGB updated\n");
					break;
				default:
					break;
			}
		}
	}
}
