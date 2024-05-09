/*
 * File Name: TerminateTask.c
 * Date: 11/2/2023
 * author: Omar Kadry
 * ----
 * Date  12/2/2023
 * Edited by: Ahmed Afifi
 */

#include "../osek_kernel.h"
#include "../check.h"
#include "../task.h"
#include "../inc/kernel.h"
StatusType
TerminateTask(void)
{
	StatusType	ercd = E_OK;
	CHECK_CALLEVEL(TCL_TASK);

	if(tcb_lastres[runtsk] != RESID_NULL){
		res_recovery();
		CHECK_RESOURCE(FALSE);
	}
	search_schedtsk();    // rescheduling.
	if (tcb_actcnt[runtsk] > 0)   // if the task has more activations.
	{
		tcb_actcnt[runtsk] -= 1;  //decrement the activation of the task.
		make_active(runtsk);      // use active task function.
	}
	exit_and_dispatch();
  
  error_exit:
	call_errorhook(ercd, OSServiceId_TerminateTask);
	return(ercd);
}
