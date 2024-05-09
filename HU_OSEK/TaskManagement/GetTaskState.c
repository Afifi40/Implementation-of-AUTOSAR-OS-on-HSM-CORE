/*
 * task.c
 * Date : 12/2/2023
 * Author: Ahmed Afifi
 *
 */

#include "../osek_kernel.h"
#include "../check.h"
#include "../task.h"
#include "../inc/kernel.h"

StatusType
GetTaskState(TaskType tskid, TaskStateRefType p_state)
{
	StatusType	ercd = E_OK;
	CHECK_CALLEVEL(TCL_TASK | TCL_ISR2 | TCL_ERROR | TCL_PREPOST);
	CHECK_TSKID(tskid);
	*p_state = (tskid == runtsk) ? RUNNING : tcb_tstat[tskid];
	return(ercd);
	
	error_exit:
		_errorhook_par1.tskid = tskid;
		_errorhook_par2.p_state = p_state;
		call_errorhook(ercd, OSServiceId_GetTaskState);
	return(ercd);
}
