

#ifndef _TASK_H_
#define _TASK_H_
#include "osek_kernel.h"
#include "inc/kernel_cfg.h"
#define TSKID_NULL		((TaskType) UINT8_INVALID)



extern const Priority	tinib_inipri[];
extern const Priority	tinib_exepri[];
extern const UINT8		tinib_maxact[];
extern const BOOL		tinib_autoact[];
extern const FP			tinib_task[];
extern const VP			tinib_stk[];
extern const UINT16		tinib_stksz[];



extern TaskType			tcb_next[];
extern UINT8			tcb_tstat[];
extern Priority			tcb_curpri[];
extern UINT8			tcb_actcnt[];


#if EXT_TASK_COUNT !=0
extern const EventMaskType	tinib_mskevt[];
extern EventMaskType	tcb_curevt[];
extern EventMaskType	tcb_waievt[];
#endif

#if RES_COUNT != 0 
extern ResourceType		tcb_lastres[];
#endif



extern TaskType			runtsk;
extern TaskType			schedtsk;
extern Priority			nextpri;



void	task_initialize (void);
void res_recovery(void);
BOOL	make_active(TaskType tskid);
BOOL	make_runnable(TaskType tskid);
void	search_schedtsk(void);
void 	dispatch(void);			/**STUB**/
void 	exit_and_dispatch(void);/**STUB**/

void	preempt(void);

#endif /* _TASK_H_ */
