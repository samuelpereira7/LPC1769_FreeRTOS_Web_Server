/*
 * MainApp.c
 *
 *  Created on: 15 de abr de 2018
 *      Author: samuelpereira
 */

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

#include "helper.h"

inline static uint8_t calc_threshold( uint16_t trimpot_value );

int main( void )
{
	/* buffer for string operations */
	uint8_t buf[30];

	int8_t x = 0;
	int8_t y = 0;
	int8_t z = 0;
	int16_t temp = 0;
	uint8_t button_status;
	uint16_t trimpot_value;

	uint8_t RGB_on = 1;
	uint64_t counter = 0;
	uint8_t threshold;

	/* initializing sensors and actuators */
	OLED_display_init();
	Temperature_init( &getTicks );
	Button_init();
	Accelerometer_init();
	Trimpot_init();
	RGB_Leds_init();

	OLED_display_clearScreen();
	OLED_display_putString( 1, 1, (uint8_t*) "+Aviao Cajada+" );
	OLED_display_putString( 1, 9, (uint8_t*) "IP Address:" );
	sprintf( (char*) buf, " %d.%d.%d.%d", MYIP_1, MYIP_2, MYIP_3, MYIP_4 );
	OLED_display_putString( 1, 9, (uint8_t*) buf );
	OLED_display_putString( 1, 25, (uint8_t*) "Acc x  : " );
	OLED_display_putString( 1, 33, (uint8_t*) "Acc y  : " );
	OLED_display_putString( 1, 41, (uint8_t*) "Acc z  : " );
	OLED_display_putString( 1, 49, (uint8_t*) "Temp   : " );

	while (1)
	{
		if ((counter % 50000) == 0)
		{
			HTTP_Server_reset();
		}

		if ((counter++ % 4000) == 0)
		{
			/* reading sensors */
			temp = Temperature_read();
			button_status = Button_read();
			Accelerometer_read( &x, &y, &z );
			trimpot_value = Trimpot_read();

			/* calculating the threshold value for y-axis of the accelerometer */
			threshold = calc_threshold( trimpot_value );

			/* RGB leds operations */
			if (button_status == 0)
			{
				RGB_on = !RGB_on;
			}

			if ((y > threshold) && RGB_on)
			{
				RGB_Leds_setLeds( RGB_LEDS_BLUE );
			}
			else if ((y < -threshold) && RGB_on)
			{
				RGB_Leds_setLeds( RGB_LEDS_RED );
			}
			else
			{
				RGB_Leds_setLeds( 0 );
			}

			/* displaying info in the oled display */
			OLED_display_fillRect( (1 + 9 * 6), 17, 80, 24 );
			if (RGB_on == 1)
			{
				OLED_display_putString( 1, 17, (uint8_t*) "RGB ON " );
			}
			else
			{
				OLED_display_putString( 1, 17, (uint8_t*) "RGB OFF" );
			}

			intToString( x, buf, 10, 10 );
			OLED_display_fillRect( (1 + 9 * 6), 25, 80, 32 );
			OLED_display_putString( (1 + 9 * 6), 25, buf );

			intToString( y, buf, 10, 10 );
			OLED_display_fillRect( (1 + 9 * 6), 33, 80, 40 );
			OLED_display_putString( (1 + 9 * 6), 33, buf );

			intToString( z, buf, 10, 10 );
			OLED_display_fillRect( (1 + 9 * 6), 41, 80, 48 );
			OLED_display_putString( (1 + 9 * 6), 41, buf );

			sprintf( (char*) buf, "%d.%dC", temp / 10, temp % 10 );
			OLED_display_fillRect( (1 + 9 * 6), 49, 90, 56 );
			OLED_display_putString( (1 + 9 * 6), 49, buf );
		}

		/* network operations */
		if (!(SocketStatus & SOCK_ACTIVE))
		{
			TCPPassiveOpen();
		}

		DoNetworkStuff();

		HTTP_Server_process();
	}

	return 0;
}

uint8_t calc_threshold( uint16_t trimpot_value )
{
	return (uint8_t) (10 + (trimpot_value / 1000) * 2);
}
