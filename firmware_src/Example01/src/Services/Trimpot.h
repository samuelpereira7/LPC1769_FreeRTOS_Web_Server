/*
 * Trimpot.h
 *
 *  Created on: 11 de abr de 2018
 *      Author: samuelpereira
 */

#ifndef SERVICES_TRIMPOT_H_
#define SERVICES_TRIMPOT_H_

#include <stdint.h>
#include "common.h"

void Trimpot_init(void);
void Trimpot_setCallback(callback_t c);
uint16_t Trimpot_read(void);

#endif /* SERVICES_TRIMPOT_H_ */
