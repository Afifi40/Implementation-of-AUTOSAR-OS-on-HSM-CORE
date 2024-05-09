/*
 * Timer_implementation.c
 *
 *  Created on: Mar 18, 2023
 *      Author: Aliaa Mohamed
 */
#include "Timer_implementation.h"
#if ALARMS_COUNT != 0 
//static volatile OvfCounter=0;
static TickType rest[COUNTER_HW_COUNT]={0};

void (*timer0_ovf_isr)(void);
void (*timer1_ovf_isr)(void);

void Timer0_init(UINT8 ClkSrc, UINT8 Prescaler_enable,UINT16 prescaler)
{
	//TIM_CTRL |= 1<<TR0; //Timer 0 Run (Start Timer 0)

	SETBIT(TIM.CTRL,TR0);
	switch(ClkSrc)
	{
		case(0):
				//Timer0 clock source 0
				CLRBIT(TIM.CTRL,TSRC00);
				CLRBIT(TIM.CTRL,TSRC01);
			break;
		case(1):
				//Timer0 clock source 1
				SETBIT(TIM.CTRL,TSRC00);
				CLRBIT(TIM.CTRL,TSRC01);
				break;
		case(2):
				//Timer0 clock source 2
				CLRBIT(TIM.CTRL,TSRC00);
				SETBIT(TIM.CTRL,TSRC01);
				break;
		case(3):
				//Timer0 clock source 3
				SETBIT(TIM.CTRL,TSRC00);
				SETBIT(TIM.CTRL,TSRC01);
				break;
		default:
				//Initially Timer0 clock source 0 is the default
				CLRBIT(TIM.CTRL,TSRC00);
				CLRBIT(TIM.CTRL,TSRC01);
				break;
	}

	if(Prescaler_enable==1)
	{
		//enable pre-scaler
		CLRBIT(TIM.CFG,TPR_DIS0);
		switch(prescaler)
				{
				case(4):
				//pre-scaler = 4
					CLRBIT(TIM.CFG,TPR00);
					CLRBIT(TIM.CFG,TPR01);
					break;
				case(16):
				//pre-scaler = 16
				SETBIT(TIM.CFG,TPR00);
				CLRBIT(TIM.CFG,TPR01);
					break;
				case(64):
				//pre-scaler = 64
					CLRBIT(TIM.CFG,TPR00);
					SETBIT(TIM.CFG,TPR01);
					break;
				case(512):
				//pre-scaler = 512
					SETBIT(TIM.CFG,TPR00);
					SETBIT(TIM.CFG,TPR01);
						break;
				default:
					//Initially Timer0 clock source 0 is the default
					CLRBIT(TIM.CTRL,TSRC00);
					CLRBIT(TIM.CTRL,TSRC01);
					break;
				}
	}
	else
	{
		//disable pre-scaler
		SETBIT(TIM.CFG,TPR_DIS0);
	}

	//timer 0 pres-caler disabled
	/*if we put 0 then the pre-scaler is enabled
	 * if 1 then the pre-scaler is disabled


	 * Timer pre-scaler adjust
	 * we have 4 division factor
	 * 1(when pre-scaler disabled)
	 * 4 - 16 - 64 - 512*/
	/*//pre-scaler = 4
	 * CLRBIT(TIM.CFG,TPR00);
	 * CLRBIT(TIM.CFG,TPR01);
	 */
	/*//pre-scaler = 16
	 * SETBIT(TIM.CFG,TPR00);
	 * CLRBIT(TIM.CFG,TPR01);
	 */
	/*//pre-scaler = 64
	 * CLRBIT(TIM.CFG,TPR00);
	 * SETBIT(TIM.CFG,TPR01);
	 */
	/*//pre-scaler = 512
	 * SETBIT(TIM.CFG,TPR00);
	 * SETBIT(TIM.CFG,TPR01);
	 */
	/*
	 * Timer0 counter register value
	 * TIM_CNT0 --> timer0 counter register from 16 bit
	 */
	/*
	 * Timer0 Reload register value
	 * TIM_RLD0 --> timer0 counter register from 16 bit
	 */
}
void Timer1_init(UINT8 ClkSrc,UINT8 Prescaler_enable,UINT16 prescaler)
{
		TIM.CTRL |= TR1 ; //Timer 0 Run (Start Timer 0)

		SETBIT(TIM.CTRL,TR0);
		switch(ClkSrc)
		{
			case(0):
					//Timer0 clock source 0
					CLRBIT(TIM.CTRL,TSRC10);
					CLRBIT(TIM.CTRL,TSRC11);
					break;
			case(1):
			//Timer0 clock source 1
					SETBIT(TIM.CTRL,TSRC10);
					CLRBIT(TIM.CTRL,TSRC11);
					break;
			case(2):
					//Timer0 clock source 2
					CLRBIT(TIM.CTRL,TSRC10);
					SETBIT(TIM.CTRL,TSRC11);
					break;
			case(3):
					//Timer0 clock source 3
					SETBIT(TIM.CTRL,TSRC10);
					SETBIT(TIM.CTRL,TSRC11);
					break;
			default:
					//Initially Timer0 clock source 0 is the default
					CLRBIT(TIM.CTRL,TSRC10);
					CLRBIT(TIM.CTRL,TSRC11);
					break;
		}

		if(Prescaler_enable==1)
		{
			//enable pre-scaler
			CLRBIT(TIM.CFG,TPR_DIS0);
			switch(prescaler)
			{
					case(4):
					//pre-scaler = 4
						CLRBIT(TIM.CFG,TPR10);
						CLRBIT(TIM.CFG,TPR11);
						break;
					case(16):
					//pre-scaler = 16
					SETBIT(TIM.CFG,TPR10);
					CLRBIT(TIM.CFG,TPR11);
						break;
					case(64):
					//pre-scaler = 64
						CLRBIT(TIM.CFG,TPR10);
						SETBIT(TIM.CFG,TPR11);
						break;
					case(512):
					//pre-scaler = 512
						SETBIT(TIM.CFG,TPR10);
						SETBIT(TIM.CFG,TPR11);
							break;
					default:
						//Initially Timer0 clock source 0 is the default
						CLRBIT(TIM.CTRL,TSRC10);
						CLRBIT(TIM.CTRL,TSRC11);
						break;
				}
		}
		else
		{
			//disable pre-scaler
			SETBIT(TIM.CFG,TPR_DIS0);
		}

		//Initially Timer1 clock source 0 is the default
		//CLRBIT(TIM.CTRL,TSRC10);
		//CLRBIT(TIM.CTRL,TSRC11);

		/*//Timer0 clock source 1
		SETBIT(TIM.CTRL,TSRC10);
		CLRBIT(TIM.CTRL,TSRC11);
		 */

		/*//Timer0 clock source 2
		CLRBIT(TIM.CTRL,TSRC10);
		SETBIT(TIM.CTRL,TSRC11);*/

		/*//Timer0 clock source 3
		SETBIT(TIM.CTRL,TSRC10);
		SETBIT(TIM.CTRL,TSRC11);*/

		//enable pre-scaler

		//CLRBIT(TIM.CFG,TPR_DIS1);

		//disable pre-scaler
		//SETBIT(TIM.CFG,TPR_DIS1);
		/*
		 * Timer pre-scaler adjust
		 * we have 4 division factor
		 * 1(when pre-scaler disabled)
		 * 4 - 16 - 64 - 512*/
		/*//pre-scaler = 4
		 * CLRBIT(TIM.CFG,TPR10);
		 * CLRBIT(TIM.CFG,TPR11);
		 */
		/*//pre-scaler = 16
		 * SETBIT(TIM.CFG,TPR10);
		 * CLRBIT(TIM.CFG,TPR11);
		 */
		/*//pre-scaler = 64
		 * CLRBIT(TIM.CFG,TPR10);
		 * SETBIT(TIM.CFG,TPR11);
		 */
		/*//pre-scaler = 512
		 * SETBIT(TIM.CFG,TPR10);
		 * SETBIT(TIM.CFG,TPR11);
		 */
		/*Timer1 counter register value
		 * TIM_CNT1 --> timer1 counter register */
		/*
		 * Timer1 Reload register value
		 * TIM_RLD0 --> timer0 counter register from 16 bit
		 */
}



void Timer0_Handler(void)
{
	for(UINT8 i =0;i<COUNTER_HW_COUNT;i++)
	{
		if (rest[i]--==0)
			{
				rest[i] = Increment_HW_Counter(i,rest[i]);  /*ISR_TODO*/  /*hardware counter*/
			}
	}

}
void Timer1_Handler(void)
{
	for(UINT8 i =0;i<COUNTER_HW_COUNT;i++)
		{
			if (rest[i]--==0)
				{
					rest[i] = Increment_HW_Counter(i,rest[i]);  /*ISR_TODO*/  /*hardware counter*/
				}
		}
}
#endif