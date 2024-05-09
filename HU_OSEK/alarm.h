



#ifndef ALARM_H_
#define ALARM_H_
#if (ALARMS_COUNT != 0)
extern TickType cnt_time[COUNTER_COUNT];
extern AlarmStateType alrm_state[ALARMS_COUNT];
extern AlarmTimeType alrm_time[ALARMS_COUNT];
extern AlarmCycleTimeType alrm_cycTime[ALARMS_COUNT];
extern CounterType alrmini_cnt[ALARMS_COUNT];
extern ActionType alrmini_act[ALARMS_COUNT];
extern ActionInfoType alrmini_actInfo[ALARMS_COUNT];
extern UINT8	cntini_AlrmNum[COUNTER_COUNT];
extern AlarmType* cntini_AlrmRef[COUNTER_COUNT];
extern TickType cntini_maxVal[COUNTER_COUNT];
extern TickType cntini_minCyc[COUNTER_COUNT];
extern TickType cntini_ticksPBase[COUNTER_COUNT];
#endif

#endif //ALARM_H_