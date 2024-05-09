
#include "AlarmsHeader.h"
#if (ALARMS_COUNT != 0)
StatusType GetAlarm(AlarmType alarmID, TickRefType Tick) {

	StatusType ercd = E_OK;

	/* check if it handle of a valid alarmID */
	CHECK_CALLEVEL(TCL_TASK | TCL_ISR2 | TCL_ERROR | TCL_PREPOST);
	CHECK_ALMID(alarmID);	/* check if the alarm id is in range */
	CHECK_NOFUNC(alrm_state[alarmID] == 0);/*Check if the alarm is running*/

	*Tick = alrm_time[alarmID];

	return ercd;
	error_exit:
		_errorhook_par1.almid=alarmID;
		call_errorhook(ercd, OSServiceId_ActivateTask);
		return ercd;
}
#endif
