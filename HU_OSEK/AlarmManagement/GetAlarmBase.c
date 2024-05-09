


#include "AlarmsHeader.h"

#if (ALARMS_COUNT != 0)
StatusType GetAlarmBase(AlarmType alarmID, AlarmBaseRefType Info)
{
	StatusType ercd = E_OK;
	CounterType counter;

	CHECK_CALLEVEL(TCL_TASK | TCL_ISR2 | TCL_ERROR | TCL_PREPOST);
	CHECK_ALMID(alarmID);

	/* get counter of this alarm */
	counter = alrmini_cnt[alarmID];

	/*
	 ** characteristics. The return value Info is a structure in which the
	 ** information of data type AlarmBaseType is stored
	 */
	Info->maxallowedvalue = cntini_maxVal[counter];
	Info->ticksperbase = cntini_ticksPBase[counter];
	Info->mincycle = cntini_minCyc[counter];

	return ercd;
	error_exit:
		_errorhook_par1.almid=alarmID;
		call_errorhook(ercd, OSServiceId_ActivateTask);
		return ercd;
}
#endif 

