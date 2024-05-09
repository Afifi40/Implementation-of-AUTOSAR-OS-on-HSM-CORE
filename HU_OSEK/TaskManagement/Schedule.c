/*
 * File Name: Schedule.c
 * Date: 11/2/2023
 * author: Esraa Ahmed Taha
 */

#include "../osek_kernel.h"
#include "../check.h"
#include "../task.h"

StatusType Schedule(void)
{
	StatusType	ercd = E_OK;
	 CHECK_CALLEVEL(TCL_TASK);
	 CHECK_RESOURCE(tcb_lastres[runtsk] == RESID_NULL);

	if (tinib_inipri[runtsk] < nextpri) {   		//if the next task has higher priority than the running task initial priority
		tcb_curpri[runtsk] = tinib_inipri[runtsk];	//the current priority of the running task will be the initial priority of this task
		preempt();
		search_schedtsk();							//then we call preempt to reschedule and run the next task that has higher priority
		dispatch();									//then we call dispatch to make context switching
	}
		return(ercd);
	  error_exit:
		//lock_cpu();
		call_errorhook(ercd, OSServiceId_Schedule);
		return(ercd);
}
