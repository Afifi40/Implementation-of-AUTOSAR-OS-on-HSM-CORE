
#ifndef _OSEK_KERNEL_H_
#define _OSEK_KERNEL_H_


#include "inc/kernel.h"

typedef UINT8 Priority;
typedef UINT8 TaskTotalType;


#define TNUM_PRIORITY	((Priority) 16)

#define TPRI_MINTASK	((Priority) 0)
#define TPRI_MAXTASK	((Priority)(TNUM_PRIORITY - 1))

#define TPRI_SCHEDULER	((Priority) 127)
#define TPRI_NULL		((Priority) UINT8_INVALID)

#define EVTMASK_NONE	((EventMaskType) 0)
#define RESID_NULL		((ResourceType) (~0u))	/* Invalid ID */

#define TCL_NULL		((UINT8) 0x00)
#define TCL_TASK		((UINT8) 0x01)	/*Task context*/
#define TCL_ISR2		((UINT8) 0x02)	/*ISR CAT2 Context*/
#define TCL_ERROR		((UINT8) 0x04)	/* ErrorHook */
#define TCL_PREPOST		((UINT8) 0x08)	/* PreTaskHook or PostTaskHook */
#define TCL_STARTUP		((UINT8) 0x10)	/* StartupHook */
#define TCL_SHUTDOWN	((UINT8) 0x20)	/* ShutdownHook */

extern UINT8		callevel;

extern void	call_errorhook(StatusType ercd, OSServiceIdType svcid);
extern void	call_posttaskhook(void);
extern void	call_pretaskhook(void);



#endif /* _OSEK_KERNEL_H_ */
