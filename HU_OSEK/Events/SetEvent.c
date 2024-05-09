/*
 * File Name: SetEvent.c
 * Date: 23/2/2023
 * author: Esraa Ahmed Taha
 */

#include "../osek_kernel.h"
#include "../check.h"
#include "../task.h"
#if (EXT_TASK_COUNT != 0)
StatusType SetEvent(TaskType tskid, EventMaskType mask)
{
	StatusType	ercd = E_OK;
    //check call level (Task, ISR cat 2)
    //check Task Id
    //check task access Extended 
    //check if task state is not SUSPENDED 
	CHECK_CALLEVEL(TCL_TASK | TCL_ISR2);
	CHECK_TSKID(tskid);
	CHECK_ACCESS(tskid < EXT_TASK_COUNT);

	if(tinib_mskevt[tskid] & mask != EVTMASK_NONE)
	{
		tcb_curevt[tskid] |= mask;                                                  //Mask --> curevent 
		if ((tcb_curevt[tskid] & tcb_waievt[tskid]) != EVTMASK_NONE) {              //check required event is being set
			tcb_waievt[tskid] = EVTMASK_NONE;                                       //wait --> non
			if ( (tcb_tstat[tskid] == WAITING) && (callevel == TCL_TASK))         //check if task state is WAITING
				if((make_runnable(tskid)))                                          //change task state to be READY && add to ready queue 
					dispatch();                                                     // schtask = taskid --> dispatch 
		
		}
	}
	return E_OK;
	error_exit:
		_errorhook_par1.tskid = tskid;
		_errorhook_par2.mask = mask;
		call_errorhook(ercd, OSServiceId_SetEvent);
		return(ercd);
}
#endif