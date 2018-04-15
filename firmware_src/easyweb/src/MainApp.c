/*
 * MainApp.c
 *
 *  Created on: 15 de abr de 2018
 *      Author: samuelpereira
 */

#include "Services/Temperature.h"
#include "Services/Button.h"
#include "Services/Accelerometer.h"
#include "Services/Trimpot.h"
#include "Services/RGB_Leds.h"
#include "Services/OLED_display.h"

#include "stdlib.h"
#include "stdio.h"
#include "string.h"

#include "Services/HTTP/easyweb.h"
#include "Services/HTTP/tcpip.h"
#include "Services/ew_systick.h"

static void intToString(int value, uint8_t* pBuf, uint32_t len, uint32_t base)
{
    static const char* pAscii = "0123456789abcdefghijklmnopqrstuvwxyz";
    int pos = 0;
    int tmpValue = value;

    // the buffer must not be null and at least have a length of 2 to handle one
    // digit and null-terminator
    if (pBuf == NULL || len < 2)
    {
        return;
    }

    // a valid base cannot be less than 2 or larger than 36
    // a base value of 2 means binary representation. A value of 1 would mean only zeros
    // a base larger than 36 can only be used if a larger alphabet were used.
    if (base < 2 || base > 36)
    {
        return;
    }

    // negative value
    if (value < 0)
    {
        tmpValue = -tmpValue;
        value    = -value;
        pBuf[pos++] = '-';
    }

    // calculate the required length of the buffer
    do {
        pos++;
        tmpValue /= base;
    } while(tmpValue > 0);


    if (pos > len)
    {
        // the len parameter is invalid.
        return;
    }

    pBuf[pos] = '\0';

    do {
        pBuf[--pos] = pAscii[value % base];
        value /= base;
    } while(value > 0);

    return;
}

int main(void)
{
	uint8_t buf[50];

	int8_t x = 0;
	int8_t y = 0;
	int8_t z = 0;
	int16_t temp = 0;
	uint8_t button_status;
	uint16_t trimpot_value;

	uint8_t RGB_on = 1;
	uint64_t counter = 0;

	Trimpot_init();
	RGB_Leds_init();
	OLED_display_init();
	Temperature_init(&getTicks);
	Accelerometer_init();

	OLED_display_clearScreen();
	OLED_display_putString(1,1,  (uint8_t*)"++Aviao Cajada++");
	OLED_display_putString(1,9, (uint8_t*)"IP Address:");
	sprintf((char*)buf, " %d.%d.%d.%d", MYIP_1, MYIP_2, MYIP_3, MYIP_4);
	OLED_display_putString(1,9, (uint8_t*)buf);
	OLED_display_putString(1,25, (uint8_t*)"Acc x  : ");
	OLED_display_putString(1,33, (uint8_t*)"Acc y  : ");
	OLED_display_putString(1,41, (uint8_t*)"Acc z  : ");
	OLED_display_putString(1,49, (uint8_t*)"Temp   : ");

	while(1)
	{
		if ( (counter % 32000) == 0 )
		{
			HTTPServer_reset();
		}

		if( (counter++ % 1000) == 0)
		{
			temp = Temperature_read();
			button_status = Button_read();
			Accelerometer_read(&x, &y, &z);;
			trimpot_value = Trimpot_read();

			if(button_status == 0)
			{
				RGB_on = !RGB_on;
			}

			if( (y > 10 + (trimpot_value/1000) * 2) && RGB_on )
			{
				RGB_Leds_setLeds(RGB_LEDS_BLUE);
			}
			else if( (y < -10 - (trimpot_value/1000) * 2) && RGB_on )
			{
				RGB_Leds_setLeds(RGB_LEDS_RED);
			}
			else
			{
				RGB_Leds_setLeds(0);
			}

			OLED_display_fillRect((1+9*6),17, 80, 24);
			if(RGB_on == 1)
			{
				OLED_display_putString(1,17, "RGB ON ");
			}
			else
			{
				OLED_display_putString(1,17, "RGB OFF");
			}

			intToString(x, buf, 10, 10);
			OLED_display_fillRect((1+9*6),25, 80, 32);
			OLED_display_putString((1+9*6),25, buf);

			intToString(y, buf, 10, 10);
			OLED_display_fillRect((1+9*6),33, 80, 40);
			OLED_display_putString((1+9*6),33, buf);

			intToString(z, buf, 10, 10);
			OLED_display_fillRect((1+9*6),41, 80, 48);
			OLED_display_putString((1+9*6),41, buf);

			intToString(temp, buf, 10, 10);
			OLED_display_fillRect((1+9*6),49, 80, 56);
			OLED_display_putString((1+9*6),49, buf);
		}

		if (!(SocketStatus & SOCK_ACTIVE)) TCPPassiveOpen();   // listen for incoming TCP-connection
		DoNetworkStuff();                                      // handle network and easyWEB-stack
														   // events
		HTTPServer();
	}

	return 0;
}
