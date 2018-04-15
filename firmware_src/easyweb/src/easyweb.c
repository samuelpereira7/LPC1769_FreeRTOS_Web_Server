/******************************************************************
 *****                                                        *****
 *****  Name: easyweb.c                                       *****
 *****  Ver.: 1.0                                             *****
 *****  Date: 07/05/2001                                      *****
 *****  Auth: Andreas Dannenberg                              *****
 *****        HTWK Leipzig                                    *****
 *****        university of applied sciences                  *****
 *****        Germany                                         *****
 *****        adannenb@et.htwk-leipzig.de                     *****
 *****  Func: implements a dynamic HTTP-server by using       *****
 *****        the easyWEB-API                                 *****
 *****  Rem.: In IAR-C, use  linker option                    *****
 *****        "-e_medium_write=_formatted_write"              *****
 *****                                                        *****
 ******************************************************************/

// Modifications by Code Red Technologies for NXP LPC1768

// CodeRed - removed header for MSP430 microcontroller
//#include "msp430x14x.h"

#include "stdlib.h"
#include "stdio.h"
#include "string.h"

// CodeRed - added #define extern on next line (else variables
// not defined). This has been done due to include the .h files 
// rather than the .c files as in the original version of easyweb.
#define extern 

#include "easyweb.h"

// CodeRed - removed header for original ethernet controller
//#include "cs8900.c"                              // ethernet packet driver

//CodeRed - added for LPC ethernet controller
#include "ethmac.h"

// CodeRed - include .h rather than .c file
// #include "tcpip.c"                               // easyWEB TCP/IP stack
#include "tcpip.h"                               // easyWEB TCP/IP stack


// CodeRed - include renamed .h rather than .c file
// #include "webside.c"                             // webside for our HTTP server (HTML)
#include "webside.h"                             // webside for our HTTP server (HTML)

#include "ew_systick.h"
#include "Services/Temperature.h"
#include "Services/Button.h"
#include "Services/Accelerometer.h"
#include "Services/Trimpot.h"
#include "Services/RGB_Leds.h"
#include "Services/OLED_display.h"

// CodeRed - added for use in dynamic side of web page
unsigned int aaPagecounter=0;
unsigned int adcValue = 0;
char b[20];
static int8_t x = 0, y = 0, z = 0;
static int16_t temp = 0;

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

