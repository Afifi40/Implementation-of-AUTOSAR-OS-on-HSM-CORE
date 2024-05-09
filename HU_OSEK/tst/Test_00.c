#include "../inc/kernel_cfg.h"
#include "../inc/kernel.h"

#ifdef TEST_00

TASK(L1){
	__nop();
}


TASK(M1){
	TaskType ID;
	UINT8 state;
	
	ActivateTask(H1);
	
	GetTaskState(H1,&state);
	
	ActivateTask(L1);
	
	GetTaskID(&ID); //check ID at watch
	GetTaskState(L1,&state);
	
	ActivateTask(M1);
	TerminateTask();
}

TASK(H1){
	UINT8 state;
	TaskType ID;
	
	GetTaskState(M1,&state); //check state at watch
	
	GetTaskID(&ID); //check ID at watch
	
	TerminateTask();
	
}

TASK(E1){__nop();}
TASK(L2){__nop();}
TASK(M2){__nop();}
TASK(H2){__nop();}
TASK(E2){__nop();}
#endif