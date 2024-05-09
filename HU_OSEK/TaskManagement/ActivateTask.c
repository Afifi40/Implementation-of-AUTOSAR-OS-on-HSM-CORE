/*
 * ActivateTask.c
 *
 *  Created on: Feb 11, 2023
 *      Author: Aliaa
 */


#include "../osek_kernel.h"
#include "../check.h"
#include "../task.h"

StatusType
ActivateTask(TaskType tskid)
{
	/** System call? privaliged vs non-privaliged **/
	StatusType	ercd;

	//Enter/log the active task with the tasks that are active
	CHECK_CALLEVEL(TCL_TASK | TCL_ISR2);
	CHECK_TSKID(tskid);


	//lock the cpu and start checking on the state then make active
	if (tcb_tstat[tskid] == SUSPENDED) {//if the task in the terminate state
		if ((make_active(tskid)&& (callevel == TCL_TASK)) ) {//if the task is in the normal task call && by using make active function and returned true
			dispatch();
		}
	}
	else if (tcb_actcnt[tskid] < tinib_maxact[tskid]) {//else if there are multiple request to activate the task and didn't reach the max multiple reactivation
		tcb_actcnt[tskid] += 1;//increment the multiple request by one
	}
	else {
		//there is an error limit

		ercd = E_OS_LIMIT;
		//exit and return error
		goto error_exit;
	}
		return(E_OK);
	error_exit:
		_errorhook_par1.tskid = tskid;/**TODO**/
		call_errorhook(ercd, OSServiceId_ActivateTask);
		return(ercd);
}
