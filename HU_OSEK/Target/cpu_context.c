/*
 * cpu_context.c
 *
 *  Created on: Apr 30, 2023
 *      Author: ahmed
 */
#include "cpu_context.h"
TaskType OLD_TASK;
TaskType NEW_TASK;
UINT8 status;

typedef struct {
	UINT32 reg_r4;
	UINT32 reg_r5;
	UINT32 reg_r6;
	UINT32 reg_r7;
	UINT32 reg_r8;
	UINT32 reg_r9;
	UINT32 reg_r10;
	UINT32 reg_r11;
	UINT32 stack_top;	/* is considered a scratch register at interrupt calls only.*/
	UINT32 reg_lr; /* link register */
	//UINT32 reg_r15; /* program counter */
	//UINT32 reg_cpsr; /* current program status register */
} TaskContextType;

extern ResourceType		tcb_lastres[];
extern StatusType TerminateTask(void);
extern const VP tinib_stk[];
extern const FP tinib_task[];
extern Priority				rescb_prevpri[];	/* Priority before resource acquisition */
extern ResourceType			rescb_prevres[];	/* Previously Acquired Resources */


//UINT32 Osek_newTask_stack_base;
FP Osek_newTask_start_code;
TaskContextType	tcb_context_var[TASK_COUNT];
void* Osek_NewTaskPtr_Arch ;

void* Osek_OldTaskPtr_Arch;

#define ICSR (*(volatile int *)0xE000ED04) //Is this the correct loc?
#define PENDSVCLR 27
#define PENDSVSET 28

//#define SHCSR (*(volatile int *)0xE000ED24) //Is this the correct loc?
//#define PENDSVACT 10


Inline void LoadContext()														
	{								
	Osek_NewTaskPtr_Arch = &tcb_context_var[NEW_TASK];	
	__set_CONTROL(USE_PSP);	
	__asm  (																	
		/* load Task Pointer */													
		"LDR R1, =Osek_NewTaskPtr_Arch										\n\t"
		/* load memory location of the pointer */								
		"LDR R1, [R1]														\n\t"
		/* get context */														
		"LDMIA R1!, {R4-R12, LR}											\n\t"
		/*recover PSP*/															
		"MSR PSP, r12														"
	);																			
	}

/** \brief Save context */
Inline void SaveContext() 					
{																				
	Osek_OldTaskPtr_Arch = (void*)&tcb_context_var[OLD_TASK];
	__asm(																	
		/* get the Task Pointer */												
		"LDR R1, =Osek_OldTaskPtr_Arch										\n\t"
		/* load the task pointer */												
		"LDR R1, [R1]														\n\t"
		/*recover PSP*/															
		"MRS R12, PSP														\n\t"
		/* save all registers R4 - R14*/										
		"STMIA R1!,{R4-R12, LR}													"
	);																			
}


 
Inline void PrepareTask() 											
{																				
	Osek_newTask_start_code = tinib_task[NEW_TASK];	
	__set_PSP((UINT32)tinib_stk[NEW_TASK]);					
	//Osek_newTask_start_stk = tinib_stk[NEW_TASK];	
	__set_CONTROL(USE_PSP);	
	tinib_task[NEW_TASK]();
	TerminateTask(); //TODO Fix later
}

void Initalize_Context(void){
	//TODO, Nothing??
}



void HW_dispatch(UINT8 new_status, TaskType new){
	
	NEW_TASK = new;
	status = new_status;	
	//__svc(0);
	__set_CONTROL(USE_MSP);	
	if(NEW_TASK == INVALID_TASK)
		return;
	if(status == CONTEXT_PREEMPTION){
		SaveContext();
	}
	else if( status == CONTEXT_TERMINATED )
		tcb_context_var[OLD_TASK].reg_lr = 0;//when terminating a task, reset  LR
	
	OLD_TASK = NEW_TASK;
	
	if(tcb_context_var[NEW_TASK].reg_lr == 0){//First time for the task to enter.
		PrepareTask();
	}
	else{
		LoadContext();
	}	
}

void SVC_Handler(void){
	
	if(status == CONTEXT_PREEMPTION){
		SaveContext();
	}
	else if( status == CONTEXT_TERMINATED )
		tcb_context_var[OLD_TASK].reg_lr = 0;//when terminating a task, reset  LR
	
	OLD_TASK = NEW_TASK;
	if(tcb_context_var[NEW_TASK].reg_lr == 0){//First time for the task to enter.
		PrepareTask();
	}
	else{
		LoadContext();
	}
}

void PendSV_Handler(void) {
	SETBIT(ICSR, PENDSVCLR);
}

