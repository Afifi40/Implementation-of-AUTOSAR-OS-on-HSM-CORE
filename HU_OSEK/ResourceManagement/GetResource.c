/*
 * File Name: Get_Res.c
 * Date: 19/4/2023
 * author: Esraa Ahmed Taha
 */

#include "../osek_kernel.h"
#include "../check.h"
#include "../task.h"
#include "../resource.h"

/*
 *  Resource Acquisition
 */
#if (RES_COUNT != 0)
StatusType
GetResource(ResourceType resid)
{
	StatusType	ercd = E_OK;

	CHECK_CALLEVEL(TCL_TASK);
	CHECK_RESID(resid);
	CHECK_ACCESS((tinib_inipri[runtsk] <= resinib_ceilpri[resid]) 
	&& (rescb_prevpri[resid] == TPRI_NULL));
	
	if((resinib_mskres[runtsk] & (1<<resid)) != 0){
		rescb_prevpri[resid] = tcb_curpri[runtsk];
		rescb_prevres[resid] = tcb_lastres[runtsk];
		tcb_lastres[runtsk]  = resid;
		
		if (resinib_ceilpri[resid] > tcb_curpri[runtsk])
			tcb_curpri[runtsk] = resinib_ceilpri[resid];
	}
	return(E_OK);

  error_exit:
	_errorhook_par1.resid = resid;
	call_errorhook(ercd, OSServiceId_GetResource);
	return(ercd);
}
#endif 