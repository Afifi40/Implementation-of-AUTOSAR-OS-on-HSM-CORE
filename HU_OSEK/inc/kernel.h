#ifndef _KERNEL_H_
#define _KERNEL_H_

//#include <sys_defs.h>
//#include <cpu_defs.h>

#include "osek.h"

#ifndef NULL
#define	NULL			((void *) 0)
#endif

typedef void		*VP;
typedef void		(*FP)(void);

typedef UINT8			TaskType;			
typedef UINT8			TaskStateType;		
typedef UINT64			ResourceType;		
typedef UINT64			EventMaskType;		
typedef UINT32			TickType;			
typedef UINT8			AlarmType;			
typedef UINT8			AppModeType;		
typedef UINT8			OSServiceIdType;	
typedef UINT8			IsrType;			
typedef UINT8			CounterType;		
typedef UINT32			AlarmIncrementType;
typedef UINT32			CounterIncrementType;
typedef UINT8 			AlarmStateType;
typedef UINT32			AlarmTimeType;
typedef UINT8 			BridgeIntType;
typedef UINT32			AlarmCycleTimeType;





typedef struct{
	TaskType TaskID;
	EventMaskType Event;
} EventInfoType;

typedef union {
	FP CallbackFunction;
	TaskType TaskID;
    EventInfoType Ev;
	CounterType Counter;
} ActionInfoType;


typedef enum {
	CALLBACK = 0,
	SETEVENT = 1,
	ACTIVATETASK = 2,
	INCREMENT = 3
} ActionType;



#ifdef ARE_THESE_USEFUL //TODO: CHECK IF THESE ARE USEFUL
/** \brief Auto Start Alarm Type */
typedef struct {
	AppModeType Mode;
	AlarmType Alarm;
	AlarmTimeType AlarmTime;
	AlarmCycleTimeType AlarmCycleTime;
} AutoStartAlarmType;
#endif
/** \brief Type definition of AlarmBaseType
 **
 ** This type is used to represent references to AlarmBase
 **/
typedef struct {
	TickType maxallowedvalue;
	TickType ticksperbase;
	TickType mincycle;
} AlarmBaseType;



typedef TaskType		*TaskRefType;
typedef TaskStateType	*TaskStateRefType;
typedef EventMaskType	*EventMaskRefType;
typedef TickType		*TickRefType;
typedef AlarmBaseType	*AlarmBaseRefType;


#define DeclareTask(TaskName)		extern const TaskType TaskName
#define DeclareResource(ResName)	extern const ResourceType ResName
#define DeclareEvent(EventName)		extern const EventMaskType EventName
#define DeclareAlarm(AlarmName)		extern const AlarmType AlarmName
#define DeclareCounter(CounterName)	extern const CounterType CounterName



extern StatusType ActivateTask(TaskType tskid);
extern StatusType TerminateTask(void);
extern StatusType ChainTask(TaskType tskid);
extern StatusType Schedule(void);
extern StatusType GetTaskID(TaskRefType p_tskid);
extern StatusType GetTaskState(TaskType tskid, TaskStateRefType p_state);

#if (EXT_TASK_COUNT != 0)
extern StatusType SetEvent(TaskType, EventMaskType);
extern StatusType ClearEvent(EventMaskType mask);
extern StatusType GetEvent(TaskType tskid, EventMaskRefType p_mask);
extern StatusType WaitEvent(EventMaskType mask);
#endif

#if (RES_COUNT != 0)
extern StatusType GetResource(ResourceType resid);
extern StatusType ReleaseResource(ResourceType resid);
#endif

#if (ALARMS_COUNT != 0)
extern StatusType GetAlarmBase(AlarmType almid, AlarmBaseRefType p_info);
extern StatusType GetAlarm(AlarmType almid, 	TickRefType p_tick);
extern StatusType SetRelAlarm(AlarmType almid,	TickType incr, TickType cycle);
extern StatusType SetAbsAlarm(AlarmType almid, 	TickType start, TickType cycle);
extern StatusType CancelAlarm(AlarmType almid);
extern StatusType IncrementCounter(CounterType CounterID);
#endif 

extern AppModeType GetActiveApplicationMode(void);
extern void StartOS(AppModeType mode);
extern void ShutdownOS(StatusType ercd);

extern StatusType SignalCounter(CounterType cntid);

extern void ErrorHook(StatusType ercd);
extern void PreTaskHook(void);
extern void PostTaskHook(void);
extern void StartupHook(void);
extern void ShutdownHook(StatusType ercd);

#define E_OS_ACCESS		((StatusType) 1)
#define E_OS_CALLEVEL	((StatusType) 2)
#define E_OS_ID			((StatusType) 3)
#define E_OS_LIMIT		((StatusType) 4)
#define E_OS_NOFUNC		((StatusType) 5)
#define E_OS_RESOURCE	((StatusType) 6)
#define E_OS_STATE		((StatusType) 7)
#define E_OS_VALUE		((StatusType) 8)

#define INVALID_TASK		((TaskType) UINT8_INVALID)

