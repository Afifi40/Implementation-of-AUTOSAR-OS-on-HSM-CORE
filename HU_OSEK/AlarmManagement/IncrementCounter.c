/*
 * Release_Res.c
 *
 *  Created on: May 6, 2023
 *      Author: Ziad
 */
#include "AlarmsHeader.h"
#if (ALARMS_COUNT != 0)
StatusType IncrementCounter(CounterType CounterID)
{
	StatusType ercd = E_OK;

	CHECK_CALLEVEL(TCL_TASK);
	CHECK_CNTID(CounterID);

	Increment_HW_Counter(CounterID, 1);
	return ercd;
	error_exit:
			_errorhook_par1.cntid = CounterID;
			call_errorhook(ercd, OSServiceId_IncrementCounter);
			return ercd;
}
#endif
