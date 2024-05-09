/*
 * Timer_Registers.h
 *
 *  Created on: Mar 18, 2023
 *      Author: Aliaa Mohamed
 */

#ifndef TIMER_HW_TIMER_REGISTERS_H_
#define TIMER_HW_TIMER_REGISTERS_H_
#include "../../inc/osek.h"

#define TIM (*(volatile TIMER_strct *)0xEC000000)

typedef struct{
	UINT32 CTRL;
	UINT32 CFG;
	UINT8 res[8];
	UINT32 CNT0;
	UINT32 CNT1;
	UINT8 res1[8];
	UINT32 RLD0;
	UINT32 RLD1;
}TIMER_strct;

//*****************************************************************//
//
// The following are the define for the bit fields in TIM_CTRL register
//
//*****************************************************************//
#define TSRC11 0x1000

#define TSRC10 0x0800

#define TF1 0x0200

#define TR1 0x0100

#define TSRC01 0x0010

#define TSRC00 0x0008
//#define TSRC0 0x0008

#define TF0 0x0002

#define TR0 0x0001

#ifndef NULL
#define	NULL			((void *) 0)
#endif
//*********************End of TIM_CFG Reg**************************//
//*****************************************************************//
//
// The following are the define for the bit fields in TIM_CTRL register
//
//*****************************************************************//
#define TPR_DIS1 0x0800

#define TPR11 0x0200

#define TPR10 0x0100

#define TPR_DIS0 0x0008

#define TPR01 0x0002

#define TPR00 0x0001
//#define TSRC0 0x0008

//*********************End of TIM_CFG Reg**************************//

//*****************************************************************//
//
// The following are the define for the bit fields in TIM_CTRL register
//
//*****************************************************************//
#define TSRC11 0x1000

#define TSRC10 0x0800

#define TF1 0x0200

#define TR1 0x0100

#define TSRC01 0x0010

#define TSRC00 0x0008
//#define TSRC0 0x0008

#define TF0 0x0002

#define TR0 0x0001

//*********************End of TIM_CTRL Reg**************************//

#endif /* TIMER_HW_TIMER_REGISTERS_H_ */
