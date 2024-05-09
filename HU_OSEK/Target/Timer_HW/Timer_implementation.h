/*
 * Timer_implementation.h
 *
 *  Created on: Mar 18, 2023
 *      Author: Aliaa Mohamed
 */


#ifndef TIMER_IMPLEMENTAION_TIMER_IMPLEMENTATION_H_
#define TIMER_IMPLEMENTAION_TIMER_IMPLEMENTATION_H_

#include "../../inc/std_macros.h"
#include "../../inc/kernel_cfg.h"
#include "../../AlarmManagement/AlarmsHeader.h"
#include "Timer_Registers.h"



void Timer0_init(UINT8 ClkSrc, UINT8 Prescaler_enable,UINT16 prescaler);

void Timer1_init(UINT8 ClkSrc, UINT8 Prescaler_enable,UINT16 prescaler);

void timer1_isr_function(void (userISR(void)));
void timer0_isr_function(void (userISR(void)));

void Timer0_Handler(void);
void Timer1_Handler(void);
#endif /* TIMER_IMPLEMENTAION_TIMER_IMPLEMENTATION_H_ */
