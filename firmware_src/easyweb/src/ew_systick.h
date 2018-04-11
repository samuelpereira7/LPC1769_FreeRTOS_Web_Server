/*
 * ew_systick.h
 *
 *  Created on: 10 de abr de 2018
 *      Author: samuelpereira
 */

#ifndef EW_SYSTICK_H_
#define EW_SYSTICK_H_

void Start_SysTick10ms(void);
void Start_SysTick1ms(void);
uint32_t getTicks(void);

#endif /* EW_SYSTICK_H_ */
