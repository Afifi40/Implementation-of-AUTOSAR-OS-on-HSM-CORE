/*
 * Release_Res.c
 *
 *  Created on: May 6, 2023
 *      Author: Ziad - Aliaa
 */
#include "AlarmsHeader.h"
#if (ALARMS_COUNT != 0)
StatusType SetRelAlarm(AlarmType alarmID, TickType Increment, TickType cycle)
{
	StatusType ercd = E_OK;

	CHECK_CALLEVEL(TCL_TASK | TCL_ISR2);
	CHECK_ALMID(alarmID);/* check if the alarm id is in range */
	/* check that increment and cycle are in range */
	CHECK_VALUE( (Increment > cntini_maxVal[alrmini_cnt[alarmID]]) ||
				   ( ( cycle == 0 ) && ( (cycle > cntini_maxVal[alrmini_cnt[alarmID]]) ||
				   (cycle < cntini_minCyc[alrmini_cnt[alarmID]]) ) ) );
	/* check if the alarm is disable */
	CHECK_STATE(alrm_state[alarmID] != 0);/* check if the alarm is disabled */
	//IntSecure_start();
	/* enable alarm */
	alrm_state[alarmID] = 1;

	/* set alarm */
	alrm_time[alarmID] = Increment;
	alrm_cycTime[alarmID] = cycle;
	//IntSecure_End();

	return ercd;
	error_exit:
		_errorhook_par1.almid=alarmID;
		_errorhook_par2.incr=Increment;
		_errorhook_par3.cycle=cycle;

		call_errorhook(ercd, OSServiceId_SetRelAlarm);
		return ercd;
}
#endif

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

