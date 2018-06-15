/*
 * ew_systick.h
 *
 *  Created on: 10 de abr de 2018
 *      Author: samuelpereira
 */

#ifndef SERVICES_SYSTICK_H_
#define SERVICES_SYSTICK_H_

#include <stdint.h>

void Start_SysTick10ms(void);
void Start_SysTick1ms(void);
uint32_t getTicks(void);

#endif /* SERVICES_SYSTICK_H_ */