int main (void)
{
	uint8_t buf[50];
	int32_t xoff = 0;
	int32_t yoff = 0;
	int32_t zoff = 0;

	Trimpot_init();
//	RGB_Leds_init();

    OLED_display_init();

    Temperature_init(&getTicks);
    Accelerometer_init();
    Accelerometer_read(&x, &y, &z);
	xoff = 0-x;
	yoff = 0-y;
	zoff = 64-z;

	OLED_display_clearScreen();
	OLED_display_putString(1,1,  (uint8_t*)"EasyWeb Demo");
	OLED_display_putString(1,9, (uint8_t*)"IP Address:");
    sprintf((char*)buf, " %d.%d.%d.%d", MYIP_1, MYIP_2, MYIP_3, MYIP_4);
    OLED_display_putString(1,17, (uint8_t*)buf);
    OLED_display_putString(1,25, (uint8_t*)"Acc x  : ");
    OLED_display_putString(1,33, (uint8_t*)"Acc y  : ");
    OLED_display_putString(1,41, (uint8_t*)"Acc z  : ");
    OLED_display_putString(1,49, (uint8_t*)"Temp   : ");

	//TCPLowLevelInit();

/*
  *(unsigned char *)RemoteIP = 24;               // uncomment those lines to get the
  *((unsigned char *)RemoteIP + 1) = 8;          // quote of the day from a real
  *((unsigned char *)RemoteIP + 2) = 69;         // internet server! (gateway must be
  *((unsigned char *)RemoteIP + 3) = 7;          // set to your LAN-router)

  TCPLocalPort = 2025;
  TCPRemotePort = TCP_PORT_QOTD;

  TCPActiveOpen();

  while (SocketStatus & SOCK_ACTIVE)             // read the quote from memory
  {                                              // by using the hardware-debugger
    DoNetworkStuff();
  }
*/

	HTTPStatus = 0;                                // clear HTTP-server's flag register

	TCPLocalPort = TCP_PORT_HTTP;                  // set port we want to listen to

	static uint64_t counter = 0;
	int c2 = 0;


  	while (1)                                      // repeat forever
	{
  		if ( (counter % 32000) == 0 )
  		{
  			TCPLowLevelInit();
  			c2++;
  		}

  		if( (counter++ % 1000) == 0)
  		{
  			temp = Temperature_read();
  			//int button = Button_read();
  			Accelerometer_read(&x, &y, &z);
  			x += xoff;
  			y += yoff;
  			z += zoff;
  			//int trim = Trimpot_read();

  			memset(b,' ',20);
  			sprintf (b, ",%d,%d,%d,%d,\n", x, y, z, temp);

  			//	RGB_Leds_setLeds(RGB_LEDS_RED);
  			//	RGB_Leds_setLeds(0);
  			//	RGB_Leds_setLeds(RGB_LEDS_GREEN);
  			//	RGB_Leds_setLeds(0);
  			//	RGB_Leds_setLeds(RGB_LEDS_BLUE);
  			//	RGB_Leds_setLeds(0);

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
}

// This function implements a very simple dynamic HTTP-server.
// It waits until connected, then sends a HTTP-header and the
// HTML-code stored in memory. Before sending, it replaces
// some special strings with dynamic values.
// NOTE: For strings crossing page boundaries, replacing will
// not work. In this case, simply add some extra lines
// (e.g. CR and LFs) to the HTML-code.

void HTTPServer(void)
{
  if (SocketStatus & SOCK_CONNECTED)             // check if somebody has connected to our TCP
  {
    if (SocketStatus & SOCK_DATA_AVAILABLE)      // check if remote TCP sent data
      TCPReleaseRxBuffer();                      // and throw it away

    if (SocketStatus & SOCK_TX_BUF_RELEASED)     // check if buffer is free for TX
    {
      if (!(HTTPStatus & HTTP_SEND_PAGE))        // init byte-counter and pointer to webside
      {                                          // if called the 1st time
        HTTPBytesToSend = sizeof(WebSide) - 1;   // get HTML length, ignore trailing zero
        PWebSide = (unsigned char *)WebSide;     // pointer to HTML-code
      }

      if (HTTPBytesToSend > MAX_TCP_TX_DATA_SIZE)     // transmit a segment of MAX_SIZE
      {
        if (!(HTTPStatus & HTTP_SEND_PAGE))           // 1st time, include HTTP-header
        {
          memcpy(TCP_TX_BUF, GetResponse, sizeof(GetResponse) - 1);
          memcpy(TCP_TX_BUF + sizeof(GetResponse) - 1, PWebSide, MAX_TCP_TX_DATA_SIZE - sizeof(GetResponse) + 1);
          HTTPBytesToSend -= MAX_TCP_TX_DATA_SIZE - sizeof(GetResponse) + 1;
          PWebSide += MAX_TCP_TX_DATA_SIZE - sizeof(GetResponse) + 1;
        }
        else
        {
          memcpy(TCP_TX_BUF, PWebSide, MAX_TCP_TX_DATA_SIZE);
          HTTPBytesToSend -= MAX_TCP_TX_DATA_SIZE;
          PWebSide += MAX_TCP_TX_DATA_SIZE;
        }
          
        TCPTxDataCount = MAX_TCP_TX_DATA_SIZE;   // bytes to xfer
        InsertDynamicValues();                   // exchange some strings...
        TCPTransmitTxBuffer();                   // xfer buffer
      }
      else if (HTTPBytesToSend)                  // transmit leftover bytes
      {
        memcpy(TCP_TX_BUF, PWebSide, HTTPBytesToSend);
        TCPTxDataCount = HTTPBytesToSend;        // bytes to xfer
        InsertDynamicValues();                   // exchange some strings...
        TCPTransmitTxBuffer();                   // send last segment
        TCPClose();                              // and close connection
        HTTPBytesToSend = 0;                     // all data sent
      }

      HTTPStatus |= HTTP_SEND_PAGE;              // ok, 1st loop executed
    }
  }
  else
    HTTPStatus &= ~HTTP_SEND_PAGE;               // reset help-flag if not connected
}

// Code Red - new version of InsertDynamicValues()
void InsertDynamicValues(void)
{
	//memset(&WebSide[205],' ', 25);
	//memcpy(&WebSide[205], b, 20);

	unsigned char *Key;
	char NewKey[6];
    unsigned int i;
  
  if (TCPTxDataCount < 4) return;                     // there can't be any special string
  
  Key = TCP_TX_BUF;

  for (i = 0; i < (TCPTxDataCount - 3); i++)
  {
    if (*Key == 'A')
     if (*(Key + 1) == 'C')
		 switch (*(Key + 2))
		 {
		   case 'X' :                                // "AD8%"?
		   {
			 sprintf(NewKey, "%04d", x);     // insert pseudo-ADconverter value
			 memcpy(Key, NewKey, 4);
			 break;
		   }
		   case 'Y' :                                 // "AD7%"?
		   {
			 sprintf(NewKey, "%04d", y);     // copy saved value from previous read
			 memcpy(Key, NewKey, 4);
			 break;
		   }
		   case 'Z' :                                 // "AD1%"?
		   {
			 sprintf(NewKey, "%04d", z);    // increment and insert page counter
			 memcpy(Key, NewKey, 4);
	//			 *(Key + 3) = ' ';
			 break;
		   }
		   case 'T' :                                 // "AD1%"?
		   {
			 sprintf(NewKey, "%03u", temp);    // increment and insert page counter
			 memcpy(Key, NewKey, 3);
	//			 *(Key + 3) = ' ';
			 break;
		   }
		 }
    Key++;
  }
}
