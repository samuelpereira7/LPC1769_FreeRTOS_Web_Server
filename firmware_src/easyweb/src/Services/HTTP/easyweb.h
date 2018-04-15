/******************************************************************
 *****                                                        *****
 *****  Name: easyweb.h                                       *****
 *****  Ver.: 1.0                                             *****
 *****  Date: 07/05/2001                                      *****
 *****  Auth: Andreas Dannenberg                              *****
 *****        HTWK Leipzig                                    *****
 *****        university of applied sciences                  *****
 *****        Germany                                         *****
 *****  Func: header-file for easyweb.c                       *****
 *****                                                        *****
 ******************************************************************/

#ifndef __EASYWEB_H
#define __EASYWEB_H

void HTTPServer(void);
void InsertDynamicValues(void);

unsigned char *PWebSide;                         // pointer to webside
unsigned int HTTPBytesToSend;                    // bytes left to send

unsigned char HTTPStatus;                        // status byte 
#define HTTP_SEND_PAGE               0x01        // help flag

#endif

