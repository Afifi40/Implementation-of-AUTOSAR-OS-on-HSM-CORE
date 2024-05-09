/*
 * File Name: GetEvent.c
 * Date: 23/2/2023
 * author: Ziad Ahmed
 */
#include "../osek_kernel.h"
#include "../check.h"
#include "../task.h"
#if (EXT_TASK_COUNT != 0)
StatusType GetEvent(TaskType tskid, EventMaskRefType p_mask)
{
    StatusType	ercd = E_OK;

	CHECK_CALLEVEL(TCL_TASK | TCL_ISR2 | TCL_ERROR | TCL_PREPOST);
	CHECK_TSKID(tskid);
	CHECK_ACCESS(tskid < EXT_TASK_COUNT);
	CHECK_STATE(tcb_tstat[tskid] != SUSPENDED);
	//Check that the Task is not in suspended state >>D_CHECK_STATE(tcb_tstat[tskid] != TS_DORMANT);

	*p_mask = tcb_curevt[tskid];


	return(ercd);

	error_exit:
	_errorhook_par1.tskid = tskid;
	_errorhook_par2.p_mask = p_mask;
	call_errorhook(ercd, OSServiceId_GetEvent);
	return(ercd);
}
#endif
