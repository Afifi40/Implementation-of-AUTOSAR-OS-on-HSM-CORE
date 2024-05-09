/*
 * task.c
 * Date : 12/2/2023
 * Author: Ahmed Afifi
 *
 */

#include "../osek_kernel.h"
#include "../check.h"
#include "../task.h"

StatusType
GetTaskID(TaskRefType p_tskid)
{
	StatusType	ercd = E_OK;
	CHECK_CALLEVEL(TCL_TASK | TCL_ISR2 | TCL_ERROR | TCL_PREPOST);

	*p_tskid = runtsk;
	return(ercd);

	error_exit:
	call_errorhook(ercd, OSServiceId_GetTaskID);
	return(ercd);

}
