#include "osek_kernel.h"
#include "check.h"
//#include <stdio.h>
//#include <stdlib.h>
UINT8	callevel = TCL_NULL;
OSServiceIdType	_errorhook_svcid;
_ErrorHook_Par	_errorhook_par1, _errorhook_par2, _errorhook_par3;

#define ERROR_HOOK_ENABLED

void ErrorHook(StatusType ercd){
	__nop();
	__nop();
	__nop();
}
#ifdef ERROR_HOOK_ENABLED

void
call_errorhook(StatusType ercd, OSServiceIdType svcid)
{
	UINT8	saved_callevel;
	if (callevel != TCL_ERROR) {

		_errorhook_svcid = svcid;
		saved_callevel = callevel;

		callevel = TCL_ERROR;
		ErrorHook(ercd);

		callevel = saved_callevel;
	}
}
#else
	
void
call_errorhook(StatusType ercd, OSServiceIdType svcid){}
#endif
