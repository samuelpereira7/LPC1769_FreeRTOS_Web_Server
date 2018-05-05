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

// Modifications by Code Red Technologies for NXP LPC1769
#include "stdlib.h"
#include "stdio.h"

// CodeRed - added #define extern on next line (else variables
// not defined). This has been done due to include the .h files 
// rather than the .c files as in the original version of easyweb.
#define extern 

#include <HTTP_Server.h>

//CodeRed - added for LPC ethernet controller
#include "ethmac.h"

// CodeRed - include .h rather than .c file
// #include "tcpip.c"                               // easyWEB TCP/IP stack
#include "tcpip.h"                               // easyWEB TCP/IP stack

// CodeRed - include renamed .h rather than .c file
// #include "webside.c"                             // webside for our HTTP server (HTML)
#include "webside.h"                             // webside for our HTTP server (HTML)

#include <Systick.h>
#include "Temperature.h"
#include "Accelerometer.h"

// This function implements a very simple dynamic HTTP-server.
// It waits until connected, then sends a HTTP-header and the
// HTML-code stored in memory. Before sending, it replaces
// some special strings with dynamic values.
// NOTE: For strings crossing page boundaries, replacing will
// not work. In this case, simply add some extra lines
// (e.g. CR and LFs) to the HTML-code.

const unsigned char GetResponse[] =   // 1st thing our server sends to a client
		{ "HTTP/1.0 200 OK\r\n"     // protocol ver 1.0, code 200, reason OK
						"Content-Type: text/html\r\n"// type of data we want to send
						"\r\n"               // indicate end of HTTP-header
		};

void HTTP_Server_reset(void)
{
	HTTPStatus = 0;                                // clear HTTP-server's flag register

	TCPLocalPort = TCP_PORT_HTTP;                  // set port we want to listen to

	TCPLowLevelInit();
}

void HTTP_Server_process( void )
{
	if (SocketStatus & SOCK_CONNECTED) // check if somebody has connected to our TCP
	{
		if (SocketStatus & SOCK_DATA_AVAILABLE) // check if remote TCP sent data
			TCPReleaseRxBuffer();                      // and throw it away

		if (SocketStatus & SOCK_TX_BUF_RELEASED) // check if buffer is free for TX
		{
			if (!(HTTPStatus & HTTP_SEND_PAGE)) // init byte-counter and pointer to webside
			{                              // if called the 1st time
				HTTPBytesToSend = sizeof(WebSide) - 1; // get HTML length, ignore trailing zero
				PWebSide = (unsigned char *) WebSide; // pointer to HTML-code
			}

			if (HTTPBytesToSend > MAX_TCP_TX_DATA_SIZE) // transmit a segment of MAX_SIZE
			{
				if (!(HTTPStatus & HTTP_SEND_PAGE)) // 1st time, include HTTP-header
				{
					memcpy( TCP_TX_BUF, GetResponse, sizeof(GetResponse) - 1 );
					memcpy( TCP_TX_BUF + sizeof(GetResponse) - 1, PWebSide,
					MAX_TCP_TX_DATA_SIZE - sizeof(GetResponse) + 1 );
					HTTPBytesToSend -= MAX_TCP_TX_DATA_SIZE
							- sizeof(GetResponse) + 1;
					PWebSide += MAX_TCP_TX_DATA_SIZE - sizeof(GetResponse) + 1;
				}
				else
				{
					memcpy( TCP_TX_BUF, PWebSide,
					MAX_TCP_TX_DATA_SIZE );
					HTTPBytesToSend -= MAX_TCP_TX_DATA_SIZE;
					PWebSide += MAX_TCP_TX_DATA_SIZE;
				}

				TCPTxDataCount = MAX_TCP_TX_DATA_SIZE; // bytes to xfer
				InsertDynamicValues();  // exchange some strings...
				TCPTransmitTxBuffer();               // xfer buffer
			}
			else if (HTTPBytesToSend)         // transmit leftover bytes
			{
				memcpy( TCP_TX_BUF, PWebSide, HTTPBytesToSend );
				TCPTxDataCount = HTTPBytesToSend;   // bytes to xfer
				InsertDynamicValues();  // exchange some strings...
				TCPTransmitTxBuffer();         // send last segment
				TCPClose();                 // and close connection
				HTTPBytesToSend = 0;                // all data sent
			}

			HTTPStatus |= HTTP_SEND_PAGE;       // ok, 1st loop executed
		}
	}
	else
		HTTPStatus &= ~HTTP_SEND_PAGE;       // reset help-flag if not connected
}

// Code Red - new version of InsertDynamicValues()
void InsertDynamicValues( void )
{
	unsigned char *Key;
	char NewKey[6];
	unsigned int i;

	if (TCPTxDataCount < 4)
		return;                     // there can't be any special string

	Key = TCP_TX_BUF;

	for (i = 0; i < (TCPTxDataCount - 3); i++)
	{
		if (*Key == 'A')
		{
			if (*(Key + 1) == 'C')
			{
				switch (*(Key + 2))
				{
					case 'X':
						sprintf( NewKey, "%04d", Accelerometer_getX() );
						memcpy( Key, NewKey, 4 );
						break;
					case 'Y':
						sprintf( NewKey, "%04d", Accelerometer_getY() );
						memcpy( Key, NewKey, 4 );
						break;
					case 'Z':
						sprintf( NewKey, "%04d", Accelerometer_getZ() );
						memcpy( Key, NewKey, 4 );
						break;
					case 'T':
						sprintf( NewKey, "%03d", Temperature_getTemp() );
						memcpy( Key, NewKey, 3 );
						break;
				}
			}
		}
		Key++;
	}
}