#define SUSPENDED			((StatusType) 0)	
#define RUNNING				((StatusType) 1)	
#define READY				((StatusType) 2)	
#define WAITING				((StatusType) 3)	



#define OSServiceId_ActivateTask				((OSServiceIdType) 0)
#define OSServiceId_TerminateTask				((OSServiceIdType) 1)
#define OSServiceId_ChainTask					((OSServiceIdType) 2)
#define OSServiceId_Schedule					((OSServiceIdType) 3)
#define OSServiceId_GetTaskID					((OSServiceIdType) 4)
#define OSServiceId_GetTaskState				((OSServiceIdType) 5)
#define OSServiceId_EnableAllInterrupts			((OSServiceIdType) 6)
#define OSServiceId_DisableAllInterrupts		((OSServiceIdType) 7)
#define OSServiceId_ResumeAllInterrupts			((OSServiceIdType) 8)
#define OSServiceId_SuspendAllInterrupts		((OSServiceIdType) 9)
#define OSServiceId_ResumeOSInterrupts			((OSServiceIdType) 10)
#define OSServiceId_SuspendOSInterrupts			((OSServiceIdType) 11)
#define OSServiceId_GetResource					((OSServiceIdType) 12)
#define OSServiceId_ReleaseResource				((OSServiceIdType) 13)
#define OSServiceId_SetEvent					((OSServiceIdType) 14)
#define OSServiceId_ClearEvent					((OSServiceIdType) 15)
#define OSServiceId_GetEvent					((OSServiceIdType) 16)
#define OSServiceId_WaitEvent					((OSServiceIdType) 17)
#define OSServiceId_GetAlarmBase				((OSServiceIdType) 18)
#define OSServiceId_GetAlarm					((OSServiceIdType) 19)
#define OSServiceId_SetRelAlarm					((OSServiceIdType) 20)
#define OSServiceId_SetAbsAlarm					((OSServiceIdType) 21)
#define OSServiceId_CancelAlarm					((OSServiceIdType) 22)
#define OSServiceId_IncrementCounter			((OSServiceIdType) 23)
#define OSServiceId_StartOS						((OSServiceIdType) 24)
#define OSServiceId_ShutdownOS					((OSServiceIdType) 25)
#define OSServiceId_SignalCounter				((OSServiceIdType) 26)


typedef union {
		TaskType			tskid;
		TaskRefType			p_tskid;
		TaskStateRefType	p_state;
		ResourceType		resid;
		EventMaskType		mask;
		EventMaskRefType	p_mask;
		AlarmType			almid;
		AlarmBaseRefType	p_info;
		TickRefType			p_tick;
		TickType			incr;
		TickType			cycle;
		TickType			start;
		AppModeType			mode;
		CounterType			cntid;
	} _ErrorHook_Par;

extern OSServiceIdType	_errorhook_svcid;
extern _ErrorHook_Par	_errorhook_par1, _errorhook_par2, _errorhook_par3;



#define OSErrorGetServiceId()				(_errorhook_svcid)

#define OSError_ActivateTask_TaskID()		(_errorhook_par1.tskid)
#define OSError_ChainTask_TaskID()			(_errorhook_par1.tskid)
#define OSError_GetTaskID_TaskID()			(_errorhook_par1.p_tskid)
#define OSError_GetTaskState_TaskID()		(_errorhook_par1.tskid)
#define OSError_GetTaskState_State()		(_errorhook_par2.p_state)
#define OSError_GetResource_ResID()			(_errorhook_par1.resid)
#define OSError_ReleaseResource_ResID()		(_errorhook_par1.resid)
#define OSError_SetEvent_TaskID()			(_errorhook_par1.tskid)
#define OSError_SetEvent_Mask()				(_errorhook_par2.mask)
#define OSError_ClearEvent_Mask()			(_errorhook_par1.mask)
#define OSError_GetEvent_TaskID()			(_errorhook_par1.tskid)
#define OSError_GetEvent_Mask()				(_errorhook_par2.p_mask)
#define OSError_WaitEvent_Mask()			(_errorhook_par1.mask)
#define OSError_GetAlarmBase_AlarmID()		(_errorhook_par1.almid)
#define OSError_GetAlarmBase_Info()			(_errorhook_par2.p_info)
#define OSError_GetAlarm_AlarmID()			(_errorhook_par1.almid)
#define OSError_GetAlarm_Tick()				(_errorhook_par2.p_tick)
#define OSError_SetRelAlarm_AlarmID()		(_errorhook_par1.almid)
#define OSError_SetRelAlarm_increment()		(_errorhook_par2.incr)
#define OSError_SetRelAlarm_cycle()			(_errorhook_par3.cycle)
#define OSError_SetAbsAlarm_AlarmID()		(_errorhook_par1.almid)
#define OSError_SetAbsAlarm_start()			(_errorhook_par2.start)
#define OSError_SetAbsAlarm_cycle()			(_errorhook_par3.cycle)
#define OSError_CancelAlarm_AlarmID()		(_errorhook_par1.almid)
#define OSError_SignalCounter_CounterID()	(_errorhook_par1.cntid)



#endif /* _KERNEL_H_ */
