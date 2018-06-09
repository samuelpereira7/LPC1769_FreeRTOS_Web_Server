/*
 * helper.h
 *
 *  Created on: 15 de abr de 2018
 *      Author: samuelpereira
 */

#ifndef COMMON_H_
#define COMMON_H_

#include <stdint.h>

void intToString(int value, uint8_t* pBuf, uint32_t len, uint32_t base);

typedef enum enuSource
{
	ACC = 0,
	TRIM,
	BUT,
	TEMP,
}source_t;

typedef struct message
{
	source_t source;
	uint16_t payload[3];
}message_t;

typedef void (*callback_t)(message_t msg);

#endif /* COMMON_H_ */
