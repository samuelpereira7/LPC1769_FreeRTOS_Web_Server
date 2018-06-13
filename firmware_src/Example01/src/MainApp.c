/*
 * MainApp.c
 *
 *  Created on: 15 de abr de 2018
 *      Author: samuelpereira
 */

/* FreeRTOS.org includes. */
#include "FreeRTOS.h"
#include "task.h"

/* Demo includes. */
#include "basic_io.h"

#include "stdlib.h"
#include "stdio.h"
#include "string.h"

#include <Systick.h>

#include "Temperature.h"
#include "Button.h"
#include "Accelerometer.h"
#include "Trimpot.h"
#include "RGB_Leds.h"
#include "OLED_display.h"

#include "Services/HTTP/tcpip.h"
#include <HTTP_Server.h>

#include "common.h"

/* Used as a loop counter to create a very crude delay. */
#define mainDELAY_LOOP_COUNT		( 0xfffff )

/* The task functions. */
void vMainTask( void *pvParameters );
void vTask2( void *pvParameters );

void acc_callback(message_t msg);
void trim_callback(message_t msg);
void but_callback(message_t msg);
void temp_callback(message_t msg);

int8_t x = 0;
int8_t y = 0;
int8_t z = 0;
int16_t temp = 0;
uint8_t button_status;
uint16_t trimpot_value;

int main( void )
{
	/* Init the semi-hosting. */
	printf( "\n" );

	OLED_display_init();

	Temperature_init( &getTicks );
	Temperature_setCallback(temp_callback);

	Button_init();
	Button_setCallback(but_callback);

	Accelerometer_init();
	Accelerometer_setCallback(acc_callback);

	Trimpot_init();
	Trimpot_setCallback(trim_callback);

	RGB_Leds_init();

	/* Create one of the two tasks. */
//	xTaskCreate(	vMainTask,		/* Pointer to the function that implements the task. */
//					"Main Task",/* Text name for the task.  This is to facilitate debugging only. */
//					240 * 2,	/* Stack depth in words. */
//					NULL,		/* We are not using the task parameter. */
//					1,			/* This task will run at priority 1. */
//					NULL );		/* We are not using the task handle. */

	/* Create the other task in exactly the same way. */
	//xTaskCreate( vTask2, "Task 2", 240, NULL, 1, NULL );
	HTTP_Server_init();

	/* Start the scheduler so our tasks start executing. */
	vTaskStartScheduler();

	/* If all is well we will never reach here as the scheduler will now be
	running.  If we do reach here then it is likely that there was insufficient
	heap available for the idle task to be created. */
	for( ;; );
	return 0;
}

void vMainTask( void *pvParameters )
{
//	vPortEnterCritical();
	/* buffer for string operations */
//	uint8_t buf[30];
//
//	uint8_t RGB_on = 1;
//	uint64_t counter = 0;
//	uint8_t threshold;

	/* initializing sensors and actuators */
//	OLED_display_init();
//
//	Temperature_init( &getTicks );
//	Temperature_setCallback(temp_callback);
//
//	Button_init();
//	Button_setCallback(but_callback);
//
//	Accelerometer_init();
//	Accelerometer_setCallback(acc_callback);
//
//	Trimpot_init();
//	Trimpot_setCallback(trim_callback);
//
//	RGB_Leds_init();

//	OLED_display_clearScreen();
//	OLED_display_putString( 1, 1, (uint8_t*) "+Aviao Cajada+" );
//	OLED_display_putString( 1, 9, (uint8_t*) "IP Address:" );
//	sprintf( (char*) buf, " %d.%d.%d.%d", MYIP_1, MYIP_2, MYIP_3, MYIP_4 );
//	OLED_display_putString( 1, 9, (uint8_t*) buf );
//	OLED_display_putString( 1, 25, (uint8_t*) "Acc x  : " );
//	OLED_display_putString( 1, 33, (uint8_t*) "Acc y  : " );
//	OLED_display_putString( 1, 41, (uint8_t*) "Acc z  : " );
//	OLED_display_putString( 1, 49, (uint8_t*) "Temp   : " );

	//vPortExitCritical();

	while (1)
	{
		/* reading sensors */
		//temp = Temperature_read();
		//button_status = Button_read();
		//Accelerometer_read( &x, &y, &z );
		//trimpot_value = Trimpot_read();

		/* calculating the threshold value for y-axis of the accelerometer */
		//threshold = calc_threshold( trimpot_value );

		/* RGB leds operations */
//		if (button_status == 0)
//		{
//			RGB_on = !RGB_on;
//		}
//
//		if ((y > threshold) && RGB_on)
//		{
//			RGB_Leds_setLeds( RGB_LEDS_BLUE );
//		}
//		else if ((y < -threshold) && RGB_on)
//		{
//			RGB_Leds_setLeds( RGB_LEDS_RED );
//		}
//		else
//		{
//			RGB_Leds_setLeds( 0 );
//		}

//		vPortEnterCritical();
//
//		/* displaying info in the oled display */
//		OLED_display_fillRect( (1 + 9 * 6), 17, 80, 24 );
//		if (RGB_on == 1)
//		{
//			OLED_display_putString( 1, 17, (uint8_t*) "RGB ON " );
//		}
//		else
//		{
//			OLED_display_putString( 1, 17, (uint8_t*) "RGB OFF" );
//		}
//
//		vPortExitCritical();
//
//		vTaskDelay(10);
//
//		vPortEnterCritical();
//		intToString( x, buf, 10, 10 );
//		OLED_display_fillRect( (1 + 9 * 6), 25, 80, 32 );
//		OLED_display_putString( (1 + 9 * 6), 25, buf );
//
//		intToString( y, buf, 10, 10 );
//		OLED_display_fillRect( (1 + 9 * 6), 33, 80, 40 );
//		OLED_display_putString( (1 + 9 * 6), 33, buf );
//
//		intToString( z, buf, 10, 10 );
//		OLED_display_fillRect( (1 + 9 * 6), 41, 80, 48 );
//		OLED_display_putString( (1 + 9 * 6), 41, buf );
//
//		sprintf( (char*) buf, "%d.%dC", temp / 10, temp % 10 );
//		OLED_display_fillRect( (1 + 9 * 6), 49, 90, 56 );
//		OLED_display_putString( (1 + 9 * 6), 49, buf );
//		vPortExitCritical();
//
//		vTaskDelay( 1000 / portTICK_RATE_MS);
	}
}

