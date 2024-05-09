
#include "AlarmsHeader.h"
#if (ALARMS_COUNT != 0)
StatusType CancelAlarm(AlarmType alarmID){
	StatusType ercd = E_OK;

	CHECK_CALLEVEL(TCL_TASK | TCL_ISR2);
	CHECK_ALMID(alarmID);	/* check if the alarm id is in range */
	CHECK_NOFUNC(alrm_state[alarmID] == 0);/*Check if the alarm is running*/

	alrm_state[alarmID] = 0;
	
	return ercd;
	error_exit:
		_errorhook_par1.almid=alarmID;
		call_errorhook(ercd, OSServiceId_CancelAlarm);
		return ercd;
}
#endif 
/*==================[end of file]============================================*/

