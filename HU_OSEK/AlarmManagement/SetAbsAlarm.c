
#include "AlarmsHeader.h"
#if (ALARMS_COUNT != 0)
StatusType SetAbsAlarm(AlarmType alarmID, TickType start, TickType cycle)
{
	StatusType ercd = E_OK;

	CHECK_CALLEVEL(TCL_TASK | TCL_ISR2);
	CHECK_ALMID(alarmID);/* check if the alarm id is in range */
	/* check that increment and cycle are in range */
	CHECK_VALUE( ((start+cnt_time[alrmini_cnt[alarmID]]) > cntini_maxVal[alrmini_cnt[alarmID]]) ||
			   ( ( cycle == 0 ) && ( (cycle > cntini_maxVal[alrmini_cnt[alarmID]]) ||
			   (cycle < cntini_minCyc[alrmini_cnt[alarmID]]) ) ) );
	CHECK_STATE(alrm_state[alarmID] != 0);/* check if the alarm is disabled */

	//IntSecure_start();

	/* enable alarm */
	alrm_state[alarmID] = 1;

	/* set abs alarm */
	alrm_time[alarmID] = cnt_time[alrmini_cnt[alarmID]] + start;
	alrm_cycTime[alarmID] = cycle;

	//IntSecure_End();
	return ercd;
	error_exit:
	_errorhook_par1.almid=alarmID;
	_errorhook_par2.start=start;
	_errorhook_par3.cycle=cycle;
		call_errorhook(ercd, OSServiceId_SetAbsAlarm);
		return ercd;


}
#endif
