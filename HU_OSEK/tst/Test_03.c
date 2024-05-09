#include "../inc/kernel_cfg.h"
#include "../inc/kernel.h"

#ifdef TEST_03

TASK(L1){
	GetResource(R1);
	ActivateTask(H2);
	ActivateTask(M2);
	//CHECK L1 PRIORITY
	//CHECK L1 STATE
	
	ReleaseResource(R1); //H2 shall run
	
	TerminateTask();
}

TASK(L2){
	__nop();

}


TASK(M1){
	GetResource(R3);
	
	GetResource(R3);//no effect
	
	GetResource(R4);
	
	ReleaseResource(R3); // ERROR
	
	ChainTask(L1);

}


TASK(M2){
	__nop();
	__nop();
	TerminateTask();
}


TASK(H2){
	ActivateTask(E1);
	GetResource(R1);
	Schedule();
	WaitEvent(A);
	ReleaseResource(R1);
	//End of tests
	TerminateTask();
}

TASK(E1){
	__nop();
	__nop();
	TerminateTask();
}
TASK(E2){__nop();}




#endif
