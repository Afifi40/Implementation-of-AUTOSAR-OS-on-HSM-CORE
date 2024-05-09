/*
 * File Name: ChainTask.c
 * Date: 11/2/2023
 * author: Esraa Ahmed Taha
 */

#include "../osek_kernel.h"
#include "../check.h"
#include "../task.h"
#include "../inc/kernel.h"

StatusType ChainTask(TaskType tskid)
{
	StatusType	ercd = E_OK;

	CHECK_CALLEVEL(TCL_TASK);
	CHECK_TSKID(tskid);
	if(tskid==runtsk)  //Case1: Chain to the same task
	{
		(void)make_active(runtsk);
	}

	else           //Chain to another task
	{
		if ((tcb_tstat[tskid] != SUSPENDED) && (tcb_actcnt[tskid] >= tinib_maxact[tskid]))   //Case2: Chain to task not in ready queue
		{
			 ercd = E_OS_LIMIT;
			 goto error_exit;
		} //CHECK OS LIMIT?!
		//Case3: otherwise
		if (tcb_actcnt[runtsk] > 0) 			// If Run Task (we want to terminate it) has another request to Run So decrement counter and make it active
		{
			tcb_actcnt[runtsk] -= 1;
			(void)make_active(runtsk);
		} //TODO: make the task active first
		if (tcb_tstat[tskid] == SUSPENDED) 	//if TASK was suspended then make it Active
			(void)make_active(tskid);
		else 									//Task in ready queue and no. of requests < the max No So increment  So increase the counter 1
			tcb_actcnt[tskid] += 1;
	}


	if(tcb_lastres[runtsk] != RESID_NULL){
		res_recovery();
		CHECK_RESOURCE(FALSE);
	}

	search_schedtsk();						// Call Search Scheduler
	exit_and_dispatch();						//Make it run
	return 0;//remove later
	error_exit:
		_errorhook_par1.tskid = tskid;
		call_errorhook(ercd, OSServiceId_ChainTask);
	return(ercd);
}
