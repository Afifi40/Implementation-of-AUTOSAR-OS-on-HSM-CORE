/*
 * task.c
 * Date : 7/2/2023
 * Author: Ahmed Afifi
 * 
 */

#include "osek_kernel.h"
#include "check.h"
#include "task.h"
#include "resource.h"
#include "inc/std_macros.h"
#include "Target/cpu_context.h"

//#define TEST_ENABLE


Inline void push_task_first(Priority pri, TaskType tskid);
Inline void	push_task_last(Priority pri, TaskType tskid);
Inline TaskType	pop_task(Priority pri);
Inline Priority	bitmap_search(UINT16 bitmap);
Inline void set_bitmap(UINT8 bit);
Inline void set_bitmap(UINT8 bit);


TaskType ready_queue_first[TNUM_PRIORITY];
TaskType ready_queue_last[TNUM_PRIORITY];

Inline void
push_task_last(Priority pri, TaskType tskid)
{
	TaskType first, last;
	//assert(pri <= TPRI_MAXTASK);
	first = ready_queue_first[pri];
	last  = ready_queue_last[pri];

	if (first == TSKID_NULL){//is first queue empty?
		ready_queue_first[pri] = tskid;
		tcb_next[first] = TSKID_NULL;
	}
	else{
		if(last == TSKID_NULL)//is last queue empty?
			tcb_next[first] = tskid;//1st task points to 2nd(inserted task)
		else //both queues aren't empty (at least two tasks of same priority already exist)
			tcb_next[last] = tskid;//last task points to the inserted task
		ready_queue_last[pri]=tskid;//task is inserted in last queue
	}
}

Inline void
push_task_first(Priority pri, TaskType tskid)
{
	//assert(pri <= TPRI_MAXTASK);
	TaskType first = ready_queue_first[pri];
	tcb_next[tskid]= first;
	ready_queue_first[pri] = tskid;

}

/**design your SRS for OSEK requirements in your Documentation**/
/**use a tag documenting rule like in ToppersOsek ASP3 in your documentation and code**/

Inline TaskType
pop_task(Priority pri)
{
	TaskType	first, last;
	first = ready_queue_first[pri];
	last = ready_queue_last[pri];
	if(first != TSKID_NULL){
		ready_queue_first[pri] = tcb_next[first];
		if(first == last)
			ready_queue_last[pri] = TSKID_NULL;
	}
	return(first);
}

/*
 *	#define SHIFTBIT(pri)	(0x8000u >> (pri))
 *	#define	bitmap_search(bitmap) (16 - ffs(bitmap))
 */

#ifndef SHIFTBIT
#define	SHIFTBIT(BIT)		(1u << (BIT))
#endif /* SHIFTBIT */

static UINT16	ready_primap;


#ifndef CPU_BITMAP_SEARCH//define this if CPU allows bitmap searching for faster methods.

/*Find  the most significant one*/
Inline Priority
bitmap_search(UINT16 bitmap)
{
	static const UINT8 search_table[] = { 0, 1, 1, 2, 2, 2, 2,
						3, 3, 3, 3, 3, 3, 3, 3 };
	Priority	pri = 0;

	//assert((bitmap & ((UINT16) 0xffffu)) != 0);
	if ((bitmap & ((UINT16) 0xff00u)) != 0) {
		bitmap >>= 8;
		pri += 8;
	}
	if ((bitmap & ((UINT16) 0xf0)) != 0) {
		bitmap >>= 4;
		pri += 4;
	}
	return(pri + (search_table[(bitmap & ((UINT16) 0x0f)) - 1]));
}


#endif /* CPU_BITMAP_SEARCH */

Inline void
set_bitmap(UINT8 bit){
	ready_primap |= SHIFTBIT(bit);
}

Inline void
clr_bitmap(UINT8 bit){
	ready_primap &= ~SHIFTBIT(bit);
}
void res_recovery(void){
	ResourceType res;
	do{
		res = tcb_lastres[runtsk];
		rescb_prevpri[res] = TPRI_NULL;
		tcb_lastres[runtsk] = rescb_prevres[res];
	}while(tcb_lastres[runtsk] != RESID_NULL);
}
TaskType	runtsk;

TaskType	schedtsk;

Priority	nextpri;


/******************************
 * Summary: Reset runtask, schedtask, ready_queue_first, nextPri, activation count
 * 			Activates tasks that has autostart = TRUE
 *
 * Post-conditions: Dispatch should be called right after at STARTOS, but for now it's called in it.
 ******************************/
