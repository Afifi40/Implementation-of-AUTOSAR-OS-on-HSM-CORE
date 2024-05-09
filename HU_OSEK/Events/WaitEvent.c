/*
 * File Name: WaitEvent.c
 * Date: 23/2/2023
 * author: Ziad Ahmed
 */

#include "../osek_kernel.h"
#include "../check.h"
#include "../task.h"

#if (EXT_TASK_COUNT != 0)
StatusType WaitEvent(EventMaskType mask)
{
	StatusType	ercd = E_OK;

	CHECK_CALLEVEL(TCL_TASK);
	CHECK_ACCESS(runtsk < EXT_TASK_COUNT);
	CHECK_RESOURCE(tcb_lastres[runtsk] == RESID_NULL);
	
	if((tinib_mskevt[runtsk] & mask ) != EVTMASK_NONE){
		if ((tcb_curevt[runtsk] & mask) == EVTMASK_NONE) {
			tcb_curpri[runtsk] = tinib_inipri[runtsk];
			tcb_waievt[runtsk] = mask;
			search_schedtsk();
			dispatch();
			tcb_curpri[runtsk] = tinib_exepri[runtsk];
		}
		else{
			tcb_curevt[runtsk] &= ~mask;
		}
	}
	return(ercd);

  error_exit:
	_errorhook_par1.mask = mask;
	call_errorhook(ercd, OSServiceId_WaitEvent);
	return(ercd);
}
#endif