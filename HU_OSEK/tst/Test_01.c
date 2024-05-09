#include "../inc/kernel_cfg.h"
#include "../inc/kernel.h"

#ifdef TEST_01

TASK(L1){
	__nop();
	__nop();
	ChainTask(L1);//Actcnt=0, tstate doesn't change from running.
}
TASK(L2){__nop();}

TASK(M1){
	ActivateTask(M2);
	ActivateTask(H1);
	
	TerminateTask();
}

TASK(M2){
	//assert that tcb_tstat[M1] = SUSPENDED
	__nop();
	__nop();
	TerminateTask();
}

TASK(H1){
	__nop();
	//assert that tcb_next[M1] = M2;
	
	ActivateTask(E1);
	////assert that tcb_tstat[E1] = Ready;
	__nop();
	
	Schedule();
	
	ChainTask(L1); //Causes rescheduling
}
TASK(H2){__nop();}

TASK(E1){
	__nop();
	__nop();
	//ends without Termination
}


TASK(E2){__nop();}



#endif
