#include "autosar.h"
#include "../task.h"
#include "kernel_cfg.h"


extern UINT32 _lc_gb_STACK_T0[];
extern UINT32 _lc_ge_STACK_T0[];

extern UINT32 _lc_gb_STACK_T1[];
extern UINT32 _lc_ge_STACK_T1[];

extern UINT32 _lc_gb_STACK_T2[];
extern UINT32 _lc_ge_STACK_T2[];

extern UINT32 _lc_gb_STACK_T3[];
extern UINT32 _lc_ge_STACK_T3[];

extern UINT32 _lc_gb_STACK_T4[];
extern UINT32 _lc_ge_STACK_T4[];

extern UINT32 _lc_gb_STACK_T5[];
extern UINT32 _lc_ge_STACK_T5[];

extern UINT32 _lc_gb_STACK_T6[];
extern UINT32 _lc_ge_STACK_T6[];

extern UINT32 _lc_gb_STACK_T7[];
extern UINT32 _lc_ge_STACK_T7[];



/*Number of system objects*/


/*Entered Data*/


    
const FP                tinib_task[TASK_COUNT]   = {  OSEK_TASK_L2,  OSEK_TASK_M2,  OSEK_TASK_H2,  OSEK_TASK_E2,  OSEK_TASK_E1,  OSEK_TASK_L1,  OSEK_TASK_M1,  OSEK_TASK_H1 };
    

    
const Priority          tinib_inipri[TASK_COUNT] =  {0,1,2,3,3,0,1,2};
    

    
const Priority          tinib_exepri[TASK_COUNT] = { 0, 1, 15, 3, 3, 0, 1, 15};
   

    
const UINT8             tinib_maxact[TASK_COUNT] = { 2, 2, 2, 0, 2, 2, 2, 2 };
    

    
const BOOL              tinib_autoact[TASK_COUNT] = { 0, 0, 0, 0, 0, 0, 1, 0 };
    

    
const UINT16            tinib_stksz[TASK_COUNT] = {  STACK_SIZE_T0,  STACK_SIZE_T1,  STACK_SIZE_T2,  STACK_SIZE_T3,  STACK_SIZE_T4,  STACK_SIZE_T5,  STACK_SIZE_T6,  STACK_SIZE_T7  };
    

    
#if EXT_TASK_COUNT !=0 
const EventMaskType     tinib_mskevt[EXT_TASK_COUNT] = { C, A|C, A|B|D, A, A };

EventMaskType           tcb_curevt[EXT_TASK_COUNT];
EventMaskType           tcb_waievt[EXT_TASK_COUNT];
#endif //EXT_TASK_COUNT
    

    
#if RES_COUNT !=0    
const Priority          resinib_ceilpri[RES_COUNT] = { 2, 1, 1, 2, 2 };
const ResourceType      resinib_mskres[TASK_COUNT] = { 1<<R2, 1<<R3, 1<<R1, 0, 0, 1<<R1, 1<<R4 | 1<<R3, 1<<R2| 1<<R5 };

Priority                rescb_prevpri[RES_COUNT];	
ResourceType            rescb_prevres[RES_COUNT];	
ResourceType            tcb_lastres[TASK_COUNT];
#endif //RES_COUNT
    

const VP                tinib_stk[TASK_COUNT] = {  _lc_ge_STACK_T0,  _lc_ge_STACK_T1,  _lc_ge_STACK_T2,  _lc_ge_STACK_T3,  _lc_ge_STACK_T4,  _lc_ge_STACK_T5,  _lc_ge_STACK_T6,  _lc_ge_STACK_T7  };

TaskType                tcb_next[TASK_COUNT];
UINT8                   tcb_tstat[TASK_COUNT];
Priority                tcb_curpri[TASK_COUNT];
UINT8                   tcb_actcnt[TASK_COUNT];

/*pragma Section*/

#pragma section "T0_STACK"
UINT32 stack_area_T0[STACK_SIZE_T0/4];
#pragma endsection

#pragma section "T1_STACK"
UINT32 stack_area_T1[STACK_SIZE_T1/4];
#pragma endsection

#pragma section "T2_STACK"
UINT32 stack_area_T2[STACK_SIZE_T2/4];
#pragma endsection

#pragma section "T3_STACK"
UINT32 stack_area_T3[STACK_SIZE_T3/4];
#pragma endsection

#pragma section "T4_STACK"
UINT32 stack_area_T4[STACK_SIZE_T4/4];
#pragma endsection

#pragma section "T5_STACK"
UINT32 stack_area_T5[STACK_SIZE_T5/4];
#pragma endsection

#pragma section "T6_STACK"
UINT32 stack_area_T6[STACK_SIZE_T6/4];
#pragma endsection

#pragma section "T7_STACK"
UINT32 stack_area_T7[STACK_SIZE_T7/4];
#pragma endsection


#if ALARMS_COUNT !=0
TickType cnt_time[COUNTER_COUNT];

AlarmStateType alrm_state[ALARMS_COUNT];
AlarmTimeType alrm_time[ALARMS_COUNT];
AlarmCycleTimeType alrm_cycTime[ALARMS_COUNT];

const CounterType alrmini_cnt[ALARMS_COUNT];
const ActionType alrmini_act[ALARMS_COUNT];
const ActionInfoType alrmini_actInfo[ALARMS_COUNT];

//const ActionType brdgini_act[BRIDGE_INT_COUNT];
//const ActionInfoType brdgini_actInfo[BRIDGE_INT_COUNT];


const UINT8	cntini_AlrmNum[COUNTER_COUNT];
const AlarmType* cntini_AlrmRef[COUNTER_COUNT];
const TickType cntini_maxVal[COUNTER_COUNT];
const TickType cntini_minCyc[COUNTER_COUNT];
const TickType cntini_ticksPBase[COUNTER_COUNT];

#endif //ALARMS_COUNT