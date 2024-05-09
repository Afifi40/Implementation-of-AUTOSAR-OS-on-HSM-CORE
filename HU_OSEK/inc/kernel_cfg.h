#ifndef INC_TASKS_CFG_H_
#define INC_TASKS_CFG_H_

#include "autosar.h"
#define TEST_03
/*Extern Tasks and define stack size*/

extern TASK(L1);
#define STACK_SIZE_T0        1024   

extern TASK(M1);
#define STACK_SIZE_T1        1024   

extern TASK(H1);
#define STACK_SIZE_T2        1024   

extern TASK(E1);
#define STACK_SIZE_T3        1024   

extern TASK(L2);
#define STACK_SIZE_T4        1024   

extern TASK(M2);
#define STACK_SIZE_T5        1024   

extern TASK(H2);
#define STACK_SIZE_T6        1024   

extern TASK(E2);
#define STACK_SIZE_T7        1024   


/*Tasks*/

#define L2 0

#define M2 1

#define H2 2

#define E2 3

#define E1 4

#define L1 5

#define M1 6

#define H1 7



/*Resources*/

#define R1 0

#define R3 1

#define R4 2

#define R2 3

#define R5 4

/*Events*/

#define A 1

#define C 2

#define B 4

#define D 8


/*Macros*/
#define EXTENDED_STATUS     
#define TASK_COUNT          8
#define EXT_TASK_COUNT      5 
#define RES_COUNT           5 

#define COUNTER_HW_COUNT    0
#define ALARMS_COUNT        0
#define COUNTER_COUNT       0

#endif