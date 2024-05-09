/*
 * Release_Res.c
 *
 *  Created on: Apr 19, 2023
 *      Author: Ziad
 */
#include "../osek_kernel.h"
#include "../check.h"
#include "../task.h"
#include "../resource.h"
//#include "../interrupt.h"

#if (RES_COUNT != 0)
StatusType
ReleaseResource(ResourceType resid)
{
	StatusType	ercd = E_OK;

	CHECK_CALLEVEL(TCL_TASK );
	CHECK_RESID(resid);
	CHECK_ACCESS(tinib_inipri[runtsk] <= resinib_ceilpri[resid]);
	CHECK_NOFUNC(tcb_lastres[runtsk] == resid); 		//LIFO		

	tcb_curpri[runtsk] = rescb_prevpri[resid];
	tcb_lastres[runtsk] = rescb_prevres[resid];
	rescb_prevpri[resid] = TPRI_NULL;
	if (tcb_curpri[runtsk] < nextpri) {
		preempt();
		search_schedtsk();
		dispatch();
	}
	return(E_OK);

  error_exit:
	_errorhook_par1.resid = resid;
	call_errorhook(ercd, OSServiceId_ReleaseResource);
	return(ercd);

}
#endif 
