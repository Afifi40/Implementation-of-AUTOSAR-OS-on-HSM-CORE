
#ifndef _CPU_CONTEXT_H_
#define _CPU_CONTEXT_H_

#include "../osek_kernel.h"
#include "../inc/std_macros.h"
#include "../inc/kernel_cfg.h"

#define CONTEXT_INIT_STATE	0
#define CONTEXT_TERMINATED  1
#define CONTEXT_PREEMPTION	2
#define USE_MSP 0
#define USE_PSP 2




void Initalize_Context(void);
void HW_dispatch(TaskType, TaskType);
void PendSV_Handler(void);

#endif //_CPU_CONTEXT_H_
