/*
 * Button.h
 *
 *  Created on: 10 de abr de 2018
 *      Author: samuelpereira
 */

#ifndef SERVICES_BUTTON_H_
#define SERVICES_BUTTON_H_

#include <stdint.h>
#include "common.h"

void Button_init(void);
void Button_setCallback(callback_t c);
uint8_t Button_read(void);

#endif /* SERVICES_BUTTON_H_ */
