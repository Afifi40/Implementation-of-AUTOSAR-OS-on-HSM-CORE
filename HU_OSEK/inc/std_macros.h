/*
 * std_macros.h
 *
 *  Created on: Mar 20, 2023
 *      Author: lenovo
 */

#ifndef TIMER_HW_STD_MACROS_H_
#define TIMER_HW_STD_MACROS_H_

#define SETBIT(REG,PIN) (REG |= PIN)
#define CLRBIT(REG,PIN) (REG &= ~(PIN))
#define TOGBIT(REG,PIN) (REG ^= PIN)
#define READBIT(REG,PIN)  ((REG >> PIN) & 1)

#endif /* TIMER_HW_STD_MACROS_H_ */
