/*
 * File Name: ClearEvent.c
 * Date: 23/2/2023
 * author: Ziad Ahmed
 */
#include "../osek_kernel.h"
#include "../check.h"
#include "../task.h"

#if (EXT_TASK_COUNT != 0)
StatusType ClearEvent(EventMaskType mask)
{
    StatusType	ercd;
	CHECK_CALLEVEL(TCL_TASK);
	CHECK_ACCESS(runtsk < EXT_TASK_COUNT);

	tcb_curevt[runtsk] &= ~mask;

	return(E_OK); //No error

  error_exit:
	_errorhook_par1.mask = mask;
	call_errorhook(ercd, OSServiceId_ClearEvent);
	return(ercd); // Error detected
}
#endif