void
task_initialize(void)
{
	Priority	pri;
	TaskType	tskid;
	runtsk = TSKID_NULL;
	schedtsk = TSKID_NULL;
	for (pri = 0; pri < TNUM_PRIORITY; pri++) {
		ready_queue_first[pri] = TSKID_NULL;
		ready_queue_last[pri] = TSKID_NULL;
	}
	nextpri = TPRI_MINTASK;
	ready_primap = 0u;

	for (tskid = 0; tskid < TASK_COUNT; tskid++) {
		tcb_next[tskid] = TSKID_NULL;
		tcb_actcnt[tskid] = 0;
		if (tinib_autoact[tskid] == TRUE) {
			(void)make_active(tskid);
			tcb_tstat[tskid] = READY;
		}
		else 
			tcb_tstat[tskid] = SUSPENDED;
	}
	//Initalize_Context(tnum_task);//TODO: Make sure it works !
	dispatch();//should be removed after implementaton of StartOS
}

BOOL
make_active(TaskType tskid)
{
	tcb_curpri[tskid] = tinib_inipri[tskid];
	#if EXT_TASK_COUNT !=0 
	if (tskid < EXT_TASK_COUNT) {
		tcb_curevt[tskid] = EVTMASK_NONE;
		tcb_waievt[tskid] = EVTMASK_NONE;
	}
	#endif
	
	#if RES_COUNT !=0 
	tcb_lastres[tskid] = RESID_NULL;
	#endif
	SetCallingLevel(TCL_TASK);
	return(make_runnable(tskid));
}


/**User space vs kernel space**/



/**
 *
 * schedtsk = runtsk if no other task has higher priority in the queue
 * schedtsk != runtsk if a task in the queue has higher priority than the running task
 * schedpri = highest runnable priority task
 * new_pri  = priority of the newly inserted task.
 **/
BOOL
make_runnable(TaskType tskid)
{

	Priority	new_pri , schedpri;
	if (schedtsk != TSKID_NULL) {
		tcb_tstat[tskid] = READY;
		new_pri  = tcb_curpri[tskid];
		schedpri = tcb_curpri[schedtsk];
		if (new_pri  <= schedpri) {
			push_task_last(new_pri ,tskid);
			set_bitmap(new_pri);
			if (new_pri  > nextpri || nextpri == TPRI_NULL) {
				nextpri = new_pri ;
			}
			return(FALSE);
		}
		else{//newest task is highest in priority
			preempt();
			nextpri = schedpri;
		}
	}
	schedtsk = tskid;
	return(TRUE);
}
void
search_schedtsk(void)
{
	if (ready_primap == ((UINT16) 0)) {
		schedtsk = TSKID_NULL; 
		// or Zero for IDLE task ? maybe case TSKID_NULL in dispatch gives idle task?
	}
	else {
		schedtsk = pop_task(nextpri);
		if (ready_queue_first[nextpri] == TSKID_NULL) {
			clr_bitmap(nextpri);
			nextpri = (ready_primap == ((UINT16) 0)) ?
						TPRI_NULL : bitmap_search(ready_primap);
		}
	}
}

/*STUB*/
/** dispatch hardware independent code
 *	1)put currently running task to ready state
 *	2)make the highest priority task running
 *	3)make its priority equal to execution priority
 *	pre-conditions: schedtsk != 255
 *
 **/
void dispatch(void){
	
	UINT8 status = CONTEXT_INIT_STATE;
	
	if(runtsk != TSKID_NULL){
		status = CONTEXT_PREEMPTION;
		if(runtsk < EXT_TASK_COUNT && tcb_waievt[runtsk] != EVTMASK_NONE)
			tcb_tstat[runtsk] = WAITING;
		else
			tcb_tstat[runtsk] = READY;
	}
	
	tcb_tstat[schedtsk] = RUNNING;
	tcb_curpri[schedtsk] = tinib_exepri[schedtsk];
	
	runtsk = schedtsk;
	SetCallingLevel(TCL_TASK);
	HW_dispatch(status, schedtsk);
}

/** exit_and_dispatch hardware independent code
 *	1)make the highest priority task running
 *	2)make its priority equal to execution priority
 *	pre-conditions: schedtsk != 255
 *	post conditions: should have somewhere to "goto" to avoid causing error???!
 **/
 
void exit_and_dispatch(void){//called if the current running task has been terminated
	UINT8 status = CONTEXT_INIT_STATE;
	if(runtsk != TSKID_NULL){
		tcb_tstat[runtsk] = SUSPENDED;
		status = CONTEXT_TERMINATED;
	}
	
	tcb_tstat[schedtsk] = RUNNING;
	tcb_curpri[schedtsk] = tinib_exepri[schedtsk];
	runtsk = schedtsk;
	SetCallingLevel(TCL_TASK);
	HW_dispatch(status, schedtsk);
}

/**
 * RETURNS: void
 * PARAM: void
 * SUMMARY:
 * 1) push the currently running task first
 * 2) set_bitmap to its priority to allow proper search for highest priority
 * post conditions: dispatch must be called!
 *
 **/

void
preempt(void)
{
	Priority runpri;
	runpri = tcb_curpri[runtsk];
	
	push_task_first(runpri, runtsk);
	set_bitmap(runpri);
}