void acc_callback(message_t msg)
{
	char buffer[20];

	if(msg.source == ACC)
	{
		x = msg.payload[0];
		y = msg.payload[1];
		z = msg.payload[2];

		memset(buffer, 0x00, 20);
		sprintf(buffer, "acc = %d,%d,%d\n", x, y, z);

		vPrintString(buffer);

		/* Send message to HTTP Server */
		if ( xQueueSendToBack( HTTP_Server_queue, &msg, 25) != pdTRUE )
		{
			vPrintString("fail acc");
		}

		/* Send message to RGB Leds */
		if ( xQueueSendToBack( RGB_Leds_queue, &msg, 15) != pdTRUE )
		{
			vPrintString("fail acc");
		}

		/* Send message to OLED display */
		if ( xQueueSendToBack( OLED_display_queue, &msg, 15) != pdTRUE )
		{
			vPrintString("fail acc");
		}
	}
}

void trim_callback(message_t msg)
{
	char buffer[10];

	if(msg.source == TRIM)
	{
		trimpot_value = (uint16_t)msg.payload[0];

		memset(buffer, 0x00, 10);
		sprintf(buffer, "tr = %d\n", trimpot_value);

		vPrintString(buffer);

		/* Send message to RGB Leds */
		if ( xQueueSendToBack( RGB_Leds_queue, &msg, 15) != pdTRUE )
		{
			vPrintString("fail trim");
		}
	}
}
void but_callback(message_t msg)
{
	char buffer[10];

	if(msg.source == BUT)
	{
		button_status = (uint8_t)msg.payload[0];

		memset(buffer, 0x00, 10);
		sprintf(buffer, "b = %d\n", button_status);

		vPrintString(buffer);

		/* Send message to RGB Leds */
		if ( xQueueSendToBack( RGB_Leds_queue, &msg, 15) != pdTRUE )
		{
			vPrintString("fail button");
		}
	}
}
void temp_callback(message_t msg)
{
	char buffer[10];

	if(msg.source == TEMP)
	{
		temp = (int32_t)msg.payload[0];

		memset(buffer, 0x00, 10);
		sprintf(buffer, "t = %d\n", temp);

		vPrintString(buffer);

		/* Send message to HTTP Server */
		if ( xQueueSendToBack( HTTP_Server_queue, &msg, 15) != pdTRUE )
		{
			vPrintString("fail temp");
		}

		/* Send message to OLED display */
		if ( xQueueSendToBack( OLED_display_queue, &msg, 15) != pdTRUE )
		{
			vPrintString("fail temp");
		}
	}
}

void vTask2( void *pvParameters )
{
	const char *pcTaskName = "Task 2 is running\n";
	volatile unsigned long ul;

	/* As per most tasks, this task is implemented in an infinite loop. */
	for( ;; )
	{
		/* Print out the name of this task. */
		vPrintString( pcTaskName );

		/* Delay for a period. */
		for( ul = 0; ul < mainDELAY_LOOP_COUNT; ul++ )
		{
			/* This loop is just a very crude delay implementation.  There is
			nothing to do in here.  Later exercises will replace this crude
			loop with a proper delay/sleep function. */
		}
	}
}
/*-----------------------------------------------------------*/

void vApplicationMallocFailedHook( void )
{
	/* This function will only be called if an API call to create a task, queue
	or semaphore fails because there is too little heap RAM remaining. */
	for( ;; );
}
/*-----------------------------------------------------------*/

void vApplicationStackOverflowHook( xTaskHandle *pxTask, signed char *pcTaskName )
{
	/* This function will only be called if a task overflows its stack.  Note
	that stack overflow checking does slow down the context switch
	implementation. */
	for( ;; );
}
/*-----------------------------------------------------------*/

void vApplicationIdleHook( void )
{
	/* This example does not use the idle hook to perform any processing. */
}
/*-----------------------------------------------------------*/

void vApplicationTickHook( void )
{
	/* This example does not use the tick hook to perform any processing. */
}

