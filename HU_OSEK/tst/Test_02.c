#include "../inc/kernel_cfg.h"
#include "../inc/kernel.h"

#ifdef TEST_02

TASK(L1){
	SetEvent(H2, A);
	
	TerminateTask();
}

TASK(L2){
	__nop();
	TerminateTask();
}


TASK(M1){
	__nop();
	ChainTask(M2); 
}


TASK(M2){
	EventMaskType returned_mask;
	
	ActivateTask(L1);
	
	ActivateTask(L2);
	
	GetEvent(L2,&returned_mask);
	
	ActivateTask(H2);
	
	
	TerminateTask();
}

TASK(H1){__nop();}

TASK(H2){
	EventMaskType returned_mask;
	StatusType error=E_OK;
	WaitEvent(C);//unaffected
	
	SetEvent (H2, A|B|D);
	
	ClearEvent (A|B);
	
	GetEvent(H2,&returned_mask);// returned_mask = D
	
	WaitEvent(A|B);//Enters wait state
	
	error = SetEvent(L1, A); //E_OS_ACCESS
	TerminateTask();
}

TASK(E1){__nop();}
TASK(E2){__nop();}




#endif
