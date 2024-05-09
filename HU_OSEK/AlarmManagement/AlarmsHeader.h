/*
 * AlarmsHeader.h
 *
 *  Created on: Apr 30, 2023
 *      Author: ahmed
 */

#ifndef ALARMMANAGEMENT_ALARMSHEADER_H_
#define ALARMMANAGEMENT_ALARMSHEADER_H_

#include "../osek_kernel.h"
#include "../inc/kernel_cfg.h"
#include "../check.h"
#if ALARMS_COUNT !=0
extern TickType cnt_time[];
extern AlarmStateType alrm_state[];
extern AlarmTimeType alrm_time[];
extern AlarmCycleTimeType alrm_cycTime[];
extern const CounterType alrmini_cnt[];
extern const ActionType alrmini_act[];
extern const ActionInfoType alrmini_actInfo[];
extern const UINT8	cntini_AlrmNum[];
extern const AlarmType* cntini_AlrmRef[];
extern const TickType cntini_maxVal[];
extern const TickType cntini_minCyc[];
extern const TickType cntini_ticksPBase[];




#ifndef NULL
#define	NULL			((void *) 0)
#endif

extern AlarmIncrementType IncrementAlarm(AlarmType, AlarmIncrementType);
extern CounterIncrementType Increment_HW_Counter(CounterType, CounterIncrementType);

#endif
#endif /* ALARMMANAGEMENT_ALARMSHEADER_H_ */
